#include "openGLRenderer.hpp"


namespace SHM{

    openGLRenderer::openGLRenderer(std::shared_ptr<Camera> camera)
    {
//        m_utils = std::shared_ptr<openGLUtility>{new openGLUtility{}};
        setModelMatrix(glm::mat4(1.0));
        setProjectonMatrix(glm::perspective(glm::radians(camera->m_fov),1920.0f/ 1080.0f, 0.01f, 100.0f));
        setViewMatrix(glm::lookAt(camera->m_position, camera->m_position + camera->m_front, camera->m_up));
        // add uniform blocks and binding points to shader class
        shader::m_ub_pairs.push_back(std::make_pair(std::string{"VPMatrices"}, 0));
        shader::m_ub_pairs.push_back(std::make_pair(std::string{"Lights"}, 1));
        setupUBO();
    }
    // openGLRenderer::~openGLRenderer(){

    // }

    void openGLRenderer::Draw(){
        for(int i=0;i< models.size(); i++){
            models[i].Draw();
        }
    }

    uint32_t openGLRenderer::LoadModel(const char* filepath, std::shared_ptr<shader> shader){
        uint32_t temp = models.size();
        Model model{filepath, shader};
        models.push_back(model);
        return temp;
    }

    void openGLRenderer::LoadShaders(const char* vs_path, const char* fs_path)
    {
        shader shader{vs_path, fs_path};
        shader.createProgram();
        shader_program = shader;
        // return shader;
    }

    void openGLRenderer::changePosition(uint32_t object_id, const glm::vec3& vec)
    {
        std::shared_ptr<shader> sh = models[object_id].getShader();
        sh->use();
        glm::mat4 model = glm::translate(glm::mat4{1.0}, vec);
        sh->setMat4("model", model);
    }

    void openGLRenderer::changeScale(uint32_t object_id, const glm::vec3& vec)
    {
        std::shared_ptr<shader> sh = models[object_id].getShader();
        sh->use();
        glm::mat4 model = glm::scale(glm::mat4{1.0}, vec);
        sh->setMat4("model", model);
    }

    const glm::mat4& openGLRenderer::getModelMatrix() const{
        return m_model;
    }

    const glm::mat4& openGLRenderer::getProjectionMatrix() const{
        return m_projection;
    }

    const glm::mat4& openGLRenderer::getViewMatrix() const{
        return m_view;
    }

    void openGLRenderer::setupUBO()
    {
        int b{-2};
        ubo_vp = SHM::BUFFERS::createNewUBO(shader::m_ub_pairs[0].first, 2*sizeof(glm::mat4),&b);
        ubo_lights = SHM::BUFFERS::createNewUBO(shader::m_ub_pairs[1].first, 16*4 + 16*3 + 16*5 + 4*4 + 5*4,&b);
    }

    void openGLRenderer::setProjectonMatrix(const glm::mat4& matrix){
        m_projection = matrix;
    }

    void openGLRenderer::setViewMatrix(const glm::mat4& matrix){
        m_view = matrix;
    }

    void openGLRenderer::setModelMatrix(const glm::mat4& matrix){
        m_model = matrix;
    }

//    std::shared_ptr<BaseUtility> openGLRenderer::GetUtility() const{
//        return m_utils;
//    }

}
