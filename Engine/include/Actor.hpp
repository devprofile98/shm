// #define SHM_ENGINE_ACTOR_H
#ifndef SHM_ENGINE_ACTOR_H
#define SHM_ENGINE_ACTOR_H

#include <iostream>
#include "Engine.hpp"
#include "BaseActor.hpp"
#include "physics/BasePhysics.hpp"


namespace SHM {
    class Actor: public BaseActor {
        public:
            Actor();
            virtual ~Actor();
            virtual void Load();
            std::shared_ptr<shader> setShader(const char* v_shader,const char* f_shader ) override;
            std::shared_ptr<shader> setShader(std::shared_ptr<shader>) override;
            std::shared_ptr<shader> getShader();
            void loadModel(const char* file_path) override;
            void setUpModel() override;
            void eachFrame() override;

            PHYSICS::PhysicObject* m_physic_component=nullptr;


    };
}

#endif SHM_ENGINE_ACTOR_H