#include <iostream>
#include "Engine.hpp"
#include <chrono>
#include <thread>
#include <memory>
#include <glad/glad.h>

#include "particle.hpp"

int main(int argc, char *argv[]) {

    std::cout << "Engine starting here ! " << argv[0] << std::endl;
    {
        // create an instance of Engine
        IND_PATH(argv[0]);
        std::shared_ptr<SHM::Engine> engine = SHM::Engine::startEngine("PlayGround", SHM::OPENGL, argv[0]);
        // main render loop
        engine->MainRenderLoop();
    }

    std::cout << "Goodbye" << std::endl;
    return 0;
}
