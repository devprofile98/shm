#ifndef PLAYGROUND_STATIC_ACTOR_H
#define PLAYGROUND_STATIC_ACTOR_H

#include "Engine.hpp"
#include "Actor.hpp"

class StaticActor : public SHM::Actor {
    public:
        StaticActor();
        virtual ~StaticActor();

        void Load() override;

        std::shared_ptr<shader> setShader(const char* v_shader,const char* f_shader ) override;
        std::shared_ptr<shader> setShader(std::shared_ptr<shader>) override;
        std::shared_ptr<shader> getShader();
        int loadModel(const char* file_path) override;
};


#endif //PLAYGROUND_STATIC_ACTOR_H
