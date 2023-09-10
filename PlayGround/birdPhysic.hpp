#ifndef PLAYGROUND_BIRD_PHYSIC_ACTOR_H
#define PLAYGROUND_BIRD_PHYSIC_ACTOR_H

#include "Engine.hpp"
#include "physics/WorldObject.hpp"
#include "physics/PhysicWorld.hpp"

using namespace SHM;

class BirdPhysic: public PHYSICS::WorldObject{
    public:
        BirdPhysic(glm::vec3* center, glm::vec2 velocity, bool moveable=false);
        ~BirdPhysic();

        void checkBoundaries();
        void updatePhysics(float deltatime=0.016f) override;
};

#endif //PLAYGROUND_BIRD_PHYSIC_ACTOR_H
