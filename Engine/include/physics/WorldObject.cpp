#include "WorldObject.hpp"

namespace SHM::PHYSICS {
    WorldObject::WorldObject(const glm::vec3& center, glm::vec2 velocity)
        : PhysicObject(center, velocity)
    {

    }

    WorldObject::~WorldObject(){
        
    }
}