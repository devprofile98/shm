#include "pipePhysic.hpp"

PipePhysic::PipePhysic(glm::vec3* center, glm::vec2 velocity) 
    : PHYSICS::WorldObject(center, velocity)
{
    this->shape = PHYSICS::OBJECT_SHAPE::RECTANGLE;
}

PipePhysic::~PipePhysic(){

}