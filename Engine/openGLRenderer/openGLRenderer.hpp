#ifndef SHM_OPENGL_RENDERER_H
#define SHM_OPENGL_RENDERER_H

#include "Core.hpp"
#include <iostream>


namespace SHM{

    class SHM_EXPORT openGLRenderer : public BaseRenderer{
    public:
        openGLRenderer();
        ~openGLRenderer();
        void Draw() override;

        // ----------- tools --------- 
        // texture member;
        // shader program member;
        // loadmesh member;
    };

}


#endif //SHM_OPENGL_RENDERER_H