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
// set out of render-loop config and command
void Engine::outLoop(GLFWwindow *window) {
    Engine::m_camera->m_position = glm::vec3{2.0f, 4.7f, 11.0f};

    static StaticActor pipe{};
    pipe.setShader("/assets/second/model_loading.vs", "/assets/second/model_loading.fs");
    pipe.loadModel(std::string{Engine::cwd + "/assets/second/texturedpipe.obj"}.c_str());
    pipe.setUpModel();

    static BirdActor bird_object{};
    bird_object.setShader(pipe.getShader());
    bird_object.loadModel(std::string{Engine::cwd + "/assets/second/texturedbird.obj"}.c_str());
    bird_object.setUpModel();
}

// set in loop config and command
void Engine::inLoop() {
    Engine::m_camera->m_front = glm::vec3{0.0f, 0.0f, -1.0f};
}

} // namespace SHM
