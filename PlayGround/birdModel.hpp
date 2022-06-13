#ifndef PLAYGROUND_BIRD_ACTOR_H
#define PLAYGROUND_BIRD_ACTOR_H

#include "Actor.hpp"

class BirdActor : public SHM::Actor {
    public:
        BirdActor();
        virtual ~BirdActor();

        void setUpModel() override;
        void eachFrame() override;

};


#endif //PLAYGROUND_BIRD_ACTOR_H