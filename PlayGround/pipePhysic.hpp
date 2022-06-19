#ifndef PLAYGROUND_BIRD_PHYSIC_ACTOR_H
#define PLAYGROUND_BIRD_PHYSIC_ACTOR_H

#include "physics/WorldObject.hpp"

using namespace SHM;

class PipePhysic: public PHYSICS::WorldObject{
    public:
        PipePhysic(glm::vec3* center, glm::vec2 velocity);
        ~PipePhysic();

};

#endif //PLAYGROUND_BIRD_PHYSIC_ACTOR_H
