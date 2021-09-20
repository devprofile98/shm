#include "Handler.hpp"

namespace SHM {

float Handler::last_x = 1920/2.0;
float Handler::last_y = 1080/2.0;
bool Handler::firstMouse = true;

Handler::Handler(GLFWwindow *window, std::shared_ptr<Camera> camera){
    Handler::camera = camera;
    Handler::firstMouse = true;
    last_frame_time = glfwGetTime();
    glfwSetCursorPosCallback(window, &Handler::mouse);
}

void Handler::keyboard(GLFWwindow *window){

    float now = glfwGetTime();
    float delta_time = now - last_frame_time;
    last_frame_time = now;

    float cameraSpeed = 2.5f * delta_time;

    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS){
        Handler::camera->m_position += cameraSpeed * Handler::camera->m_front;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        Handler::camera->m_position -= cameraSpeed * Handler::camera->m_front;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Handler::camera->m_position -= glm::normalize(glm::cross(Handler::camera->m_front, Handler::camera->m_up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Handler::camera->m_position += glm::normalize(glm::cross(Handler::camera->m_front, Handler::camera->m_up)) * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        this->space_btn->execute();

}


//TODO fix mouse callback function
void Handler::mouse(GLFWwindow *window, double x, double y){
    float xoffset = x - Handler::last_x;
    float yoffset = y - Handler::last_y;

    Handler::last_x = x;
    Handler::last_y = y;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    if (state == GLFW_PRESS)
    {
        Handler::camera->m_yaw +=xoffset;
        Handler::camera->m_pitch += yoffset;

        if (Handler::camera->m_pitch > 89.0f)
            Handler::camera->m_pitch = 89.0f;
        if (Handler::camera->m_pitch < -89.0f)
            Handler::camera->m_pitch = -89.0f;


        glm::vec3 front;
        front.x = cos(glm::radians(Handler::camera->m_yaw)) * cos(glm::radians(Handler::camera->m_pitch));
        front.y = sin(glm::radians(Handler::camera->m_pitch));
        front.z = sin(glm::radians(Handler::camera->m_yaw)) * cos(glm::radians(Handler::camera->m_pitch));
        Handler::camera->m_front = glm::normalize(front);
    }
}

// Camera* SHM::Handler::camera = nullptr;
}
