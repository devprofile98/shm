#include "staticActor.hpp"

StaticActor::StaticActor() {

  SHM::Engine::GetEngine()->getRenderer()->m_actors.push_back(this);
  //   SHM::Engine::GetEngine()->setMovingCharacter(this);
  std::cout << "statically called Static actor to add actor" << std::endl;
}
StaticActor::~StaticActor() {
  std::cout << "Static Actor destroyed!" << std::endl;
}

void StaticActor::setUpModel() {
  // float height = 0.0f;
  // for (int i = 0; i < 128; i++) {
  //     height = static_cast<float>(std::rand() % 3);

  //     if (i % 2 == 0) {
  //         PipePhysic *another_pipe = new PipePhysic{new
  //         glm::vec3{static_cast<float>(i * 2), height, 0}, {0.0f, 0.0f}};
  //         another_pipe->halfSize = glm::vec3{0.95, 2.4f, 0.0};
  //         SHM::Engine::GetEngine()->getPhysicWorld()->registerToPhysics(another_pipe);
  //         pipes_pos.push_back({static_cast<float>(i * 2), height, 0});
  //     } else {
  //         PipePhysic *another_pipe = new PipePhysic{new
  //         glm::vec3{static_cast<float>(i * 2), 9 + height, 0}, {0.0f, 0.0f}};
  //         another_pipe->halfSize = glm::vec3{0.95, 2.4f, 0.0};
  //         SHM::Engine::GetEngine()->getPhysicWorld()->registerToPhysics(another_pipe);
  //         pipes_pos.push_back({static_cast<float>(i * 2), 9 + height, 0});
  //     }
  // }
}

void StaticActor::eachFrame() {
  this->model->DrawInstances(pipes_pos, nullptr);
}

void StaticActor::add_pipe_pos(const glm::vec3 &pos) {
  pipes_pos.push_back(pos);
}
