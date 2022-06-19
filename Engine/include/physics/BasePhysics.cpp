#include "BasePhysics.hpp"

namespace SHM::PHYSICS {
    
    PhysicObject::PhysicObject(glm::vec3* center, glm::vec2 velocity, bool moveable)
            : centerPosition(center), velocity(velocity), is_moveable(moveable) 
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