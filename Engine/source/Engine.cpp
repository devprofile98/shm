#include <thread>
#include <memory>
#include "Engine.hpp"
#include "CameraActor.hpp"

#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stbi_image_write.h"

#include "Logger.hpp"

namespace SHM {
void skybox(unsigned int *textureId);
Engine::Engine(const char *project_name, API_TYPE api_type, const char *cwd) : mainCharacter(nullptr) {
    // initializing the Engine
    this->m_renderer = nullptr;
    this->m_camera = std::shared_ptr<Camera>{new Camera{}};
    this->m_camera_character = true;
    this->cwd = ".";
    this->cameraCharacter = new CameraActor{};

    // initialize physics
    this->m_world = new PHYSICS::World{};

    // current working directory path, relative to where the Engine starts
    Engine::cwd = std::string{cwd, std::string_view{cwd}.find_last_of("/")};
    Logger::info("Start The Engine At : {}", this->cwd);

    // Setting up the Renderer
    context_manager = new ContextManager{project_name};
    m_handler = new Handler{context_manager->GetWindow(), m_camera};
    setRenderer(api_type);
    m_renderer->GetUtility()->InitWorld();
    InitWorld();

    // uploading camera and view matrices to buffers
    SHM::BUFFERS::uploadSubDataToUBO(m_renderer->ubo_vp, m_renderer->getProjectionMatrix());
    SHM::BUFFERS::uploadSubDataToUBO(m_renderer->ubo_vp, m_renderer->getViewMatrix(), sizeof(glm::mat4));

    // Uploading Directional Light Data to GPU buffers
    SHM::BUFFERS::uploadSubDataToUBO(m_renderer->ubo_lights, glm::vec3(-0.5, -0.5, -0.5));
    SHM::BUFFERS::uploadSubDataToUBO(m_renderer->ubo_lights, glm::vec3(0.9, 0.9, 0.9), sizeof(glm::vec4));
    SHM::BUFFERS::uploadSubDataToUBO(m_renderer->ubo_lights, glm::vec3(-1.0, 1.0, -1.0), 3 * sizeof(glm::vec4));
}

Engine::~Engine() {
    delete context_manager;
    delete m_handler;
    delete m_world;
    delete cameraCharacter;
    Logger::debug("Engine Destroyed, Good bye!");
}

void Engine::setRenderer(API_TYPE api_type) {
    switch (api_type) {
        case OPENGL:
            m_renderer = std::shared_ptr<openGLRenderer>{new openGLRenderer{m_camera}}; // set OPENGL as graphic api
            break;
        case VULKAN:
            m_renderer = std::shared_ptr<openGLRenderer>{new openGLRenderer{m_camera}}; // set VULKAN as graphic api
            break;
        default:
            m_renderer = std::shared_ptr<openGLRenderer>{new openGLRenderer{m_camera}};
            break;
    }
}

// return renderer object to user
std::shared_ptr<BaseRenderer> Engine::getRenderer() { return SHM::Engine::GetEngine()->m_renderer; }

std::shared_ptr<Camera> Engine::getCamera() { return SHM::Engine::GetEngine()->m_camera; }

// Main Render Loop
// ---------------------------------
void Engine::MainRenderLoop() {

    // loading user configurations
    outLoop(context_manager->GetWindow());

    while (!glfwWindowShouldClose(context_manager->GetWindow())) {

        glClearColor(0.4f, 0.7f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        context_manager->processInput();

        // calculate Shadows
        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;
        float near_plane = 1.0f, far_plane = 60.5f;
        lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        lightView = glm::lookAt(glm::vec3(5.0f, 5.0f, -1.0f), glm::vec3(1.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;

        m_renderer->m_shadow_map_shader->use();
        m_renderer->m_shadow_map_shader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

        ///// drawing shadow
        glViewport(0, 0, 1024, 1024);
        glBindFramebuffer(GL_FRAMEBUFFER, m_renderer->depth_map_fbo);
        glClear(GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0 + m_renderer->shadow_map_texture);
        glBindTexture(GL_TEXTURE_2D, m_renderer->shadow_map_texture);
        // m_renderer->m_shadow_map_shader->setInt("shadowMap", 2);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        m_renderer->Draw(false, m_renderer->m_shadow_map_shader);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glCullFace(GL_BACK);
        glDisable(GL_CULL_FACE);
        // TODO fix memory leak here
        //        if (glfwGetKey(context_manager->GetWindow(), GLFW_KEY_P) == GLFW_PRESS){
        //            m_renderer->LoadShaders(
        //                    "F:/project/SHM/Engine/assets/model_loading.vs",
        //                    "F:/project/SHM/Engine/assets/model_loading.fs"
        //                     );
        //        }

        if (glfwGetKey(context_manager->GetWindow(), GLFW_KEY_P) == GLFW_PRESS) {

            saveImage("screenshot.png");
        }

        SHM::BUFFERS::uploadSubDataToUBO(Engine::getRenderer()->ubo_vp, Engine::getRenderer()->getViewMatrix(),
                                         sizeof(glm::mat4));
        SHM::BUFFERS::uploadSubDataToUBO(m_renderer->ubo_vp, lightSpaceMatrix, 2 * sizeof(glm::mat4));

        m_renderer->setViewMatrix(glm::lookAt(m_camera->m_position, m_camera->m_position + m_camera->m_front, m_camera->m_up));

        // drawing user defined objects
        glViewport(0, 0, 1920, 1080);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        Loop();

        // render opaque objects first, and find transparent in object and sort them
        m_renderer->Draw();
        // draw skybox only on empty pixels
        if (skybox != nullptr) {
            this->skybox->Draw(m_renderer->getViewMatrix(), m_renderer->getProjectionMatrix());
        }
        // draw transparent objects in order
        m_renderer->Draw(true);

        // handle keyboard input
        auto key =
            m_handler->keyboard(context_manager->GetWindow(), !this->mainCharacter ? this->cameraCharacter : this->mainCharacter);

        glfwSwapBuffers(context_manager->GetWindow());
        glfwPollEvents();
        // update physics
        Engine::m_world->updateWorld(0.01f);
        Engine::getCamera()->updateCameraPosition();
    }
}

Handler *Engine::getHandler() { return m_handler; }

std::shared_ptr<shader> Engine::CreateShader(const char *vertex_code, const char *fragment_code) {
    std::string _vertexPath{Engine::cwd + vertex_code};
    std::string _fragmentPath{Engine::cwd + fragment_code};
    std::shared_ptr<shader> sh{new shader{_vertexPath.c_str(), _fragmentPath.c_str()}};
    return sh;
}

void Engine::mouse(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        last_x = xpos;
        last_y = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - last_x;
    float yoffset = last_y - ypos; // reversed since y-coordinates go from bottom to top
    last_x = xpos;
    last_y = ypos;
    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    m_camera->m_yaw += xoffset;
    m_camera->m_pitch += yoffset;
    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (m_camera->m_pitch > 89.0f)
        m_camera->m_pitch = 89.0f;
    if (m_camera->m_pitch < -89.0f)
        m_camera->m_pitch = -89.0f;
    glm::vec3 front;
    front.x = cos(glm::radians(m_camera->m_yaw)) * cos(glm::radians(m_camera->m_pitch));
    front.y = sin(glm::radians(m_camera->m_pitch));
    front.z = sin(glm::radians(m_camera->m_yaw)) * cos(glm::radians(m_camera->m_pitch));
    m_camera->m_front = glm::normalize(front);
}

bool Engine::InitWorld() {
    int b{-2};
    // configure GLOBAL variables
    m_renderer->getUboIndex("light");
    m_renderer->ubo_vp = m_renderer->GetUtility()->createNewGlobalBlock("VPMatrices", 3 * sizeof(glm::mat4), &b);
    m_renderer->ubo_lights = m_renderer->GetUtility()->createNewGlobalBlock("Lights", 16 * 4 + 16 * 12 * 5, &b);
    m_renderer->ubo_spots = m_renderer->GetUtility()->createNewGlobalBlock("Spots", 12 * (112), &b);

    // configure shadow
    m_renderer->enableShadows();

    Logger::info("Global block set, World Initilized.");
    return true;
}

PHYSICS::World *Engine::getPhysicWorld() { return Engine::m_world; }

void Engine::saveImage(char *file_path) {

    int width = 1024, height;
    glBindBuffer(GL_TEXTURE_2D, getRenderer()->shadow_map_texture);
    glfwGetFramebufferSize(context_manager->GetWindow(), &width, &height);
    GLsizei nrchannel = 3;
    GLsizei stride = width * nrchannel;
    stride += (stride % 4) ? (4 - stride % 4) : 0;

    std::vector<char> *buffer = new std::vector<char>(stride * height);

    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer->data());
    stbi_flip_vertically_on_write(true);
    std::thread t{[file_path, width, height, nrchannel, buffer, stride] {
        stbi_write_png(file_path, width, height, nrchannel, buffer->data(), stride);
        delete buffer;
    }};
    t.detach();
}

std::shared_ptr<Engine> Engine::GetEngine() {
    if (m_engine == nullptr) {
        SHM::Logger::error("Engine has not been started yet!");
    }
    return m_engine;
}

std::shared_ptr<Engine> Engine::startEngine(const char *project_name, API_TYPE api_type, const char *cwd) {
    m_engine = std::shared_ptr<Engine>{new Engine(project_name, api_type, cwd)};
    return m_engine;
}

void Engine::setMovingCharacter(BaseActor *actor) { this->mainCharacter = actor; }

bool Engine::setSkyShader(std::vector<std::string> sides, std::shared_ptr<shader> sh) {

    std::shared_ptr<shader> skyboxshader;
    if (sh == nullptr) {
        skyboxshader = CreateShader("/assets/shaders/skybox.vs", "/assets/shaders/skybox.fs");
        skyboxshader->createProgram();
    }
    this->skybox = std::make_shared<SHM::opengl::CubeMaps>(sides, sh ? sh : skyboxshader);
    return true;
}

void Engine::Loop(){};
void Engine::outLoop(GLFWwindow *window){};

} // namespace SHM
