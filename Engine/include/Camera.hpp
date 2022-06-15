#ifndef SHM_OPENGL_CAMERA_H
#define SHM_OPENGL_CAMERA_H

#include <Core.hpp>
#include "BaseActor.hpp"

namespace SHM {

    class Camera{

        public:

            enum class ATTACH{
                X=1,
                Y=2,
                Z=4,
                ALL=7
            };

            Camera(glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f));
            ~Camera();

            glm::vec3 m_position;
            glm::vec3 m_up;
            glm::vec3 m_front;
            glm::vec3 m_right;
            glm::vec3 m_world_up;
            float m_fov;
            float m_yaw;
            float m_pitch;

            void attachTo(BaseActor* actor, uint8_t attach = 0);
            void updateCameraPosition();

        private:
            const glm::vec3 * m_internal_position;
            uint8_t m_attach_mode = 0;
    };

}

#endif //SHM_OPENGL_CAMERA_H
