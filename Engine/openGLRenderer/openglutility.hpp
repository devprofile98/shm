#ifndef SHM_OPENGLUTILITY_HPP
#define SHM_OPENGLUTILITY_HPP

#include "BaseUtility.hpp"

namespace SHM {

    class openGLUtility : public BaseUtility
    {
    public:
        openGLUtility();
        ~openGLUtility();
        void InitWorld() override;
    };

}
#endif // OPENGLUTILITY_HPP
