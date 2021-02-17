#include "Camera.hpp"


namespace SHM{

    // Camera::Camera(){

    // }

    Camera::Camera(glm::vec3 position, glm::vec3 up){
        m_world_up = up;
        m_yaw = -90.0f;
        m_pitch = 0.0f;
        m_position = position;
        m_up = up;
    }



}