#include "shm/Engine.hpp"
#include "shm/Light.hpp"
#include "shm/Logger.hpp"
// #include "birdModel.hpp"
#include "chrono"
#include "shm/buffers.hpp"
#include "shm/glm/gtx/string_cast.hpp"
#include "staticActor.hpp"

#include <format>

#define GET_MODEL(x) Engine::getRenderer()->getModelByIndex(x)
#define REGISTER_MODEL(x) Engine::getRenderer()->registerModel(x)

void calculate_tangent() {
    glm::vec3 pos1(-1.0, 1.0, 0.0);
    glm::vec3 pos2(-1.0, -1.0, 0.0);
    glm::vec3 pos3(1.0, -1.0, 0.0);
    glm::vec3 pos4(1.0, 1.0, 0.0);
    // texture coordinates
    glm::vec2 uv1(0.0, 1.0);
    glm::vec2 uv2(0.0, 0.0);
    glm::vec2 uv3(1.0, 0.0);
    glm::vec2 uv4(1.0, 1.0);
    // normal vector
    glm::vec3 nm(0.0, 0.0, 1.0);

    glm::vec3 edge1 = pos2 - pos1;
    glm::vec3 edge2 = pos3 - pos1;
    glm::vec2 deltaUV1 = uv2 - uv1;
    glm::vec2 deltaUV2 = uv3 - uv1;
    // calculate T and B and TBN

    float f = 1.0 / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
    glm::vec3 tangent;
    glm::vec3 biTangent;
    tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

    biTangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    biTangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    biTangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

    std::cout << std::format("Tangent is : {} {} {}", tangent.x, tangent.y, tangent.z) << std::endl;
    std::cout << std::format("bi Tangent is : {} {} {}", biTangent.x, biTangent.y, biTangent.z) << std::endl;
    glm::vec3 normal = glm::cross(tangent, biTangent);
    std::cout << std::format("the normal is: {} {} {}\n", normal.x, normal.y, normal.z);
}

namespace SHM {
// set out of render-loop configs and commands
void Engine::outLoop(GLFWwindow *window) {

    // calculate_tangent();
    Engine::m_camera->m_position = glm::vec3{2.0f, 4.7f, 11.0f};

    std::vector<std::string> faces = {
        Engine::cwd + "/assets/cubemaps/skybox/right.jpg", Engine::cwd + "/assets/cubemaps/skybox/left.jpg",
        Engine::cwd + "/assets/cubemaps/skybox/top.jpg",   Engine::cwd + "/assets/cubemaps/skybox/bottom.jpg",
        Engine::cwd + "/assets/cubemaps/skybox/front.jpg", Engine::cwd + "/assets/cubemaps/skybox/back.jpg",
    };

    Engine::setSkyShader(faces);

    static StaticActor pipe{};
    pipe.setShader("/assets/shaders/model_loading.vs", "/assets/shaders/model_loading.fs");
    pipe.loadModel(std::string{Engine::cwd + "/assets/models/wooden_surface.obj"}.c_str());
    pipe.setUpModel();
    //   pipe.model->setPosition({1.0, 0.5, 0.0});
    pipe.model->setPosition({0.0, 0.0, 0.0});
    pipe.model->setScale({2.0, 1.0, 2.0});
    // pipe.model->material.roughness = 0.9;

    static StaticActor plane{};
    plane.setShader("/assets/shaders/model_loading.vs", "/assets/shaders/model_loading.fs");
    plane.loadModel(std::string{Engine::cwd + "/assets/models/plane.obj"}.c_str());
    plane.setUpModel();
    plane.model->setPosition({-2.0, 2.5, 2.0});
    plane.model->setRotation(glm::vec3{0.0, 0.0, 1.0}, 45.0f);
    plane.isAlpha = true;

    static StaticActor _tmp{};
    _tmp.setShader("/assets/shaders/model_loading.vs", "/assets/shaders/model_loading.fs");
    _tmp.loadModel(std::string{Engine::cwd + "/assets/models/plane.obj"}.c_str());
    _tmp.setUpModel();
    _tmp.model->setPosition({-2.0, 2.5, 2.0});
    _tmp.model->setRotation(glm::vec3{0.0, 0.0, 1.0}, 45.0f);
    _tmp.isAlpha = true;
    _tmp.model->setRoughness(0.3);

    static StaticActor cube{};
    cube.setShader("/assets/shaders/model_loading.vs", "/assets/shaders/model_loading.fs");
    cube.loadModel(std::string{Engine::cwd + "/assets/models/cube.obj"}.c_str());
    cube.setUpModel();
    cube.model->setPosition({2.8, 3.5, 2.6});
    cube.model->setScale({0.2, 0.2, 0.2});
    cube.model->setRotation(glm::vec3{0.0, 0.0, 1.0}, 45.0f);
    cube.model->setRoughness(1.0);

    static StaticActor table{};
    table.setShader("/assets/shaders/model_loading.vs", "/assets/shaders/model_loading.fs");
    // table.setShader(pipe.getShader());
    table.loadModel(std::string{Engine::cwd + "/assets/models/tableobj.obj"}.c_str());
    table.setUpModel();
    table.model->setPosition({2.8, 0.5, 2.6});
    table.model->setScale({2.2, 2.2, 2.2});
    // table.model->setRoughness(1.0);

    static StaticActor plane2{};
    plane2.setShader("/assets/shaders/model_loading.vs", "/assets/shaders/model_loading.fs");
    plane2.loadModel(std::string{Engine::cwd + "/assets/models/plane.obj"}.c_str());
    plane2.setUpModel();
    plane2.model->setPosition({4.5, 2.2, 4.0});
    plane2.model->setRotation(glm::vec3{0.0, 1.0, 0.0}, 0.0f);
    plane2.isAlpha = true;
    plane2.model->setRoughness(0.3);

    static StaticActor bird_object{};
    bird_object.setShader("/assets/shaders/model_loading.vs", "/assets/shaders/model_loading.fs");

    // bird_object.setShader(wall.getShader());
    bird_object.loadModel(std::string{Engine::cwd + "/assets/models/chair.obj"}.c_str());
    bird_object.setUpModel();
    bird_object.model->setPosition({1.0, 0.5, -1.0});
    bird_object.model->setScale({4.0, 4.0, 4.0});
    bird_object.model->setRotation(glm::vec3{0.0, 1.0, 0.0}, 30.0f);
    // bird_object.model->setRotation(glm::vec3{1.0, 0.0, 0.0}, 30.0f);
    bird_object.model->setSelected(true);

    SpotLight sl{{1.0, -1.0, 2.2}, {1.0, 3.0, 2.2}, SHM::rgb::GREEN};
    SpotLight sl1{{0.0, 0.0, 0.0}, {1.0, 1.0, 2.2}, SHM::rgb::RED};
    SpotLight sl2{{0.0, 0.0, 0.0}, {1.0, 1.0, -2.2}, SHM::rgb::BLUE};

    PointLight pl{{-1.0, 3.0, 2.2}, SHM::rgb::PURPLE};
    // PointLight pl2{{2.8, 1.0, -1.2}, {1.0, 0.3, 0.0}};
    PointLight pl3{{1.0, 2.5, -1.0}, SHM::rgb::RED};
    PointLight pl4{{7.0, 1.0, 1.2}, SHM::rgb::BLUE};
}

// set in loop config and command
void Engine::Loop() {
    // Engine::m_camera->m_front = glm::vec3{0.0f, 0.0f, -1.0f};
}

} // namespace SHM
