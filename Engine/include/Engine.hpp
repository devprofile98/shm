#define MAKE_SHM_LIB

#include "Core.hpp"
#include <memory>
#include <iostream>
#include <stdint.h>


namespace SHM
{

    enum API_TYPE{

        OPENGL,
        VULKAN
    };

    class SHM_EXPORT Engine{
    public:
        Engine(const char* project_name,API_TYPE api_type);
        ~Engine();

        static std::shared_ptr<BaseRenderer> getRenderer();

        void MainRenderLoop();

    private:
        ContextManager* context_manager;
        void setRenderer(API_TYPE api_type);
        static std::shared_ptr<BaseRenderer> m_renderer;
    };

}