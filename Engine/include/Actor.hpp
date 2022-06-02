#ifndef SHM_ENGINE_ACTOR_H
#define SHM_ENGINE_ACTOR_H

#include "BaseActor.hpp"
#include <iostream>

namespace SHM {
    class Actor: public BaseActor {
        public:
            Actor();
            virtual ~Actor();

            virtual void Load();
    };
}

#endif SHM_ENGINE_ACTOR_H