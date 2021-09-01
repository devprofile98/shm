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
cyclon::Vector3 anchor_pos{0.22f, 5.5f, 0.25f};
cyclon::ParticleAnchorSpring pas{&anchor_pos, 0.99f, 0.5f};
cyclon::ParticleContact contact[1];
cyclon::ParticleRod *rods[4];
cyclon::ParticleContactResolver pc_resolver{4};
bool first_time = true;

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
    GET_MODEL(ground)->setPosition(glm::vec3{0.0f, -1.0f, 0.0f});

    newShader3->createProgram();
    int ball = Engine::getRenderer()
            ->LoadModel(
                "F:/project/SHM/Engine/assets/wooden watch tower23.obj",
                newShader3
                );
    newShader3->use();
    newShader3->useGlobalVariables();
    GET_MODEL(ball)->setPosition(glm::vec3{0.0f, -1.0f, 2.0f});/*-1.0f, 1.0f, 3.0f*/
    GET_MODEL(ball)->setScale(glm::vec3{0.5, 0.5, 0.5});

    newShader4->createProgram();
    int ball1 = Engine::getRenderer()
            ->LoadModel(
                "F:/project/SHM/PlayGround/assets/second/cube.obj",
                newShader4
                );
    newShader4->use();
    newShader4->useGlobalVariables();
    GET_MODEL(ball1)->setPosition(glm::vec3{-4.0f, 1.0f, -3.0f});
    GET_MODEL(ball1)->setScale(glm::vec3{0.5, 0.5, 0.5});
    GET_MODEL(ball1)->setRotation(glm::vec3{10.0f});

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
    GET_MODEL(ball3)->setPosition(glm::vec3{0.22f, 4.5f, 0.25f});
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
    parts[1].velocity = cyclon::Vector3{0.0f, 0.0f, 0.0f};
    parts[1].damping = 0.99f;
    parts[1].setPosition(cyclon::Vector3{
                             GET_MODEL(ball3)->getPosition()->x,
                             GET_MODEL(ball3)->getPosition()->y,
                             GET_MODEL(ball3)->getPosition()->z
                         });
    parts[2].inverseMass = ((cyclon::real)1.0)/2.0f;
    parts[2].velocity = cyclon::Vector3{0.0f, 0.0f, 0.0f};
    parts[2].damping = 0.99f;
    parts[2].setPosition(cyclon::Vector3{
                             GET_MODEL(ball2)->getPosition()->x,
                             GET_MODEL(ball2)->getPosition()->y,
                             GET_MODEL(ball2)->getPosition()->z
                         });

    rods[0] = new cyclon::ParticleRod{2.592337};
    rods[0]->particle[0] = &parts[1];
    rods[0]->particle[1] = &parts[2];
    rods[0]->fillContact(&contact[0], 1);

    PointLight pl{{-2,1,3}, {1.0, 1.0, 0.0}};
    PointLight pl2{{1,1,5}, {1.0f, 0.0f, 1.0f}};


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
//        if (first_time){
//            first_time = !first_time;
//            Engine::saveImage("shadow.png");
//        }

//        parts[2].integrate(0.0016f);
//        GET_MODEL(3)->setPosition(
//                    glm::vec3(
//                        parts[2].position.x,
//                    parts[2].position.y,
//                parts[2].position.z
//                ));

//        pas.updateForce(&parts[1], 0.0016);
//        parts[1].integrate(0.0016f);
//        GET_MODEL(4)->setPosition(
//                    glm::vec3(
//                        parts[1].position.x,
//                    parts[1].position.y,
//                parts[1].position.z
//                ));

//        pc_resolver.resolveContacts(contact, 1, 0.0016);

    }

    GET_MODEL(2)->setPosition(glm::vec3{sin((float)glfwGetTime()) * 5 , 2.0f, 0.0f});
}
}


