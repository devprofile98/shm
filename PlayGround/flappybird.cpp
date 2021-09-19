#include "Engine.hpp"
#include "buffers.hpp"
#include "Light.hpp"
#include "chrono"
#include "glm/gtx/string_cast.hpp"
#include "cyclone/cyclone.h"

#define GET_MODEL(x) Engine::getRenderer()->getModelByIndex(x)

namespace SHM {

std::shared_ptr<shader> pipeshader = Engine::CreateShader("F:/project/SHM/PlayGround/assets/second/model_loading.vs", "F:/project/SHM/PlayGround/assets/second/model_loading.fs");
std::shared_ptr<shader> birdshader = Engine::CreateShader("F:/project/SHM/PlayGround/assets/second/model_loading.vs", "F:/project/SHM/PlayGround/assets/second/model_loading.fs");

cyclone::Contact contacts[128];
cyclone::CollisionData cdata;

class Bird : public cyclone::CollisionSphere{
public:
    unsigned startTime;
    Bird(){
        body = new cyclone::RigidBody();
    }
    ~Bird(){delete body;}

    void setState()
    {
        body->setCanSleep(false);
        body->setAwake();

        cyclone::Matrix3 tensor;
        cyclone::real coeff = 0.4f*body->getMass()*radius*radius;
        tensor.setInertiaTensorCoeffs(coeff,coeff,coeff);
        body->setInertiaTensor(tensor);

        // Set the data common to all particle types
        body->setPosition(0.0f, 1.5f, 0.0f);
//        startTime = 1;

        // Clear the force accumulators
        body->calculateDerivedData();
        calculateInternals();
    }
};

Bird birdi;


class Pipe: public cyclone::CollisionBox{
public:
    Pipe(){
        body = new cyclone::RigidBody();
    }
    ~Pipe(){delete body;}

    void setState(const glm::vec3& pos)
    {
        body->setPosition(pos.x, pos.y, pos.z);
        body->setOrientation(1,0,0,0);
        body->setVelocity(0,0,0);
        body->setRotation(cyclone::Vector3(0,0,0));
        halfSize = cyclone::Vector3(1,1,2);

        cyclone::real mass = halfSize.x * halfSize.y * halfSize.z * 8.0f;
        body->setMass(mass);

        cyclone::Matrix3 tensor;
        tensor.setBlockInertiaTensor(halfSize, mass);
        body->setInertiaTensor(tensor);

        body->setLinearDamping(0.95f);
        body->setAngularDamping(0.8f);
        body->clearAccumulators();
        body->setAcceleration(0,-10.0f,0);

        body->setCanSleep(false);
        body->setAwake();

        body->calculateDerivedData();
        calculateInternals();
    }
};

Pipe pipes[128]; // 64 in 2 row, up and down
std::vector<glm::vec3> pipes_pos;




//set out of render-loop config and command
void Engine::outLoop(){
    cdata.contacts = contacts;
    Engine::m_camera->m_position = glm::vec3{2.0f, 4.7f, 11.0f};

    birdi.setState();

    // load pipe
    pipeshader->createProgram();
    int pipe = Engine::getRenderer()
            ->LoadModel(
                "F:/project/SHM/PlayGround/assets/second/pipe.obj",
                pipeshader
                );

    birdshader->createProgram();
    int bird = Engine::getRenderer()
            ->LoadModel(
                "F:/project/SHM/PlayGround/assets/second/bird.obj",
                birdshader
                );
    GET_MODEL(bird)->setPosition({-3.0f, 5.7f, 0.0f});
    birdi.body->setPosition({-3.0f, 5.7f, 0.0f});

    GET_MODEL(bird)->setScale({0.5f, 0.5f, 0.5f});
    GET_MODEL(bird)->setRotation({0.0f, 1.0f, 0.0f});

    // building pipes collider
    float height=0.0f;
    for(int i=0; i <128; i++){
        height = static_cast<float>(std::rand() % 3);

        if (i % 2 == 0){
            pipes[i].setState({static_cast<float>(i*2), height, 0});
            pipes_pos.push_back({static_cast<float>(i*2), height, 0});
        }else{
            pipes[i].setState({static_cast<float>(i*2), 8+height, 0});
            pipes_pos.push_back({static_cast<float>(i*2), 8+height, 0});
        }
    }

}
int frametillexc = 0;
// set in loop config and command
void Engine::inLoop(){
    // for pipe in pipes
    // check collision with the bird
    GET_MODEL(0)->DrawInstances(pipes_pos, nullptr);
    Engine::m_camera->m_front = glm::vec3{0.0f, 0.0f, -1.0f};
    Engine::m_camera->m_position = glm::vec3{GET_MODEL(1)->getPosition()->x, 4.7f, 11.0f};
    GET_MODEL(1)->setPosition({GET_MODEL(1)->getPosition()->x + 0.01, GET_MODEL(1)->getPosition()->y, GET_MODEL(1)->getPosition()->z});
    birdi.body->setPosition({GET_MODEL(1)->getPosition()->x + 0.01, GET_MODEL(1)->getPosition()->y, GET_MODEL(1)->getPosition()->z});
    std::cout << frametillexc++ <<std::endl;

    for(int i=0;i<12;i++){

        if (cyclone::CollisionDetector::boxAndSphere(pipes[i], birdi, &cdata))
        {
//            std::cout << "Collision detected with pipe number "<<std::endl;
        }
    }

}

}
