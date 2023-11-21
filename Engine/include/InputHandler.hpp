#ifndef SHM_INPUT_HANDLER_H
#define SHM_INPUT_HANDLER_H

#include "Core.hpp"
// #include "Engine.hpp"
namespace SHM {
enum class KEY {
    KEYBOARD_NONE,
    KEYBOARD_W,
    KEYBOARD_S,
    KEYBOARD_A,
    KEYBOARD_D,
    KEYBOARD_SPACE,
    KEYBOARD_ENTER,
    KEYBOARD_ESCAPE,
    // To be continued
};

// class SHM_EXPORT Command {
//   public:
//     virtual ~Command(){};
//     // virtual void execute(BaseActor *actor) = 0;
// };
} // namespace SHM

#endif // SHM_INPUT_HANDLER_H