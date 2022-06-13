#include "Actor.hpp"

namespace SHM {

    Actor::Actor() {
        // SHM::Engine::getRenderer()->m_actors.push_back(this);
        std::cout << "statically called Static actor to add actor" << std::endl;
    }

    Actor::~Actor() {}

    void Actor::Load() {}

    std::shared_ptr<shader> Actor::setShader(const char* v_shader, const char* f_shader) {
        this->m_object_shader = SHM::Engine::CreateShader( v_shader, f_shader);
        this->m_object_shader->createProgram();
        this->m_object_shader->useGlobalVariables();
        return this->m_object_shader;
    }


    std::shared_ptr<shader> Actor::setShader(std::shared_ptr<shader> source_shader) {
        this->m_object_shader = source_shader;
        return this->m_object_shader;
    }

    std::shared_ptr<shader> Actor::getShader(){
        return this->m_object_shader;
    }

    void Actor::loadModel(const char* file_path){
        this->model = SHM::Engine::getRenderer()->LoadModel(file_path, this->m_object_shader);
        // return this->model_id;
    }

    void Actor::setUpModel(){

    }

    void Actor::eachFrame(){
        
    }

}