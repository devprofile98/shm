#ifndef PLAYGROUND_BIRD_ACTOR_H
#define PLAYGROUND_BIRD_ACTOR_H

#include "Actor.hpp"
#include "birdPhysic.hpp"

class BirdActor : public SHM::Actor {
  public:
    BirdActor();
    virtual ~BirdActor();

    void setUpModel() override;
    void eachFrame() override;
    void jump() override;
};

#endif // PLAYGROUND_BIRD_ACTOR_H