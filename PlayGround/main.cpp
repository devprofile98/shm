#include <iostream>
#include "Engine.hpp"
// #include "openGLRenderer.hpp"
#include <chrono>
#include <thread>
#include <memory>

#include <glad/glad.h>

int main(){


    // SHM::Engine *engine = new SHM::Engine{"PlayGround",SHM::OPENGL};
    std::unique_ptr<SHM::Engine> engine{new SHM::Engine{"PlayGround",SHM::OPENGL}};
    engine->getRenderer()->LoadShaders(
                    "F:/project/GameEngine/learnOPENGL/shaders/model_loading.vs",
                    "F:/project/GameEngine/learnOPENGL/shaders/model_loading.fs"
                     );
    engine->getRenderer()->LoadModel("F:/project/GameEngine/learnOPENGL/resources/DONATE2.obj");
    engine->MainRenderLoop();
    std::cout<<"hello from playground"<<std::endl;

    return 0;
}
