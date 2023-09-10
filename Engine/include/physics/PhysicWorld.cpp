#include "PhysicWorld.hpp"

namespace SHM::PHYSICS {
    World::World() {
        this->m_all_objects.reserve(200);
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
        for(int first=0; first <= this->m_all_objects.size()-1; first++){
            for (int sec=0; sec <= this->m_all_objects.size()-1; sec++)
            {
                if (first == sec) {
                    continue;
                }
                else if (this->m_all_objects[first]->is_moveable || this->m_all_objects[sec]->is_moveable ) [[likely]] {
                    // check if there is a collision
                    glm::vec2 diff {*(this->m_all_objects[first]->centerPosition) - *(this->m_all_objects[sec]->centerPosition)};
                    if (this->m_all_objects[first]->shape == PHYSICS::OBJECT_SHAPE::CIRCLE) {
                        if (this->m_all_objects[sec]->shape == PHYSICS::OBJECT_SHAPE::RECTANGLE) {
                            glm::vec2 clamped = glm::clamp(diff, glm::vec2(-this->m_all_objects[sec]->halfSize), glm::vec2(this->m_all_objects[sec]->halfSize));
                            glm::vec2 closest = glm::vec2(*(this->m_all_objects[sec]->centerPosition)) + clamped;
                            diff = closest - glm::vec2(*(this->m_all_objects[first]->centerPosition));
                            float result = glm::length(diff);
                            if (result < this->m_all_objects[first]->m_object_radius){
                                this->m_all_objects[first]->isAwake = false;
                            }
                        }
                        else if (this->m_all_objects[sec]->shape == PHYSICS::OBJECT_SHAPE::CIRCLE) {

                        }
                    }
                    else if ((this->m_all_objects[first]->shape == PHYSICS::OBJECT_SHAPE::RECTANGLE)) {
                        if (this->m_all_objects[sec]->shape == PHYSICS::OBJECT_SHAPE::RECTANGLE) {

                        }
                        else if (this->m_all_objects[sec]->shape == PHYSICS::OBJECT_SHAPE::CIRCLE) {

                        }
                    }
                }
            }
        }
    }
}