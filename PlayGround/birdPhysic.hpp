#ifndef PLAYGROUND_BIRD_PHYSIC_ACTOR_H
#define PLAYGROUND_BIRD_PHYSIC_ACTOR_H

#include "physics/WorldObject.hpp"

using namespace SHM;

class BirdPhysic: public PHYSICS::WorldObject{
    public:
        BirdPhysic(const glm::vec3& center, glm::vec2 velocity);
        ~BirdPhysic();

        void checkBoundaries();
};

#endif //PLAYGROUND_BIRD_PHYSIC_ACTOR_H
