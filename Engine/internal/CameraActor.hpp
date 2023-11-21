#ifndef SHM_ENGINE_INTERNAL_CAMERA_ACTOR
#define SHM_ENGINE_INTERNAL_CAMERA_ACTOR

#include "Actor.hpp"
#include "BaseActor.hpp"
#include "InputHandler.hpp"

class CameraActor: public SHM::Actor {

  public:
    CameraActor();
    virtual ~CameraActor();

    void setUpModel() override;
    // void eachFrame() override;
    // void jump() override;
    void handleInput(SHM::KEY key) override;
};

#endif // SHM_ENGINE_INTERNAL_CAMERA_ACTOR 