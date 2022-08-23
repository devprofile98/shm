#ifndef SHM_ENGINE_H
#define SHM_ENGINE_H

#define MAKE_SHM_LIB

#include "Core.hpp"
#include "Camera.hpp"
#include "Handler.hpp"
#include "openGLRenderer.hpp"
#include "InputHandler.hpp"

#include <string_view>
#include <memory>
#include <iostream>
#include <stdint.h>

#include "physics/PhysicWorld.hpp"

namespace SHM {

enum API_TYPE { OPENGL, VULKAN };
//    class Application;
class SHM_EXPORT Engine {
  public:
    ~Engine();

    std::shared_ptr<BaseRenderer> getRenderer();
    std::shared_ptr<Camera> getCamera();
    void MainRenderLoop();
    Handler *getHandler();
    std::string cwd;

    std::shared_ptr<shader> CreateShader(const char *vertex_code, const char *fragment_code);

    // TODO remove it from here and add it to handler class
    void mouse(GLFWwindow *window, double xpos, double ypos);
    float last_x, last_y;
    bool firstMouse = true;

    bool InitWorld();
    void outLoop(GLFWwindow *window = nullptr);
    void inLoop();
    void saveImage(char *file_path);
    //        void setKeyBinding(Application *app);
    ContextManager *context_manager;
    BaseActor *mainCharacter;
    PHYSICS::World *getPhysicWorld();
    void setMovingCharacter(BaseActor *actor);
    void setActionToKey(KEY key, Command *command);

    static std::shared_ptr<Engine> GetEngine();
    static std::shared_ptr<Engine> startEngine(const char *project_name, API_TYPE api_type, const char *cwd = nullptr);

  protected:
    Engine(const char *project_name, API_TYPE api_type, const char *cwd = nullptr);
    static inline std::shared_ptr<Engine> m_engine;

  private:
    void setRenderer(API_TYPE api_type);
    std::shared_ptr<BaseRenderer> m_renderer;

    std::shared_ptr<Camera> m_camera;
    Handler *m_handler;
    PHYSICS::World *m_world;
};

} // namespace SHM
#endif // SHM_ENGINE_H
