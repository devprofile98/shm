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

            virtual std::shared_ptr<shader> setShader(const char*, const char*)=0;
            virtual std::shared_ptr<shader> setShader(std::shared_ptr<shader>)=0;
            virtual std::shared_ptr<shader> getShader()=0;
            virtual int loadModel(const char* file_path)=0;

    };
}

#endif SHM_ENGINE_ACTOR_H