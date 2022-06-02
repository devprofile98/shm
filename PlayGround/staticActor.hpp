#ifndef PLAYGROUND_STATIC_ACTOR_H
#define PLAYGROUND_STATIC_ACTOR_H

#include "Engine.hpp"
#include "Actor.hpp"

class StaticActor : public SHM::Actor {
    public:
        StaticActor();
        virtual ~StaticActor();

        void Load() override;
};


#endif //PLAYGROUND_STATIC_ACTOR_H
