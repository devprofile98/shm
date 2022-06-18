#ifndef SHM_PHYSICS_WORLD_PHYSICS_H
#define SHM_PHYSICS_WORLD_PHYSICS_H

#include <vector>
#include <iostream>
#include "BasePhysics.hpp"

namespace SHM::PHYSICS {
    class World {
        public:
            World();
            ~World();

            bool registerToPhysics(PhysicObject* object);
            void updateWorld(float duration);

        private:
            std::vector<PhysicObject*> m_all_objects;
    };
}

#endif //SHM_PHYSICS_WORLD_PHYSICS_H