#ifndef SHM_OPENGL_RENDERER_H
#define SHM_OPENGL_RENDERER_H

#include "Core.hpp"
#include <iostream>
// #include <vector>
#include "Model.hpp"
#include "Camera.hpp"
#include <memory>



namespace SHM{

    class Camera;
    class SHM_EXPORT openGLRenderer : public BaseRenderer{
    public:
        openGLRenderer(){};
        openGLRenderer(std::shared_ptr<Camera> camera);
        ~openGLRenderer(){};
        void Draw() override;

        void LoadModel(const char* filepath) override;
        void LoadShaders(const char* vs_path, const char* fs_path) override;

        void setProjectonMatrix(const glm::mat4& matrix);
        void setViewMatrix(const glm::mat4& matrix);
        void setModelMatrix(const glm::mat4& matrix);

        const glm::mat4& getModelMatrix() const;
        const glm::mat4& getProjectionMatrix() const;
        const glm::mat4& getViewMatrix() const;
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
