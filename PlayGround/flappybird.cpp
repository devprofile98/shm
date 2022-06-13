#include "Engine.hpp"
#include "buffers.hpp"
#include "Light.hpp"
#include "chrono"
#include "glm/gtx/string_cast.hpp"
#include "staticActor.hpp"
#include "birdModel.hpp"

#define GET_MODEL(x) Engine::getRenderer()->getModelByIndex(x)
#define REGISTER_MODEL(x) Engine::getRenderer()->registerModel(x)

namespace SHM {

// std::shared_ptr<shader> line_shader = Engine::CreateShader("/assets/vert.vs", "/assets/frag.fs");

float vertices[] = {
    0.0f, 0.0f, 0.0f, // 0
    0.0f, 0.0f, -1.0f, // 1
    1.0f, 0.0f ,-1.0f, // 2
    1.0f, 0.0f, 0.0   // 3
};

float element[] = {
    0,1,
    1,2,
    2,3,
    3,0
};

uint32_t vao, vbo, ebo;

// declaring physic objects
// --------------------------------------------
class PhysicObject{
public:
    PhysicObject(const glm::vec3& center, glm::vec2 velocity)
        : centerPosition(center), velocity(velocity)
    {}
    bool isAwaik = true;
    glm::vec3 centerPosition; // bounding volume center
    glm::vec2 velocity{0.0f, 0.0f};
    void addVelocity(glm::vec2 v){
        velocity += v;
    }

    virtual void updatePhysics(float deltatime=0.016f){};

private:
    void generateVertex(){
    }

};

// represent bird as a circle bounding volume
//--------------------------------------------
class Bird : public PhysicObject{
public:
    Bird(const glm::vec3& center={0.0f, 0.0f, 0.0f}, glm::vec2 velocity={0.0f, 0.0f}, float radius=1.0f)
        :PhysicObject(center, velocity), radius(radius){}

    float radius;

    void calculateVelocity(float deltatime){
        //        centerPosition.x = -20 * deltatime * deltatime + velocity.x * deltatime + centerPosition.x;
        centerPosition.x += 0.01;
        centerPosition.y = -30 * deltatime * deltatime + velocity.y * deltatime + centerPosition.y;
        velocity.y = -30 * deltatime + velocity.y;
    }

    void checkBoundaries(){
        if (centerPosition.y > 8.5 || centerPosition.y < 0){
            isAwaik = false;
        }
    }

    void updatePhysics(float deltatime) override{
        checkBoundaries();
        if (isAwaik)
            calculateVelocity(deltatime);
    }
};

// represent Pipes as boxes
// ------------------------------------------
class Pipe : public PhysicObject{
public:
    Pipe(const glm::vec3& center={0.0f, 0.0f, 0.0f}, const glm::vec3& halfSize ={1.0, 2.0f, 0.0f})
        :PhysicObject(center, {0.0f, 0.0f}), halfSize(halfSize)
    {}

    glm::vec3 halfSize;
};

// represent common functionality for game
// ------------------------------------------
class GameApplication{
public:
    // detect collisions
    bool detectCollisions(Bird *b, Pipe *p){
        // rectangle and circle detection
        glm::vec2 diff{b->centerPosition - p->centerPosition};
        //        glm::vec2 diff{center - p->center};
        glm::vec2 clamped = glm::clamp(diff, glm::vec2(-p->halfSize), glm::vec2(p->halfSize));
        glm::vec2 closest = glm::vec2(p->centerPosition) + clamped;
        diff= closest - glm::vec2(b->centerPosition);
        float result = glm::length(diff);
        return result < b->radius;
    };
};

GameApplication game;
Pipe *pipes = new Pipe[128];
Bird birdi;

// space button --- > add velocity to y axis
// -----------------------------------------
void spacebtn(){
}

// define action for space button
// -----------------------------------------
class JumpAction: public Command{
public:
    virtual void execute() override{
//        std::cout << "space pressed"<<std::endl;
//        spacebtn();
    };
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
//        birdi.velocity += glm::vec2{0.0f, 3.0f};
        if (birdi.velocity.y < 0){
           birdi.velocity.y = 4;
        }
           else {
            birdi.addVelocity({0.0f, 3.0f});
           }

    }
}

//set out of render-loop config and command
void Engine::outLoop(GLFWwindow* window){
    Engine::m_camera->m_position = glm::vec3{2.0f, 4.7f, 11.0f};
    glfwSetKeyCallback(window, key_callback);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(float)*3,0);
    //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    // prepare bird

    static StaticActor pipe{};
    pipe.setShader("/assets/second/model_loading.vs", "/assets/second/model_loading.fs");
    pipe.loadModel(std::string{ Engine::cwd + "/assets/second/texturedpipe.obj"}.c_str());

    static BirdActor bird_object{};
    bird_object.setShader(pipe.getShader());
    bird_object.loadModel(std::string{ Engine::cwd + "/assets/second/texturedbird.obj"}.c_str());

    // GET_MODEL(bird)->setPosition({-3.0f, 5.7f , 0.0f});
    birdi.centerPosition = glm::vec3{-3.0f, 5.7f , 0.0f};
    // GET_MODEL(bird)->setScale({0.5f, 0.5f, 0.5f});
    // GET_MODEL(bird)->setRotation({0.0f, 1.0f, 0.0f});
    // GET_MODEL(bird)->setRotation({0.0f , -1.0f, 0.0f});


    // StaticActor wing_object{};
    // wing_object.setShader(pipe.getShader());
    // int wing = wing_object.loadModel(std::string{ Engine::cwd + "/assets/second/texturedwing.obj"}.c_str());

    // GET_MODEL(wing)->setScale({0.75f, 0.75f, 0.75f});
    // GET_MODEL(wing)->setRotation({0.0, 1.0, 0.0}, 1.0f);


    // building pipes collider
    float height=0.0f;
    for(int i=0; i <128; i++){
        height = static_cast<float>(std::rand() % 3);

        if (i % 2 == 0){
            pipes[i].centerPosition = glm::vec3{static_cast<float>(i*2), height, 0};
            pipes[i].halfSize = glm::vec3{0.95, 2.4f, 0.0};
            // pipes_pos.push_back({static_cast<float>(i*2), height, 0});
            pipe.add_pipe_pos({static_cast<float>(i*2), height, 0});
        }else{
            pipes[i].centerPosition = glm::vec3{static_cast<float>(i*2), 9+height, 0};
            pipes[i].halfSize = glm::vec3{0.95, 2.4f, 0.0};
            // pipes_pos.push_back({static_cast<float>(i*2), 9+height, 0});
            pipe.add_pipe_pos({static_cast<float>(i*2), 9+height, 0});
        }
    }

}

// set in loop config and command
void Engine::inLoop(){
    // for pipe in pipes
    // check collision with the bird
    // GET_MODEL(0)->DrawInstances(pipes_pos, nullptr);
    Engine::m_camera->m_front = glm::vec3{0.0f, 0.0f, -1.0f};
    // Engine::m_camera->m_position = glm::vec3{GET_MODEL(1)->getPosition()->x, 4.7f, 11.0f};
    // //    birdi.centerPosition = glm::vec3{GET_MODEL(1)->getPosition()->x, GET_MODEL(1)->getPosition()->y, GET_MODEL(1)->getPosition()->z};
    // GET_MODEL(1)->setPosition({birdi.centerPosition.x, birdi.centerPosition.y, birdi.centerPosition.z});
    // GET_MODEL(2)->setPosition({birdi.centerPosition.x, birdi.centerPosition.y, birdi.centerPosition.z + birdi.radius/2});
    // GET_MODEL(2)->setRotation({0.0, 1.0, 0.0}, 1.0f);
    // for (int i=0; i<128;i++)
    //     if (game.detectCollisions(&birdi, &pipes[i])){
    //         birdi.isAwaik = false;
    //     }

    birdi.updatePhysics(0.009);
}

}
