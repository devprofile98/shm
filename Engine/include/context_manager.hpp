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

        virtual void processInput();

        float deltaTime= 0.5f;
        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f,  10.0f);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    private:
        void createWindow(uint32_t width, uint32_t height, const char* window_name);
        GLFWwindow* window;

    };

}
#endif  //SHM_CONTEXT_MANAGER