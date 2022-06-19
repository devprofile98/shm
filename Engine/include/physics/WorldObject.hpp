#ifndef SHM_PHYSICS_WORLD_OBJECT_H
#define SHM_PHYSICS_WORLD_OBJECT_H

#include "BasePhysics.hpp"

namespace SHM::PHYSICS {   
    class WorldObject : public PhysicObject {
        public:
            WorldObject(glm::vec3* center, glm::vec2 velocity, bool moveable=false);
            ~WorldObject();
    };
}

#endif //SHM_PHYSICS_WORLD_OBJECT_H