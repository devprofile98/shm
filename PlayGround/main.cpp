#include <iostream>
#include "Engine.hpp"
#include <chrono>
#include <thread>
#include <memory>
#include <glad/glad.h>

#include "particle.hpp"


int main(){

    // SHM::Engine *engine = new SHM::Engine{"PlayGround",SHM::OPENGL};
    {
        std::unique_ptr<SHM::Engine> engine{new SHM::Engine{"PlayGround", SHM::OPENGL}}; // create an instance of Engine
        //load Fragment Shader and Vertex-shader
//        engine->getRenderer()->LoadShaders(
//                    "F:/project/SHM/Engine/assets/model_loading.vs",
//                    "F:/project/SHM/Engine/assets/model_loading.fs"
//                    );
//        engine->getRenderer()->shader_program.useGlobalVariables();
//        // load 3d model
//        engine->getRenderer()->LoadModel("F:/project/SHM/Engine/assets/wooden watch tower23.obj");

        // main render loop
        engine->MainRenderLoop();
    }

    std::cout<<"Goodbye"<<std::endl;
    return 0;
}
