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

        virtual void setModelMatrix(const glm::mat4& matrix)=0;
        virtual void setProjectonMatrix(const glm::mat4& matrix)=0;
        virtual void setViewMatrix(const glm::mat4& matrix)=0;

        virtual const glm::mat4& getModelMatrix() const=0;
        virtual const glm::mat4& getProjectionMatrix() const=0;
        virtual const glm::mat4& getViewMatrix() const=0;

        shader shader_program;
    
    protected:
        glm::mat4 m_model;
        glm::mat4 m_projection;
        glm::mat4 m_view;
    private:

    };


}


#endif  //SHM_BASE_RENDERER_H