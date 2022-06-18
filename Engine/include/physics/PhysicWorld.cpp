#include "PhysicWorld.hpp"

namespace SHM::PHYSICS {
    World::World() {
        this->m_all_objects.reserve(40);
        std::cout << "Physic World Created!" << std::endl;
    }

    World::~World() {
        std::cout << "Physic World Deconstructed!" << std::endl;
    }

    bool World::registerToPhysics(PhysicObject* object) {
        this->m_all_objects.push_back(object);
        return true;
    }

    void World::updateWorld(float duration){
        // do the calculation here and update physicObjects props
    }

}