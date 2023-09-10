#include "birdPhysic.hpp"

BirdPhysic::BirdPhysic(glm::vec3 *center, glm::vec2 velocity, bool moveable) : PHYSICS::WorldObject(center, velocity, moveable) {
    this->shape = PHYSICS::OBJECT_SHAPE::CIRCLE;
    this->m_object_radius = 1.0f;
    SHM::Engine::GetEngine()->getPhysicWorld()->registerToPhysics(this);
}

BirdPhysic::~BirdPhysic() {}

void BirdPhysic::checkBoundaries() {
    if (centerPosition->y > 8.5 || centerPosition->y < 0) {
        isAwake = false;
    }
}

void BirdPhysic::updatePhysics(float deltatime){
}