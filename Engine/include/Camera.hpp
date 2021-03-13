#ifndef SHM_OPENGL_CAMERA_H
#define SHM_OPENGL_CAMERA_H

#include <Core.hpp>

namespace SHM {

    class Camera{
        public:
        Camera(glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f), 
               glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f));

            glm::vec3 m_position;
            glm::vec3 m_up;
            glm::vec3 m_front;
            glm::vec3 m_right;
            glm::vec3 m_world_up;
            float m_fov;
            float m_yaw;
            float m_pitch;

        private:

    };

}

#endif //SHM_OPENGL_CAMERA_H
