#ifndef SHM_BASE_RENDERER_H
#define SHM_BASE_RENDERER_H
#define MAKE_SHM_LIB

#include "Core.hpp"

namespace SHM{

    class SHM_EXPORT BaseRenderer{
    public:
        BaseRenderer(){};
        virtual ~BaseRenderer(){};
        virtual void Draw()=0;

    private:

    };


}


#endif  //SHM_BASE_RENDERER_H