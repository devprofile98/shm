#ifndef SHM_BASE_RENDERER_H
#define SHM_BASE_RENDERER_H
#define MAKE_SHM_LIB

// #include "shader.hpp"
#include "butils.hpp"
#include "Utility.hpp"
#include "Core.hpp"
#include "buffers.hpp"
#include "Model.hpp"


namespace SHM{

    class SHM_EXPORT BaseRenderer{
    public:
        BaseRenderer(){};
        virtual ~BaseRenderer(){};
        virtual void Draw()=0;
        virtual Model* LoadModel(const char* filepath, std::shared_ptr<shader> shader)=0;
        virtual void LoadShaders(const char* vs_path, const char* fs_path)=0;
        virtual void changePosition(uint32_t object_id,const glm::vec3& vec)=0;
        virtual void changeScale(uint32_t object_id, const glm::vec3& vec)=0;
        virtual void setModelMatrix(const glm::mat4& matrix)=0;
        virtual void setProjectonMatrix(const glm::mat4& matrix)=0;
        virtual void setViewMatrix(const glm::mat4& matrix)=0;

        virtual const glm::mat4& getModelMatrix() const=0;
        virtual const glm::mat4& getProjectionMatrix() const=0;
        virtual const glm::mat4& getViewMatrix() const=0;

        virtual std::shared_ptr<Utility> GetUtility() const=0;
        virtual int getUboIndex(std::string ub_name) const =0;

        shader shader_program;
        uint32_t ubo_vp, ubo_lights, ubo_spots;

    protected:
        glm::mat4 m_model;
        glm::mat4 m_projection;
        glm::mat4 m_view;
//        std::shared_ptr<BaseUtility> m_utils;
        std::shared_ptr<Utility> m_utils;
    private:
    };


}



#endif  //SHM_BASE_RENDERER_H
