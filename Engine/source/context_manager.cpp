#include "context_manager.hpp"
#include "Logger.hpp"
namespace SHM {

ContextManager::ContextManager(const char *window_name) { createWindow(1920, 1080, window_name); }

ContextManager::~ContextManager() {
    delete window;
    glfwTerminate();
}

void ContextManager::FrameBufferCallback(GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); }

// create glfw window and return it
void ContextManager::createWindow(uint32_t width, uint32_t height, const char *window_name) {
    // glfw init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    int major, minor;

    window = glfwCreateWindow(width, height, "SHM", NULL, NULL);
    if (window == nullptr) {
        SHM::Logger::error("Failed to create GLFW window");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // remove glfw 60fps limit
    glfwSetFramebufferSizeCallback(window, &ContextManager::FrameBufferCallback);
    // glfwSetCursorPosCallback(window, mouse_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        SHM::Logger::error("Failed to initialize GLAD");
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    // configure global opengl state
    // -----------------------------
    // glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    std::string vendor = (const char *)glGetString(GL_VENDOR);
    SHM::Logger::info("OpenGL context created v{}.{} on {} platform.", major, minor, vendor);

    // glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

GLFWwindow *ContextManager::GetWindow() const { return this->window; }

void ContextManager::processInput() {
    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

} // namespace SHM
