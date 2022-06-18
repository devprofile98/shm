#ifndef SHM_PHYSICS_WORLD_OBJECT_H
#define SHM_PHYSICS_WORLD_OBJECT_H

#include "BasePhysics.hpp"

namespace SHM::PHYSICS {   
    class WorldObject : public PhysicObject {
        public:
            WorldObject(const glm::vec3& center, glm::vec2 velocity);
            ~WorldObject();
    };
}

#endif //SHM_PHYSICS_WORLD_OBJECT_H