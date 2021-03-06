#ifndef SHM_ENGINE_H
#define SHM_ENGINE_H

#define MAKE_SHM_LIB

#include "Core.hpp"
#include <memory>
#include <iostream>
#include <stdint.h>
#include "Camera.hpp"
#include "Handler.hpp"
#include "openGLRenderer.hpp"


namespace SHM
{

    enum API_TYPE{
        OPENGL,
        VULKAN
    };

    class SHM_EXPORT Engine{
    public:
        Engine(const char* project_name, API_TYPE api_type);
        ~Engine();

        static std::shared_ptr<BaseRenderer> getRenderer();
        static std::shared_ptr<Camera> getCamera();
        void MainRenderLoop();

        static std::shared_ptr<shader> CreateShader(const char *vertex_code, const char *fragment_code);

        // TODO remove it from here and add it to handler class
        void mouse(GLFWwindow* window, double xpos, double ypos);
        float last_x, last_y;
        bool firstMouse=true;

        bool InitWorld() const;
        void outLoop();
        void inLoop();



    private:
        ContextManager* context_manager;
        void setRenderer(API_TYPE api_type);
        static std::shared_ptr<BaseRenderer> m_renderer;

        static std::shared_ptr<Camera > m_camera;
        Handler* m_handler;
    };

}
#endif //SHM_ENGINE_H
