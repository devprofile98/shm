#ifndef SHM_OPENGL_RENDERER_H
#define SHM_OPENGL_RENDERER_H

#include "Core.hpp"
#include "openglutility.hpp"
#include "Model.hpp"
#include "Camera.hpp"

#include <iostream>
#include <memory>
#include <utility>
#include <vector>


namespace SHM{

//    struct Light{
//        glm::vec3 position;
//        glm::vec3 ambient;
//        glm::vec3 diffuse;
//    };

    class Camera;

    class SHM_EXPORT openGLRenderer : public BaseRenderer{
    public:
        openGLRenderer(){};
        openGLRenderer(std::shared_ptr<Camera> camera);
        ~openGLRenderer(){};
        void Draw() override;

        uint32_t LoadModel(const char* filepath, std::shared_ptr<shader> shader) override;
        // Deprecated function
        void LoadShaders(const char* vs_path, const char* fs_path) override;
        void changePosition(uint32_t object_id, const glm::vec3& vec) override;
        void changeScale(uint32_t object_id, const glm::vec3& vec) override;
        void setProjectonMatrix(const glm::mat4& matrix);
        void setViewMatrix(const glm::mat4& matrix);
        void setModelMatrix(const glm::mat4& matrix);

        const glm::mat4& getModelMatrix() const;
        const glm::mat4& getProjectionMatrix() const;
        const glm::mat4& getViewMatrix() const;

        std::shared_ptr<Utility> GetUtility() const override;
        int getUboIndex(std::string ub_name) const override;


    private:
        void setupUBO();
        std::vector<Model> models;

        // ----------- tools --------- 
        // texture member;
        // shader program member;
        // loadmesh member;
    };

}


#endif //SHM_OPENGL_RENDERER_H
