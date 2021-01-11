#include "Engine.hpp"

namespace SHM{

    Engine::Engine(const char* project_name, API_TYPE api_type){
        std::cout<<"START THE ENGINE"<<std::endl;

        context_manager = new ContextManager{project_name};
        setRenderer(api_type);

        MainRenderLoop();
    }

    Engine::~Engine(){
        delete context_manager;

        std::cout<<"Engine Destructed"<<std::endl;
    }

    void Engine::setRenderer(API_TYPE api_type){
        switch (api_type)
        {
        case OPENGL:
            m_renderer =  std::shared_ptr<openGLRenderer>{new openGLRenderer{}}; // set OPENGL as graphic api
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

        glfwSwapBuffers(context_manager->GetWindow());
        glfwPollEvents();
        }
    }



    std::shared_ptr<BaseRenderer> Engine::m_renderer = nullptr;
}


