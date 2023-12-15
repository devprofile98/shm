#ifndef PLAYGROUND_STATIC_ACTOR_H
#define PLAYGROUND_STATIC_ACTOR_H

#include "shm/Actor.hpp"

class StaticActor : public SHM::Actor {
public:
  StaticActor();
  virtual ~StaticActor();

  void setUpModel() override;
  void eachFrame() override;

  std::vector<glm::vec3> pipes_pos; // list of all pipes position in game
  void add_pipe_pos(const glm::vec3 &pos);
};

#endif // PLAYGROUND_STATIC_ACTOR_H
