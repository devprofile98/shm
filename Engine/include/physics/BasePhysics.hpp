#ifndef SHM_PHYSICS_BASE_PHYSIC_H
#define SHM_PHYSICS_BASE_PHYSIC_H

#include "../Core.hpp"

namespace SHM
{
    namespace PHYSICS {

        enum class OBJECT_SHAPE {
            CIRCLE,
            RECTANGLE,

            // to be implemented
            // SPHERE
            // CUBE
        };

        class PhysicObject{
            public:
                PhysicObject(glm::vec3* center, glm::vec2 velocity, bool moveable = false);
                bool isAwake = true;
                glm::vec3* centerPosition; // bounding volume center
                glm::vec2 velocity{0.0f, 0.0f};
                glm::vec3 halfSize{0.0f, 0.0f, 0.0f};
                bool is_moveable;
                float m_object_radius = 0.0f;
                void addVelocity(glm::vec2 v);

                OBJECT_SHAPE shape;

                virtual void updatePhysics(float deltatime=0.016f);

            private:
                void generateVertex();
            };
    }
}

#endif //SHM_PHYSICS_BASE_PHYSIC_H