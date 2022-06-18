#include "birdPhysic.hpp"

BirdPhysic::BirdPhysic(const glm::vec3& center, glm::vec2 velocity) 
    : PHYSICS::WorldObject(center, velocity)
{
}

BirdPhysic::~BirdPhysic(){

}

void BirdPhysic::checkBoundaries(){
    if (centerPosition.y > 8.5 || centerPosition.y < 0){
        isAwake = false;
    }
}