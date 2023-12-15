#include "shm/Engine.hpp"
#include "shm/Light.hpp"
#include "shm/Logger.hpp"
// #include "birdModel.hpp"
#include "chrono"
#include "shm/buffers.hpp"
#include "shm/glm/gtx/string_cast.hpp"
#include "staticActor.hpp"

#define GET_MODEL(x) Engine::getRenderer()->getModelByIndex(x)
#define REGISTER_MODEL(x) Engine::getRenderer()->registerModel(x)

namespace SHM {
// set out of render-loop config and command
void Engine::outLoop(GLFWwindow *window) {
  Engine::m_camera->m_position = glm::vec3{2.0f, 4.7f, 11.0f};

  std::vector<std::string> faces = {
      Engine::cwd + "/assets/cubemaps/skybox/right.jpg",
      Engine::cwd + "/assets/cubemaps/skybox/left.jpg",
      Engine::cwd + "/assets/cubemaps/skybox/top.jpg",
      Engine::cwd + "/assets/cubemaps/skybox/bottom.jpg",
      Engine::cwd + "/assets/cubemaps/skybox/front.jpg",
      Engine::cwd + "/assets/cubemaps/skybox/back.jpg",
  };

  Engine::setSkyShader(faces);

  static StaticActor pipe{};
  pipe.setShader("/assets/models/model_loading.vs",
                 "/assets/models/model_loading.fs");
  pipe.loadModel(
      std::string{Engine::cwd + "/assets/models/wooden_surface.obj"}.c_str());
  pipe.setUpModel();
  //   pipe.model->setPosition({1.0, 0.5, 0.0});
  pipe.model->setPosition({0.0, 0.0, 0.0});
  pipe.model->setScale({2.0, 1.0, 2.0});

  static StaticActor wall{};
  wall.setShader(pipe.getShader());
  wall.loadModel(
      std::string{Engine::cwd + "/assets/models/tableobj.obj"}.c_str());
  wall.setUpModel();
  //   wall.model->setPosition({-8.5, 6.0, 0.0});
  wall.model->setPosition({2.8, 0.5, 2.6});
  wall.model->setScale({2.2, 2.2, 2.2});

  static StaticActor plane{};
  plane.setShader("/assets/models/model_loading.vs",
                  "/assets/models/model_loading.fs");
  plane.loadModel(
      std::string{Engine::cwd + "/assets/models/plane.obj"}.c_str());
  plane.setUpModel();
  plane.model->setPosition({-2.0, 2.5, 2.0});
  plane.model->setRotation(glm::vec3{0.0, 0.0, 1.0}, 45.0f);
  plane.isAlpha = true;

  static StaticActor plane2{};
  plane2.setShader("/assets/models/model_loading.vs",
                   "/assets/models/model_loading.fs");
  plane2.loadModel(
      std::string{Engine::cwd + "/assets/models/plane.obj"}.c_str());
  plane2.setUpModel();
  plane2.model->setPosition({4.5, 2.2, 4.0});
  plane2.model->setRotation(glm::vec3{0.0, 1.0, 0.0}, 60.0f);
  plane2.isAlpha = true;

  static StaticActor bird_object{};
  bird_object.setShader("/assets/models/model_loading.vs",
                        "/assets/models/model_loading.fs");

  //   bird_object.setShader("/assets/vert.vs", "/assets/frag.fs");
  bird_object.loadModel(
      std::string{Engine::cwd + "/assets/models/chair.obj"}.c_str());
  bird_object.setUpModel();
  bird_object.model->setPosition({1.0, 0.5, 0.0});
  bird_object.model->setScale({4.0, 4.0, 4.0});
  bird_object.model->setRotation(glm::vec3{0.0, 1.0, 0.0}, 30.0f);
  bird_object.model->setSelected(true);

  SpotLight sl{{1.0, -1.0, 2.2}, {1.0, 3.0, 2.2}, SHM::rgb::GREEN};
  SpotLight sl1{{0.0, 0.0, 0.0}, {1.0, 1.0, 2.2}, SHM::rgb::RED};
  SpotLight sl2{{0.0, 0.0, 0.0}, {1.0, 1.0, -2.2}, SHM::rgb::BLUE};

  //   sl.setDiffuse({1.0f, 1.0f, 0.0f});
  //   sl.setAmbient({0.0f, 0.0f, 1.0f});
  //   sl.setSpecular({0.5f, 0.5f, 1.0f});

  PointLight pl{{-1.0, 3.0, 2.2}, SHM::rgb::PURPLE};
  PointLight pl2{{2.8, 1.0, -1.2}, {1.0, 0.3, 0.0}};
  PointLight pl3{{2.0, 1.5, 7.2}, SHM::rgb::RED};
  PointLight pl4{{7.0, 1.0, 1.2}, SHM::rgb::BLUE};

  //   PointLight pl2{{0.0, 1.0, 3.2}, SHM::rgb::ORANGE};
  //   PointLight pl3{{2.0, 0.0, 0.2}, SHM::rgb::PURPLE};
  //   pl.setDiffuse({1.0f, 0.0f, 1.0f});
  //   pl.setAmbient({0.0f, 0.0f, 1.0f});
  //   pl.setSpecular({0.5f, 0.5f, 1.0f});
}

// set in loop config and command
void Engine::Loop() {
  // Engine::m_camera->m_front = glm::vec3{0.0f, 0.0f, -1.0f};
}

} // namespace SHM
