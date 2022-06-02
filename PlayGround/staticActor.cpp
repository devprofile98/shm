#include "staticActor.hpp"

StaticActor::StaticActor() {
    SHM::Engine::getRenderer()->m_actors.push_back(this);
    std::cout << "statically called Static actor to add actor" << std::endl;
}

StaticActor::~StaticActor() {}

void StaticActor::Load() {}
