#ifndef SHM_CONTEXT_MANAGER
#define SHM_CONTEXT_MANAGER

#include "Core.hpp"

namespace SHM{

    class SHM_EXPORT ContextManager{
    public:
        ContextManager(const char* window_name);
        ~ContextManager();

        static void FrameBufferCallback(GLFWwindow* window, int width, int height);
        GLFWwindow* GetWindow() const;
    private:
        void createWindow(uint32_t width, uint32_t height, const char* window_name);
        GLFWwindow* window;

    };

}
#endif  //SHM_CONTEXT_MANAGER