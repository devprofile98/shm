#include "WorldObject.hpp"

namespace SHM::PHYSICS {
    WorldObject::WorldObject(glm::vec3* center, glm::vec2 velocity, bool moveable)
        : PhysicObject(center, velocity, moveable)
    {
        
    }

    WorldObject::~WorldObject(){
        
    }
}