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

float vertices[] = {
    0.0f, 0.0f, 0.0f,  // 0
    0.0f, 0.0f, -1.0f, // 1
    1.0f, 0.0f, -1.0f, // 2
    1.0f, 0.0f, 0.0    // 3
};

float element[] = {0, 1, 1, 2, 2, 3, 3, 0};

uint32_t vao, vbo, ebo;

// declaring physic objects
// --------------------------------------------
class PhysicObject {
  public:
    PhysicObject(const glm::vec3 &center, glm::vec2 velocity) : centerPosition(center), velocity(velocity) {}
    bool isAwaik = true;
    glm::vec3 centerPosition; // bounding volume center
    glm::vec2 velocity{0.0f, 0.0f};
    void addVelocity(glm::vec2 v) { velocity += v; }

    virtual void updatePhysics(float deltatime = 0.016f){};

  private:
    void generateVertex() {}
};

// represent bird as a circle bounding volume
//--------------------------------------------
class Bird : public PhysicObject {
  public:
    Bird(const glm::vec3 &center = {0.0f, 0.0f, 0.0f}, glm::vec2 velocity = {0.0f, 0.0f}, float radius = 1.0f)
        : PhysicObject(center, velocity), radius(radius) {}

    float radius;

    void calculateVelocity(float deltatime) {
        //        centerPosition.x = -20 * deltatime * deltatime + velocity.x * deltatime + centerPosition.x;
        centerPosition.x += 0.01;
        centerPosition.y = -30 * deltatime * deltatime + velocity.y * deltatime + centerPosition.y;
        velocity.y = -30 * deltatime + velocity.y;
    }

    void checkBoundaries() {
        if (centerPosition.y > 8.5 || centerPosition.y < 0) {
            isAwaik = false;
        }
    }

    void updatePhysics(float deltatime) override {
        checkBoundaries();
        if (isAwaik)
            calculateVelocity(deltatime);
    }
};

// represent Pipes as boxes
// ------------------------------------------
class Pipe : public PhysicObject {
  public:
    Pipe(const glm::vec3 &center = {0.0f, 0.0f, 0.0f}, const glm::vec3 &halfSize = {1.0, 2.0f, 0.0f})
        : PhysicObject(center, {0.0f, 0.0f}), halfSize(halfSize) {}

    glm::vec3 halfSize;
};

// GameApplication game;
Pipe *pipes = new Pipe[128];
Bird birdi;

// space button --- > add velocity to y axis
// -----------------------------------------
void spacebtn() {}

// define action for space button
// -----------------------------------------
class JumpAction : public Command {
  public:
    virtual void execute(){
        //        std::cout << "space pressed"<<std::endl;
        //        spacebtn();
    };
};

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        //        birdi.velocity += glm::vec2{0.0f, 3.0f};
        if (birdi.velocity.y < 0) {
            birdi.velocity.y = 4;
        } else {
            birdi.addVelocity({0.0f, 3.0f});
        }
    }
}

// set out of render-loop config and command
void Engine::outLoop(GLFWwindow *window) {
    Engine::m_camera->m_position = glm::vec3{2.0f, 4.7f, 11.0f};
    glfwSetKeyCallback(window, key_callback);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    static StaticActor pipe{};
    pipe.setShader("/assets/second/model_loading.vs", "/assets/second/model_loading.fs");
    pipe.loadModel(std::string{Engine::cwd + "/assets/second/texturedpipe.obj"}.c_str());
    pipe.setUpModel();

    static BirdActor bird_object{};
    bird_object.setShader(pipe.getShader());
    bird_object.loadModel(std::string{Engine::cwd + "/assets/second/texturedbird.obj"}.c_str());
    bird_object.setUpModel();
    birdi.centerPosition = glm::vec3{-3.0f, 5.7f, 0.0f};
}

// set in loop config and command
void Engine::inLoop() {
    Engine::m_camera->m_front = glm::vec3{0.0f, 0.0f, -1.0f};
    birdi.updatePhysics(0.009);
}

} // namespace SHM
