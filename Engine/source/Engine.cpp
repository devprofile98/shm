#include "Engine.hpp"

namespace SHM{

    Engine::Engine(const char* project_name, API_TYPE api_type){
        std::cout<<"START THE ENGINE"<<std::endl;
        context_manager = new ContextManager{project_name};
        setRenderer(api_type);
        m_renderer->m_model = glm::mat4(1.0f);
        m_renderer->m_projection = glm::perspective(glm::radians(80.0f), 1920.0f/ 1080.0f, 0.1f, 100.0f);
        m_renderer->m_view = glm::lookAt(m_camera.m_position, m_camera.m_position + m_camera.m_front, m_camera.m_up);

        // MainRenderLoop();
    }

    Engine::~Engine(){
        delete context_manager;
        std::cout<<"Engine Destructed"<<std::endl;
    }

    void Engine::setRenderer(API_TYPE api_type){
        switch (api_type)
        {
        case OPENGL:
            m_renderer = std::shared_ptr<openGLRenderer>{new openGLRenderer{}}; // set OPENGL as graphic api
            break;
        case VULKAN:
            m_renderer = std::shared_ptr<openGLRenderer>{new openGLRenderer{}}; // set VULKAN as graphic api
            break;
        default:
            m_renderer = std::shared_ptr<openGLRenderer>{new openGLRenderer{}};
            break;
        }
    }

    
    std::shared_ptr<BaseRenderer> Engine::getRenderer(){
        return SHM::Engine::m_renderer;
    }

    // Main Render Loop
    void Engine::MainRenderLoop(){
        while (!glfwWindowShouldClose(context_manager->GetWindow())){
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        context_manager->processInput();
        m_renderer->Draw();
        m_renderer->shader_program.use();
        m_renderer->shader_program.setMat4("projection", m_renderer->m_projection);
        m_renderer->shader_program.setMat4("view", m_renderer->m_view);
        m_renderer->m_view = glm::lookAt(m_camera.m_position, m_camera.m_position + m_camera.m_front, m_camera.m_up);

        // render the loaded model
        m_renderer->m_model = glm::translate(m_renderer->m_model, glm::vec3(1.0f, 1.0f, 1.0f)); // translate it down so it's at the center of the scene
        m_renderer->m_model = glm::scale(m_renderer->m_model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        m_renderer->shader_program.setMat4("model", m_renderer->m_model);


        float cameraSpeed = 2.5f * 0.001f ;
        if(glfwGetKey(context_manager->GetWindow(),GLFW_KEY_W) == GLFW_PRESS){
            m_camera.m_position += cameraSpeed;
            std::cout<<"process WWW"<<std::endl;
        }
        if (glfwGetKey(context_manager->GetWindow(), GLFW_KEY_S) == GLFW_PRESS){
            m_camera.m_position -= cameraSpeed;
            std::cout<<"process SSSS"<<std::endl;

        }
        if (glfwGetKey(context_manager->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
            m_camera.m_position -= glm::normalize(glm::cross(m_camera.m_front, m_camera.m_up)) * cameraSpeed;
        if (glfwGetKey(context_manager->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
            m_camera.m_position += glm::normalize(glm::cross(m_camera.m_front, m_camera.m_up)) * cameraSpeed;

        glfwSwapBuffers(context_manager->GetWindow());
        glfwPollEvents();
        }
    }



    std::shared_ptr<BaseRenderer> Engine::m_renderer = nullptr;
}


