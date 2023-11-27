#include "Engine.hpp"
#include "CameraActor.hpp"

#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stbi_image_write.h"

#include "cube.h"

namespace SHM {
void skybox(unsigned int *textureId);
Engine::Engine(const char *project_name, API_TYPE api_type, const char *cwd) : mainCharacter(nullptr) {
    // this->cwd = std::string{cwd};
    this->m_renderer = nullptr;
    this->m_camera = std::shared_ptr<Camera>{new Camera{}};
    this->m_camera_character = true;
    this->cwd = ".";
    this->cameraCharacter = new CameraActor{};

    // initialize physics
    this->m_world = new PHYSICS::World{};
    Engine::cwd = std::string{cwd, std::string_view{cwd}.find_last_of("/")};
    std::cout << "START THE ENGINE at : " << this->cwd << std::endl;
    context_manager = new ContextManager{project_name};
    m_handler = new Handler{context_manager->GetWindow(), m_camera};
    std::cout << "BEFORE" << std::endl;
    setRenderer(api_type);
    m_renderer->GetUtility()->InitWorld();
    InitWorld();
    std::cout << "AFTER" << std::endl;
    skyboxshader = CreateShader("/assets/skybox.vs", "/assets/skybox.fs");
    skyboxshader->createProgram();

    // uploading camera and view matrices to buffers
    SHM::BUFFERS::uploadSubDataToUBO(m_renderer->ubo_vp, m_renderer->getProjectionMatrix());
    SHM::BUFFERS::uploadSubDataToUBO(m_renderer->ubo_vp, m_renderer->getViewMatrix(), sizeof(glm::mat4));

    SHM::BUFFERS::uploadSubDataToUBO(m_renderer->ubo_lights, glm::vec3(-0.5, -0.5, -0.5));
    SHM::BUFFERS::uploadSubDataToUBO(m_renderer->ubo_lights, glm::vec3(0.9, 0.9, 0.9), sizeof(glm::vec4));
    SHM::BUFFERS::uploadSubDataToUBO(m_renderer->ubo_lights, glm::vec3(-1.0, 0.0, -2.0), 3 * sizeof(glm::vec4));
}

Engine::~Engine() {
    delete context_manager;
    delete m_handler;
    delete m_world;
    delete cameraCharacter;
    std::cout << "Engine Destructed" << std::endl;
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

    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    skybox(&this->skytextureId);
    skyboxshader->use();
    skyboxshader->setInt("skybox", 0);
    outLoop(context_manager->GetWindow());

    while (!glfwWindowShouldClose(context_manager->GetWindow())) {

        glClearColor(0.4f, 0.7f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        context_manager->processInput();

        // calculate Shadows
        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;
        float near_plane = 1.0f, far_plane = 40.5f;
        lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        lightView = glm::lookAt(glm::vec3(-2.0f, 6.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;

        // m_renderer->m_shadow_map_shader->use();
        // m_renderer->m_shadow_map_shader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

        // glViewport(0, 0, 1024, 1024);
        // glBindFramebuffer(GL_FRAMEBUFFER, m_renderer->depth_map_fbo);
        // glClear(GL_DEPTH_BUFFER_BIT);
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, m_renderer->shadow_map_texture);
        // m_renderer->Draw(false, m_renderer->m_shadow_map_shader);

        // glBindFramebuffer(GL_FRAMEBUFFER, 0);

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
        glBindTexture(GL_TEXTURE_2D, m_renderer->shadow_map_texture);
        Loop();

        // glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
        glDepthMask(GL_FALSE);
        skyboxshader->use();
        skyboxshader->setMat4("view", glm::mat4(glm::mat3(m_renderer->getViewMatrix())));
        // skyboxshader->setMat4("view", m_renderer->getViewMatrix());
        skyboxshader->setMat4("projection", m_renderer->getProjectionMatrix());
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->skytextureId);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default
        glDepthMask(GL_TRUE);

        m_renderer->Draw();
        // a = glGetError();
        // if (a != GL_NO_ERROR) {
        //     std::cout << "Error happend after ~~~~ ! " << a << std::endl;
        // }

        auto key =
            m_handler->keyboard(context_manager->GetWindow(), !this->mainCharacter ? this->cameraCharacter : this->mainCharacter);
        glfwSwapBuffers(context_manager->GetWindow());
        glfwPollEvents();
        Engine::m_world->updateWorld(0.01f);
        Engine::getCamera()->updateCameraPosition();
    }
}

Handler *Engine::getHandler() { return m_handler; }

std::shared_ptr<shader> Engine::CreateShader(const char *vertex_code, const char *fragment_code) {
    std::string _vertexPath{Engine::cwd + vertex_code};
    std::string _fragmentPath{Engine::cwd + fragment_code};
    std::cout << "shader file here: " << Engine::cwd << " - " << _vertexPath << " - " << _fragmentPath << std::endl;
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
    std::cout << "what is going on" << m_renderer->getUboIndex("light") << std::endl;
    m_renderer->ubo_vp = m_renderer->GetUtility()->createNewGlobalBlock("VPMatrices", 3 * sizeof(glm::mat4), &b);
    m_renderer->ubo_lights = m_renderer->GetUtility()->createNewGlobalBlock("Lights", 16 * 4 + 16 * 12 * 5, &b);
    m_renderer->ubo_spots = m_renderer->GetUtility()->createNewGlobalBlock("Spots", 12 * (112), &b);

    // configure shadow
    // m_renderer->enableShadows();

    return -23;
}

PHYSICS::World *Engine::getPhysicWorld() { return Engine::m_world; }

void Engine::saveImage(char *file_path) {

    int width = 1024, height;
    glBindBuffer(GL_TEXTURE_2D, getRenderer()->shadow_map_texture);
    glfwGetFramebufferSize(context_manager->GetWindow(), &width, &height);
    GLsizei nrchannel = 3;
    GLsizei stride = width * nrchannel;
    stride += (stride % 4) ? (4 - stride % 4) : 0;

    GLsizei bufferSize = stride * height;
    std::vector<char> buffer(bufferSize);

    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
    stbi_flip_vertically_on_write(true);
    stbi_write_png(file_path, width, height, nrchannel, buffer.data(), stride);
}

std::shared_ptr<Engine> Engine::GetEngine() {
    if (m_engine == nullptr) {
        std::cout << "ENGINE: "
                  << "Engine has not been started yet!" << std::endl;
    }
    return m_engine;
}

std::shared_ptr<Engine> Engine::startEngine(const char *project_name, API_TYPE api_type, const char *cwd) {
    m_engine = std::shared_ptr<Engine>{new Engine(project_name, api_type, cwd)};
    return m_engine;
}

// void Engine::setActionToKey(KEY key, Command *command) { this->m_handler->setKeyToCommand(key, command); }

void Engine::setMovingCharacter(BaseActor *actor) { this->mainCharacter = actor; }

void Engine::Loop(){};
void Engine::outLoop(GLFWwindow *window){};

void skybox(unsigned int *textureId) {
    // first create the texture_slot
    // unsigned int textureId;
    glGenTextures(1, textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, *textureId);
    std::vector<std::string> cubeSidePath{
        // /home/ahmad/Documents/project/cpp/shm/Engine/assets/cubemaps/skybox/back.jpg
        "/home/ahmad/Documents/project/cpp/shm/Engine/assets/cubemaps/skybox/right.jpg",
        "/home/ahmad/Documents/project/cpp/shm/Engine/assets/cubemaps/skybox/left.jpg",
        "/home/ahmad/Documents/project/cpp/shm/Engine/assets/cubemaps/skybox/top.jpg",
        "/home/ahmad/Documents/project/cpp/shm/Engine/assets/cubemaps/skybox/bottom.jpg",
        "/home/ahmad/Documents/project/cpp/shm/Engine/assets/cubemaps/skybox/front.jpg",
        "/home/ahmad/Documents/project/cpp/shm/Engine/assets/cubemaps/skybox/back.jpg",
    };
    // load the texture
    int width, height, nrchannel;
    // upload texture to the gpu memory
    for (int i = 0; i < cubeSidePath.size(); i++) {
        unsigned char *data = stbi_load(cubeSidePath[i].c_str(), &width, &height, &nrchannel, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            std::cout << "Failed to load skybox Texture " << stbi_failure_reason() << cubeSidePath[i] << std::endl;
        }
    }
    // setup texture properties
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

} // namespace SHM
