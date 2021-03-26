#include "openGLRenderer.hpp"


namespace SHM{


    // openGLRenderer::openGLRenderer(){}

    openGLRenderer::openGLRenderer(std::shared_ptr<Camera> camera)
    {
        setModelMatrix(glm::mat4(1.0));
        setProjectonMatrix(glm::perspective(glm::radians(camera->m_fov),1920.0f/ 1080.0f, 0.01f, 100.0f));
        setViewMatrix(glm::lookAt(camera->m_position, camera->m_position + camera->m_front, camera->m_up));
        // add uniform blocks and binding points to shader class
        setupUBO();
        shader::m_ub_pairs.push_back(std::make_pair(std::string{"VPMatrices"}, 0));
        shader::m_ub_pairs.push_back(std::make_pair(std::string{"Lights"}, 1));

    }
    // openGLRenderer::~openGLRenderer(){

    // }

    void openGLRenderer::Draw(){
        for(int i=0;i< models.size(); i++){
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(-1.0f, -1.0f, -1.0f));
            model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
            shader_program.setMat4("model", model);
            models[i].Draw(shader_program);
        }
    }

    void openGLRenderer::LoadModel(const char* filepath){
        Model model{filepath};
        models.push_back(model);

    }

    void openGLRenderer::LoadShaders(const char* vs_path, const char* fs_path)
    {
        shader shader{vs_path, fs_path};
        shader.createProgram();
        shader_program = shader;
        // return shader;
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
        glGenBuffers(1, &ubo_vp);
        glBindBuffer(GL_UNIFORM_BUFFER, ubo_vp);
        glBufferData(GL_UNIFORM_BUFFER, 2*sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo_vp,0, 2 * sizeof(glm::mat4));

        glGenBuffers(1, &ubo_lights);
        glBindBuffer(GL_UNIFORM_BUFFER, ubo_lights);
        glBufferData(GL_UNIFORM_BUFFER, 16*3, nullptr, GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        glBindBufferRange(GL_UNIFORM_BUFFER, 1, ubo_lights,0, 16*3);

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

}
