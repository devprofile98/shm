// #define SHM_ENGINE_ACTOR_H
#ifndef SHM_ENGINE_ACTOR_H
#define SHM_ENGINE_ACTOR_H

#include <iostream>
#include <string>
#include "Engine.hpp"
#include "BaseActor.hpp"
#include "physics/BasePhysics.hpp"

namespace SHM {
class Actor : public BaseActor {
  public:
    Actor(const std::string &name = "Unknown");
    virtual ~Actor();
    virtual void Load();
    std::shared_ptr<shader> setShader(const char *v_shader, const char *f_shader) override;
    std::shared_ptr<shader> setShader(std::shared_ptr<shader>) override;
    std::shared_ptr<shader> getShader();
    void loadModel(const char *file_path) override;
    void handleInput(KEY key) override;
    void setUpModel() override;
    void eachFrame() override;
    std::string getName() const;
    PHYSICS::PhysicObject *m_physic_component = nullptr;

  private:
    std::string mObjectName = "Unknown";
};
} // namespace SHM

#endif // SHM_ENGINE_ACTOR_H