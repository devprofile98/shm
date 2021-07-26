#include "Engine.hpp"
#include "buffers.hpp"
#include "Light.hpp"
#include "physics.hpp"


namespace SHM {

std::shared_ptr<shader> newShader2 = Engine::CreateShader("F:/project/SHM/PlayGround/assets/second/model_loading.vs", "F:/project/SHM/PlayGround/assets/second/model_loading.fs");
std::shared_ptr<shader> newShader3 = Engine::CreateShader("F:/project/SHM/PlayGround/assets/second/model_loading.vs", "F:/project/SHM/PlayGround/assets/second/model_loading.fs");


    void Engine::outLoop(){
        // write your configuration code to run before Engine::MainRenderLoop

        // link and create shader

        glm::mat4 model = glm::translate(glm::mat4{1.0}, glm::vec3(-3.0, -1.0, -1.0));
        model = glm::translate(model, glm::vec3(10.0, 10.0, 10.0));
        newShader2->createProgram();
        Model *ground = Engine::getRenderer()
                ->LoadModel(
                    "F:/project/SHM/PlayGround/assets/second/untitled.obj",
                    newShader2
                 );
        newShader2->use();
        newShader2->useGlobalVariables();


        newShader3->createProgram();
        Model *ball = Engine::getRenderer()
                ->LoadModel(
                    "F:/project/SHM/PlayGround/assets/second/ball.obj",
                    newShader3
                 );
        newShader3->use();
        newShader3->useGlobalVariables();
        ball->setPosition(glm::vec3{0.0f, 2.0f, 0.0f});
        ball->setScale(glm::vec3{0.02, 0.02, 0.02});

        PointLight pl{{-2,-0.7,3}, {1.0, 1.0, 0.0}};
        PointLight pl2{{1,-0.7,5}, {1.0f, 0.0f, 1.0f}};


        SpotLight sl{{0, -1, 0}, {0,0,0}};
        sl.setDiffuse({0.0f, 0.0f, 1.0f});
        SpotLight sl2{{0, -1, 0}, {-1,1,-1},{0.0f, 1.0f, 0.0f}};
        SpotLight sl3{{0, -1, 0}, {-2,-0.5,-1}};

    }

    void Engine::inLoop(){

//        glm::mat4 model{1.0};
//        model = glm::translate(model, glm::vec3(-1.0, -1.0, -1.0));
//        model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
//        newShader2->use();
//        newShader2->setMat4("model", model);

    }

}
