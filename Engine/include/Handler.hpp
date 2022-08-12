#ifndef SHM_HANDLER_H
#define SHM_HANDLER_H

#include <memory>

#include "Core.hpp"
#include "Camera.hpp"
#include "BaseActor.hpp"

namespace SHM {

// void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//     if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
//     {
//         currentXPos--;
//         if (currentXPos < 0)
//             currentXPos = 0;
//     }
// }

class SHM_EXPORT Command {
  public:
    virtual ~Command(){};
    virtual void execute(BaseActor *actor) { actor->jump(); };
};

class SHM_EXPORT Handler {
  public:
    Handler(GLFWwindow *window, std::shared_ptr<Camera> camera);
    ~Handler(){};
    /* TODO
        add a keyboard-command mapping function in Engine
        overrid custom Command with some key-map enum for ex: overridekey(KEY_SPACE, myCustomCommand)
    */

    Command *keyboard(GLFWwindow *window);
    static void mouse(GLFWwindow *window, double x, double y);
    static float last_x;
    static float last_y;
    static bool firstMouse;
    static inline std::shared_ptr<Camera> camera;
    float last_frame_time;

    // buttons
    Command *space_btn;
};

} // namespace SHM

#endif // SHM_HANDLER_H
