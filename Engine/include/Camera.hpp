#ifndef SHM_OPENGL_CAMERA_H
#define SHM_OPENGL_CAMERA_H

#include "Core.hpp"
#include "BaseActor.hpp"

namespace SHM {

enum class Movement {
    Forward,
    Backward,
    Right,
    Left,
    Upward,
    Downward,
};

class Camera {

  public:
    enum class ATTACH : uint8_t { None = 0, X = 1, Y = 2, Z = 4, All = 7 };

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
    ~Camera();

    glm::vec3 m_position;
    glm::vec3 m_up;
    glm::vec3 m_front;
    glm::vec3 m_right;
    glm::vec3 m_world_up;
    float m_fov;
    float m_yaw;
    float m_pitch;

    void attachTo(BaseActor *actor, ATTACH attach = ATTACH::None);
    void updateCameraPosition();
    void move(Movement movement);

  private:
    glm::vec3 *m_internal_position;
    ATTACH m_attach_mode = ATTACH::None;
};

} // namespace SHM

#endif // SHM_OPENGL_CAMERA_H
