#include "BasePhysics.hpp"

namespace SHM::PHYSICS {
    
    PhysicObject::PhysicObject(const glm::vec3& center, glm::vec2 velocity)
            : centerPosition(center), velocity(velocity)
    {

    }

    void PhysicObject::addVelocity(glm::vec2 v){
        velocity += v;
    }

    void PhysicObject::updatePhysics(float deltatime){

    }

    void PhysicObject::generateVertex(){

    }
}