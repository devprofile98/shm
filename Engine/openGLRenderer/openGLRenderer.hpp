#ifndef SHM_OPENGL_RENDERER_H
#define SHM_OPENGL_RENDERER_H

#include "Core.hpp"
#include <iostream>
// #include <vector>
#include "Model.hpp"


namespace SHM{

    class SHM_EXPORT openGLRenderer : public BaseRenderer{
    public:
        openGLRenderer();
        ~openGLRenderer();
        void Draw() override;

        void LoadModel(const char* filepath) override;
        void LoadShaders(const char* vs_path, const char* fs_path) override;

        //TODO make this private
        glm::mat4 m_model;
        glm::mat4 m_projection;
        glm::mat4 m_view;
        // shader shader_program;

    private:
        std::vector<Model> models;



        // ----------- tools --------- 
        // texture member;
        // shader program member;
        // loadmesh member;
    };

}


#endif //SHM_OPENGL_RENDERER_H