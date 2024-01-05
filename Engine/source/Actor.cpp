#include "Actor.hpp"

namespace SHM {

Actor::Actor(const std::string &name) { this->mObjectName = name; }

Actor::~Actor() { delete m_physic_component; }

void Actor::Load() {}

std::shared_ptr<shader> Actor::setShader(const char *v_shader, const char *f_shader) {
    this->m_object_shader = SHM::Engine::GetEngine()->CreateShader(v_shader, f_shader);
    this->m_object_shader->createProgram();
    this->m_object_shader->useGlobalVariables();
    return this->m_object_shader;
}

std::shared_ptr<shader> Actor::setShader(std::shared_ptr<shader> source_shader) {
    this->m_object_shader = source_shader;
    return this->m_object_shader;
}

void Actor::handleInput(KEY key) {
    // override this function and implement your input handling
}

std::shared_ptr<shader> Actor::getShader() { return this->m_object_shader; }

void Actor::loadModel(const char *file_path) {
    this->model = SHM::Engine::GetEngine()->getRenderer()->LoadModel(file_path, this->m_object_shader);
    //   if (this->model) {
    // SHM::Engine::GetEngine()->getRenderer()->m_actors.push_back(this);
    //   }
    // return this->model_id;
}

void Actor::setUpModel() { SHM::Engine::GetEngine()->getRenderer()->m_actors.push_back(this); }

void Actor::eachFrame() {}

std::string Actor::getName() const { return this->mObjectName; }
// void Actor::jump() {}

} // namespace SHM