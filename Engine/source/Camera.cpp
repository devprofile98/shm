#include "Camera.hpp"

namespace SHM {

Camera::Camera(glm::vec3 position, glm::vec3 up) : m_front(glm::vec3(0.0f, 0.0f, -1.0f)) {
    m_world_up = up;
    m_yaw = -90.0f;
    m_pitch = 0.0f;
    m_position = position;
    m_up = up;
    m_fov = 45.0f;
    m_right = glm::cross(m_front, m_up);
    m_internal_position = new glm::vec3{0.0, 0.0, 0.0};
}

Camera::~Camera() {
    delete this->m_internal_position;
    std::cout << "Camera destroyed!" << std::endl;
}

void Camera::move(SHM::Movement movement) {
    m_right = glm::cross(m_front, m_up);
    if (movement == SHM::Movement::Forward) {
        this->m_position += glm::vec3{m_front.x / 5, m_front.y / 5, m_front.z / 5};
    } else if (movement == SHM::Movement::Backward) {
        this->m_position += glm::vec3{-m_front.x / 5, -m_front.y / 5, -m_front.z / 5};
    } else if (movement == SHM::Movement::Right) {
        this->m_position += glm::vec3{m_right.x / 5, m_right.y / 5, m_right.z / 5};
    } else if (movement == SHM::Movement::Left) {
        this->m_position += glm::vec3{-m_right.x / 5, -m_right.y / 5, -m_right.z / 5};
    }
}

void Camera::attachTo(BaseActor *actor, ATTACH attach_mode) {
    this->m_attach_mode = attach_mode;
    this->m_internal_position = actor->model->getPosition();
}

void Camera::updateCameraPosition() {
    if (m_internal_position == nullptr || this->m_attach_mode == ATTACH::None) {
        return;
    }
    if (m_attach_mode == ATTACH::X) {
        m_position.x = m_internal_position->x;
    } else if (m_attach_mode == ATTACH::Y) {
        m_position.y = m_internal_position->y;
    } else if (m_attach_mode == ATTACH::Z) {
        m_position.z = m_internal_position->z;
    } else if (m_attach_mode == ATTACH::All) {
        this->m_position.x = this->m_internal_position->x;
        this->m_position.y = this->m_internal_position->y;
        this->m_position.z = this->m_internal_position->z;
    } else if (m_attach_mode == ATTACH::X | m_attach_mode == ATTACH::Y) {
        this->m_position.x = this->m_internal_position->x;
        this->m_position.y = this->m_internal_position->y;
    } else if (m_attach_mode == ATTACH::X | m_attach_mode == ATTACH::Z) {
        this->m_position.x = this->m_internal_position->x;
        this->m_position.z = this->m_internal_position->z;
    } else if (m_attach_mode == ATTACH::Y | m_attach_mode == ATTACH::Z) {
        this->m_position.y = this->m_internal_position->y;
        this->m_position.z = this->m_internal_position->z;
    }
}
} // namespace SHM
