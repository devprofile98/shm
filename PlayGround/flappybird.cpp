#include "Engine.hpp"
#include "buffers.hpp"
#include "Light.hpp"
#include "chrono"
#include "glm/gtx/string_cast.hpp"

#define GET_MODEL(x) Engine::getRenderer()->getModelByIndex(x)

namespace SHM {

std::shared_ptr<shader> pipeshader = Engine::CreateShader("F:/project/SHM/PlayGround/assets/second/model_loading.vs", "F:/project/SHM/PlayGround/assets/second/model_loading.fs");
std::shared_ptr<shader> birdshader = Engine::CreateShader("F:/project/SHM/PlayGround/assets/second/model_loading.vs", "F:/project/SHM/PlayGround/assets/second/model_loading.fs");
std::shared_ptr<shader> line_shader = Engine::CreateShader("F:/project/SHM/PlayGround/assets/vert.vs", "F:/project/SHM/PlayGround/assets/frag.fs");

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

    void updatePhysics(float deltatime) override{
//        centerPosition.x = -20 * deltatime * deltatime + velocity.x * deltatime + centerPosition.x;
        centerPosition.y = -30 * deltatime * deltatime + velocity.y * deltatime + centerPosition.y;
        velocity.y = -30 * deltatime + velocity.y;
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

//    void keyboard(){
//        if (glfwGetKey(Engine)
//    }
};

GameApplication game;
Pipe *pipes = new Pipe[128];
std::vector<glm::vec3> pipes_pos; // list of all pipes position in game
Bird birdi;


//set out of render-loop config and command
void Engine::outLoop(){
    Engine::m_camera->m_position = glm::vec3{2.0f, 4.7f, 11.0f};

    // set line prop
    line_shader->createProgram();
    line_shader->use();
    line_shader->useGlobalVariables();
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

//    glGenBuffers(1, &ebo);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(element), &element, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(float)*3,0);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    // prepare bird

    // load pipe
    pipeshader->createProgram();
    pipeshader->useGlobalVariables();
    int pipe = Engine::getRenderer()
            ->LoadModel(
                "F:/project/SHM/PlayGround/assets/second/pipe.obj",
                pipeshader
                );
//    GET_MODEL(pipe)->setScale({1.0, 4.0, 1.0});

    birdshader->createProgram();
    birdshader->useGlobalVariables();
    int bird = Engine::getRenderer()
            ->LoadModel(
                "F:/project/SHM/PlayGround/assets/second/bird.obj",
                birdshader
                );
    GET_MODEL(bird)->setPosition({-3.0f, 5.7f , 0.0f});
    birdi.centerPosition = glm::vec3{-3.0f, 5.7f , 0.0f};
    GET_MODEL(bird)->setScale({0.5f, 0.5f, 0.5f});
    GET_MODEL(bird)->setRotation({0.0f, 1.0f, 0.0f});
    GET_MODEL(bird)->setRotation({0.0f , -1.0f, 0.0f});

    // building pipes collider
    float height=0.0f;
    for(int i=0; i <128; i++){
        height = static_cast<float>(std::rand() % 3);

        if (i % 2 == 0){
            pipes[i].centerPosition = glm::vec3{static_cast<float>(i*2), height, 0};
            pipes[i].halfSize = glm::vec3{0.95, 2.4f, 0.0};
            pipes_pos.push_back({static_cast<float>(i*2), height, 0});
        }else{
            pipes[i].centerPosition = glm::vec3{static_cast<float>(i*2), 9+height, 0};
            pipes[i].halfSize = glm::vec3{0.95, 2.4f, 0.0};
            pipes_pos.push_back({static_cast<float>(i*2), 9+height, 0});
        }
    }

}

// set in loop config and command
void Engine::inLoop(){
    // for pipe in pipes
    // check collision with the bird
    GET_MODEL(0)->DrawInstances(pipes_pos, nullptr);
//    Engine::m_camera->m_front = glm::vec3{0.0f, 0.0f, -1.0f};
//    Engine::m_camera->m_position = glm::vec3{GET_MODEL(1)->getPosition()->x, 4.7f, 11.0f};
//    birdi.centerPosition = glm::vec3{GET_MODEL(1)->getPosition()->x, GET_MODEL(1)->getPosition()->y, GET_MODEL(1)->getPosition()->z};
    GET_MODEL(1)->setPosition({birdi.centerPosition.x, birdi.centerPosition.y, birdi.centerPosition.z});

    for (int i=0; i<128;i++)
        if (game.detectCollisions(&birdi, &pipes[i])){
            std::cout << "collision detected with " << i << std::endl;
            std::cout << glm::to_string(birdi.centerPosition - pipes[i].centerPosition) <<std::endl;
        }
    line_shader->use();
    glBindVertexArray(vao);
    glm::mat4 model{1.0};
    model = glm::translate(model, glm::vec3{pipes[7].centerPosition.x, pipes[7].centerPosition.y + pipes[7].halfSize.y, pipes[7].centerPosition.z+2.0f});
    model = glm::scale(model, glm::vec3{1, 1, 1});
    line_shader->setMat4("projection", Engine::getRenderer()->getProjectionMatrix());
    line_shader->setMat4("view", Engine::getRenderer()->getViewMatrix());
    line_shader->setMat4("model", model);

    glDrawArrays(GL_POINTS,0, 1);
/*    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);*/
//    glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);
//    glDrawArrays(GL_LINES, 0, 4);
    glLineWidth(2.0f);
    glPointSize(5.0f);

    birdi.updatePhysics(0.0016);
    std::cout << birdi.centerPosition.y <<std::endl;

}
}
