#include "staticActor.hpp"

StaticActor::StaticActor() {
    SHM::Engine::getRenderer()->m_actors.push_back(this);
    std::cout << "statically called Static actor to add actor" << std::endl;
}

StaticActor::~StaticActor() {
    std::cout << "Static Actor destroyed!" << std::endl;

}

void StaticActor::setUpModel() {}

void StaticActor::eachFrame() {
    // this->model->DrawInstances(pipes_pos, nullptr);

}

void StaticActor::add_pipe_pos(const glm::vec3 &pos){
    pipes_pos.push_back(pos);
}
