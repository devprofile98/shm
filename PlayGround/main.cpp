#include <iostream>
#include "Engine.hpp"
#include "openGLRenderer.hpp"
#include <chrono>
#include <thread>
#include <memory>

#include <glad/glad.h>

int main(){

    {
        // SHM::Engine *engine = new SHM::Engine{"PlayGround",SHM::OPENGL};
        std::unique_ptr<SHM::Engine> engine{new SHM::Engine{"PlayGround",SHM::OPENGL}};
    }

    std::cout<<"hello from playground"<<std::endl;
    std::cin.get();
    return 0;
}