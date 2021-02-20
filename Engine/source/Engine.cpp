#include "Engine.hpp"

namespace SHM{

    Engine::Engine(const char* project_name, API_TYPE api_type){
        std::cout<<"START THE ENGINE"<<std::endl;
        context_manager = new ContextManager{project_name};
        m_handler = new Handler{context_manager->GetWindow(), &m_camera};
        // glfwSetCursorPosCallback(context_manager->GetWindow(), &m_handler->mouse);
        setRenderer(api_type);
    }

    Engine::~Engine(){
        delete context_manager;
        delete m_handler;
        std::cout<<"Engine Destructed"<<std::endl;
    }

    void Engine::setRenderer(API_TYPE api_type){
        switch (api_type)
        {
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
        m_renderer->shader_program.setMat4("projection", m_renderer->getProjectionMatrix());
        m_renderer->shader_program.setMat4("view", m_renderer->getViewMatrix());
        m_renderer->setViewMatrix(glm::lookAt(m_camera.m_position, m_camera.m_position + m_camera.m_front, m_camera.m_up));
        // render the loaded model
        m_renderer->setModelMatrix(glm::translate(m_renderer->getModelMatrix(), glm::vec3(1.0f, 1.0f, 1.0f))); 
        m_renderer->setModelMatrix(glm::scale(m_renderer->getModelMatrix(), glm::vec3(1.0f, 1.0f, 1.0f)));
        m_renderer->setModelMatrix(glm::rotate(m_renderer->getModelMatrix(), glm::radians(45.0f), glm::vec3(0.0,1.0,0.0)));
        m_renderer->shader_program.setMat4("model", m_renderer->getModelMatrix());   
        m_renderer->shader_program.setFloat("iTime", glfwGetTime());
        
        // Handler::keyboard(context_manager->GetWindow(), m_camera);
        m_handler->keyboard(context_manager->GetWindow());
        
        glfwSwapBuffers(context_manager->GetWindow());
        glfwPollEvents();

        }
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

        m_camera.m_yaw += xoffset;
        m_camera.m_pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (m_camera.m_pitch > 89.0f)
            m_camera.m_pitch = 89.0f;
        if (m_camera.m_pitch < -89.0f)
            m_camera.m_pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(m_camera.m_yaw)) * cos(glm::radians(m_camera.m_pitch));
        front.y = sin(glm::radians(m_camera.m_pitch));
        front.z = sin(glm::radians(m_camera.m_yaw)) * cos(glm::radians(m_camera.m_pitch));
        m_camera.m_front = glm::normalize(front);
    }



    std::shared_ptr<BaseRenderer> Engine::m_renderer = nullptr;
}


