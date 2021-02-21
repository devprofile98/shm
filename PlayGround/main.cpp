#include <iostream>
#include "Engine.hpp"
#include <chrono>
#include <thread>
#include <memory>
#include <glad/glad.h>


int main(){

    // SHM::Engine *engine = new SHM::Engine{"PlayGround",SHM::OPENGL};
    std::unique_ptr<SHM::Engine> engine{new SHM::Engine{"PlayGround",SHM::OPENGL}}; // create an instance of Engine

    //load Fragment Shader and Vertex-shader
    engine->getRenderer()->LoadShaders(
                    "/home/ahmad/Documents/projects/cpp/shm/Engine/assets/model_loading.vs",
                    "/home/ahmad/Documents/projects/cpp/shm/Engine/assets/model_loading.fs"
                     );

    // load 3d model
    engine->getRenderer()->LoadModel("/home/ahmad/Downloads/Rubics_cube/cube.obj");

    // main render loop
    engine->MainRenderLoop();

    std::cout<<"Goodbye"<<std::endl;

    return 0;
}
