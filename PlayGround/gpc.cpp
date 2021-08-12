#include "Engine.hpp"
#include "buffers.hpp"
#include "Light.hpp"
#include "chrono"
#include "physics.hpp"


#define GET_MODEL(x) Engine::getRenderer()->getModelByIndex(x)

namespace SHM {

std::shared_ptr<shader> newShader2 = Engine::CreateShader("F:/project/SHM/PlayGround/assets/second/model_loading.vs", "F:/project/SHM/PlayGround/assets/second/model_loading.fs");
std::shared_ptr<shader> newShader3 = Engine::CreateShader("F:/project/SHM/PlayGround/assets/second/model_loading.vs", "F:/project/SHM/PlayGround/assets/second/model_loading.fs");
std::shared_ptr<shader> newShader4 = Engine::CreateShader("F:/project/SHM/PlayGround/assets/second/model_loading.vs", "F:/project/SHM/PlayGround/assets/second/model_loading.fs");

cyclon::Particle parts[4];
cyclon::ParticleGravity g{cyclon::Vector3{0.0f, -1.0f, 0.0f}};
auto now = std::chrono::high_resolution_clock::now();


class TestCyclon{
public:
    TestCyclon(cyclon::Particle* ps)
        :parts(ps)
    {

    }

    ~TestCyclon(){
        delete [] parts;
    }
private:
    cyclon::Particle *parts;
};

void Engine::outLoop(){
    // write your configuration code to run before Engine::MainRenderLoop
    glm::mat4 model = glm::translate(glm::mat4{1.0}, glm::vec3(-3.0, -1.0, -1.0));
    model = glm::translate(model, glm::vec3(10.0, 10.0, 10.0));
    newShader2->createProgram();
    int ground = Engine::getRenderer()
            ->LoadModel(
                "F:/project/SHM/PlayGround/assets/second/untitled.obj",
                newShader2
                );
    newShader2->use();
    newShader2->useGlobalVariables();


    newShader3->createProgram();
    int ball = Engine::getRenderer()
            ->LoadModel(
                "F:/project/SHM/PlayGround/assets/second/cube.obj",
                newShader3
                );
    newShader3->use();
    newShader3->useGlobalVariables();
    GET_MODEL(ball)->setPosition(glm::vec3{0.0f, 2.0f, 0.0f});
    GET_MODEL(ball)->setScale(glm::vec3{0.05, 0.05, 0.05});

    newShader4->createProgram();
    int ball1 = Engine::getRenderer()
            ->LoadModel(
                "F:/project/SHM/PlayGround/assets/second/cube.obj",
                newShader4
                );
    newShader4->use();
    newShader4->useGlobalVariables();
    GET_MODEL(ball1)->setPosition(glm::vec3{0.9f, 2.0f, 0.0f});
    GET_MODEL(ball1)->setScale(glm::vec3{0.05, 0.05, 0.05});

    int ball2 = Engine::getRenderer()
            ->LoadModel(
                "F:/project/SHM/PlayGround/assets/second/cube.obj",
                newShader3
                );
    newShader3->use();
    //    newShader3->useGlobalVariables();
    GET_MODEL(ball2)->setPosition(glm::vec3{0.45f, 2.0f, 0.9f});
    GET_MODEL(ball2)->setScale(glm::vec3{0.05, 0.05, 0.05});


    int ball3 = Engine::getRenderer()
            ->LoadModel(
                "F:/project/SHM/PlayGround/assets/second/cube.obj",
                newShader3
                );
    newShader3->use();
    //    newShader3->useGlobalVariables();
    GET_MODEL(ball3)->setPosition(glm::vec3{0.22f, 2.5f, 0.25f});
    GET_MODEL(ball3)->setScale(glm::vec3{0.05, 0.05, 0.05});


    parts[0].inverseMass = ((cyclon::real)1.0)/2.0f;
    parts[0].velocity = cyclon::Vector3{0.0f, 3.0f, 0.3f};
    parts[0].damping = 0.99f;
    parts[0].setPosition(cyclon::Vector3{
                             GET_MODEL(ball)->getPosition()->x,
                             GET_MODEL(ball)->getPosition()->y,
                             GET_MODEL(ball)->getPosition()->z
                         });


    parts[1].inverseMass = ((cyclon::real)1.0)/2.0f;
    parts[1].velocity = cyclon::Vector3{0.3f, 3.0f, 0.3f};
    parts[1].damping = 0.99f;
    parts[1].setPosition(cyclon::Vector3{
                             GET_MODEL(ball3)->getPosition()->x,
                             GET_MODEL(ball3)->getPosition()->y,
                             GET_MODEL(ball3)->getPosition()->z
                         });

    PointLight pl{{-2,-0.7,3}, {1.0, 1.0, 0.0}};
    PointLight pl2{{1,-0.7,5}, {1.0f, 0.0f, 1.0f}};


    SpotLight sl{{0, -1, 0}, {0,0,0}};
    sl.setDiffuse({0.0f, 0.0f, 1.0f});
    SpotLight sl2{{0, -1, 0}, {-1,1,-1},{0.0f, 1.0f, 0.0f}};
    SpotLight sl3{{0, -1, 0}, {-2,-0.5,-1}};

}

void Engine::inLoop(){

    if (std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::high_resolution_clock::now() - now)
            .count() > 10)
    {
//        std::cout << parts[1].position.x << " "<< parts[1].position.y << " " <<parts[1].position.z<<std::endl;

        g.updateForce(&parts[0], 0.0016f);
        parts[0].integrate(0.0016f);

        Engine::getRenderer()->getModelByIndex(1)->setPosition(
                    glm::vec3(
                        parts[0].position.x,
                    parts[0].position.y,
                parts[0].position.z
                ));


        g.updateForce(&parts[1], 0.0016f);
        parts[1].integrate(0.0016f);
        Engine::getRenderer()->getModelByIndex(4)->setPosition(
                    glm::vec3(
                        parts[1].position.x,
                    parts[1].position.y,
                parts[1].position.z
                ));
    }
}
}


