#ifndef SHM_HANDLER_H
#define SHM_HANDLER_H

#include <memory>

#include "Core.hpp"
#include "Camera.hpp"
#include "BaseActor.hpp"
#include "InputHandler.hpp"

namespace SHM {

class SHM_EXPORT Handler {
  public:
    Handler(GLFWwindow *window, std::shared_ptr<Camera> camera);
    ~Handler(){};
    /* TODO
        add a keyboard-command mapping function in Engine
        override custom Command with some key-map enum for ex: overridekey(KEY_SPACE, myCustomCommand)
    */

    void *keyboard(GLFWwindow *window, BaseActor* actor);
    static void mouse(GLFWwindow *window, double x, double y);
    static float last_x;
    static float last_y;
    static bool firstMouse;
    static inline std::shared_ptr<Camera> camera;
    float last_frame_time;

    // void setKeyToCommand(KEY key, Command *command);

    // buttons
    // Command *space_btn, *w_btn;
};

} // namespace SHM

#endif // SHM_HANDLER_H
