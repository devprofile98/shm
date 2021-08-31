#include "Engine.hpp"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stbi_image_write.h"

namespace SHM{

Engine::Engine(const char* project_name, API_TYPE api_type){
    std::cout<<"START THE ENGINE"<<std::endl;
    context_manager = new ContextManager{project_name};
    m_handler = new Handler{context_manager->GetWindow(), m_camera};
    setRenderer(api_type);
    m_renderer->GetUtility()->InitWorld();
    InitWorld();
    // uploading camera and view matrices to buffers
    SHM::BUFFERS::uploadSubDataToUBO(m_renderer->ubo_vp, m_renderer->getProjectionMatrix());
    SHM::BUFFERS::uploadSubDataToUBO(m_renderer->ubo_vp, m_renderer->getViewMatrix(), sizeof(glm::mat4));

    SHM::BUFFERS::uploadSubDataToUBO(m_renderer->ubo_lights, glm::vec3(0.0,-1.0,0.0));
    SHM::BUFFERS::uploadSubDataToUBO(m_renderer->ubo_lights, glm::vec3(0.9,0.9,0.9), sizeof(glm::vec4));
    SHM::BUFFERS::uploadSubDataToUBO(m_renderer->ubo_lights, glm::vec3(-1.0,0.0,-2.0), 3*sizeof(glm::vec4));


    // perparing user configurations
    outLoop();

}

Engine::~Engine(){
    delete context_manager;
    delete m_handler;
    std::cout<<"Engine Destructed"<<std::endl;
}

void Engine::setRenderer(API_TYPE api_type){
    switch (api_type){
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
std::shared_ptr<BaseRenderer> Engine::getRenderer(){
    return SHM::Engine::m_renderer;
}

std::shared_ptr<Camera> Engine::getCamera(){
    return SHM::Engine::m_camera;
}

// Main Render Loop
// ---------------------------------
void Engine::MainRenderLoop(){
    while (!glfwWindowShouldClose(context_manager->GetWindow())){

        glClearColor(0.4f, 0.7f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        context_manager->processInput();
        inLoop();

        // calculate Shadows
        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;
        float near_plane = 1.0f, far_plane = 7.5f;
        lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        lightView = glm::lookAt(glm::vec3(-4.0f, 6.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;

        m_renderer->m_shadow_map_shader->use();
        m_renderer->m_shadow_map_shader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

        glViewport(0, 0, 1024, 1024);
        glBindFramebuffer(GL_FRAMEBUFFER, m_renderer->depth_map_fbo);
            glClear(GL_DEPTH_BUFFER_BIT);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_renderer->shadow_map_texture);
            m_renderer->Draw(m_renderer->m_shadow_map_shader);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // TODO fix memory leak here
        //        if (glfwGetKey(context_manager->GetWindow(), GLFW_KEY_P) == GLFW_PRESS){
        //            m_renderer->LoadShaders(
        //                    "F:/project/SHM/Engine/assets/model_loading.vs",
        //                    "F:/project/SHM/Engine/assets/model_loading.fs"
        //                     );
        //        }

        //        m_renderer->shader_program.use();
        SHM::BUFFERS::uploadSubDataToUBO(Engine::getRenderer()->ubo_vp, Engine::getRenderer()->getViewMatrix(), sizeof(glm::mat4));
        SHM::BUFFERS::uploadSubDataToUBO(m_renderer->ubo_vp, lightSpaceMatrix, 2*sizeof(glm::mat4));

        m_renderer->setViewMatrix(glm::lookAt(m_camera->m_position, m_camera->m_position + m_camera->m_front, m_camera->m_up));
        //        SHM::BUFFERS::uploadSubDataToUBO(m_renderer->ubo_lights, m_camera->m_position, 3*sizeof(glm::vec4));

        // drawing user defined objects
        glViewport(0, 0, 960, 540);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, m_renderer->shadow_map_texture);
        m_renderer->Draw();

        m_handler->keyboard(context_manager->GetWindow());
        glfwSwapBuffers(context_manager->GetWindow());
        glfwPollEvents();

    }
}

std::shared_ptr<shader> Engine::CreateShader(const char *vertex_code, const char *fragment_code)
{
    std::shared_ptr<shader> sh{new shader{vertex_code, fragment_code}};
    return sh;
}

void Engine::mouse(GLFWwindow* window, double xpos, double ypos){
    if (firstMouse)
    {
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

bool Engine::InitWorld() const
{
    int b{-2};
    // configure GLOBAL variables
    getRenderer()->ubo_vp = getRenderer()->GetUtility()->createNewGlobalBlock("VPMatrices", 3*sizeof(glm::mat4),&b);
    getRenderer()->ubo_lights = getRenderer()->GetUtility()->createNewGlobalBlock("Lights", 16*4 + 16*12*5,&b);
    getRenderer()->ubo_spots = getRenderer()->GetUtility()->createNewGlobalBlock("Spots", 12*(112),&b);

    // configure shadow
    getRenderer()->enableShadows();

    return -23;
}

void Engine::saveImage(char *file_path){

        int width=1024, height;
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

std::shared_ptr<BaseRenderer> Engine::m_renderer = nullptr;
std::shared_ptr<Camera> Engine::m_camera{ new Camera{}};
}


