#ifndef SHM_PHYSICS_BASE_PHYSIC_H
#define SHM_PHYSICS_BASE_PHYSIC_H

#include "../Core.hpp"

namespace SHM
{
    namespace PHYSICS {
        class PhysicObject{
            public:
                PhysicObject(const glm::vec3& center, glm::vec2 velocity);
                bool isAwake = true;
                glm::vec3 centerPosition; // bounding volume center
                glm::vec2 velocity{0.0f, 0.0f};

                void addVelocity(glm::vec2 v);

                virtual void updatePhysics(float deltatime=0.016f);

            private:
                void generateVertex();
            };
    }
}

#endif //SHM_PHYSICS_BASE_PHYSIC_H