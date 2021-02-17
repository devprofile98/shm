#ifndef SHM_BASE_RENDERER_H
#define SHM_BASE_RENDERER_H
#define MAKE_SHM_LIB

// #include "shader.hpp"
#include "Core.hpp"

namespace SHM{

    class SHM_EXPORT BaseRenderer{
    public:
        BaseRenderer(){};
        virtual ~BaseRenderer(){};
        virtual void Draw()=0;
        virtual void LoadModel(const char* filepath)=0;
        virtual void LoadShaders(const char* vs_path, const char* fs_path)=0;

        glm::mat4 m_model;
        glm::mat4 m_projection;
        glm::mat4 m_view;
        shader shader_program;
    private:

    };


}


#endif  //SHM_BASE_RENDERER_H