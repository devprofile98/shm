#include "Camera.hpp"


namespace SHM{

    Camera::Camera(glm::vec3 position, glm::vec3 up){
        m_world_up = up;
        m_yaw = -90.0f;
        m_pitch = 0.0f;
        m_position = position;
        m_up = up;
        m_fov = 45.0f;
    }

    Camera::~Camera() {
        delete this->m_internal_position;
        std::cout << "Camera destroyed!" << std::endl;
    }

    void Camera::attachTo(BaseActor* actor, uint8_t attach_mode){
        this->m_attach_mode = attach_mode;
        this->m_internal_position = actor->model->getPosition();
    }

    void Camera::updateCameraPosition() {
        if (m_internal_position == nullptr) return;
        if (m_attach_mode == static_cast<uint8_t>(ATTACH::X)){
            m_position.x = m_internal_position->x;
        }
        else if (m_attach_mode == static_cast<uint8_t>(ATTACH::Y)){
            m_position.y = m_internal_position->y;
        }
        else if (m_attach_mode == static_cast<uint8_t>(ATTACH::Z)){
            m_position.z = m_internal_position->z;
        }
        else if (m_attach_mode == static_cast<uint8_t>(ATTACH::ALL)){
            this->m_position.x = this->m_internal_position->x;
            this->m_position.y = this->m_internal_position->y;
            this->m_position.z = this->m_internal_position->z;
        }
        else if (m_attach_mode == static_cast<uint8_t>(ATTACH::X) | static_cast<uint8_t>(ATTACH::Y)){
            this->m_position.x = this->m_internal_position->x;
            this->m_position.y = this->m_internal_position->y;
        }
        else if (m_attach_mode == static_cast<uint8_t>(ATTACH::X) | static_cast<uint8_t>(ATTACH::Z)){
            this->m_position.x = this->m_internal_position->x;
            this->m_position.z = this->m_internal_position->z;
        }
        else if (m_attach_mode == static_cast<uint8_t>(ATTACH::Y) | static_cast<uint8_t>(ATTACH::Z)){
            this->m_position.y = this->m_internal_position->y;
            this->m_position.z = this->m_internal_position->z;
        }

    }
}
