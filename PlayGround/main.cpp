#include <iostream>
#include "Engine.hpp"
#include <chrono>
#include <thread>
#include <memory>
#include <glad/glad.h>

#include "particle.hpp"


int main(int argc, char *argv[]) {

    {
        // create an instance of Engine
        IND_PATH(argv[0]);
        std::unique_ptr<SHM::Engine> engine{
            new SHM::Engine{"PlayGround", SHM::OPENGL, argv[0]}
        };
        // main render loop
        engine->MainRenderLoop();
    }

    std::cout<<"Goodbye"<<std::endl;
    return 0;
}
