#include "Actor.hpp"

namespace SHM {
    Actor::Actor() {
        std::cout << "Actor class initialized" << std::endl;
    }

    Actor::~Actor(){
        std::cout << "Actor class destroyed" << std::endl;
    }

    void Actor::Load(){
        std::cout << "Actor class loaded" << std::endl;
    }
    
}