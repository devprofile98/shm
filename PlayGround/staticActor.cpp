#include "staticActor.hpp"

StaticActor::StaticActor() {
    SHM::Engine::getRenderer()->m_actors.push_back(this);
    std::cout << "statically called Static actor to add actor" << std::endl;
}

StaticActor::~StaticActor() {}

void StaticActor::Load() {}

std::shared_ptr<shader> StaticActor::setShader(const char* v_shader, const char* f_shader) {
    this->m_object_shader = SHM::Engine::CreateShader( v_shader, f_shader);
    this->m_object_shader->createProgram();
    this->m_object_shader->useGlobalVariables();
    return this->m_object_shader;
}


std::shared_ptr<shader> StaticActor::setShader(std::shared_ptr<shader> source_shader) {
    this->m_object_shader = source_shader;
    return this->m_object_shader;
}

std::shared_ptr<shader> StaticActor::getShader(){
    return this->m_object_shader;
}

int StaticActor::loadModel(const char* file_path){
    this->model_id = SHM::Engine::getRenderer()->LoadModel(file_path, this->m_object_shader);
    return this->model_id;
}

