#include "openGLRenderer.hpp"


namespace SHM{


    // openGLRenderer::openGLRenderer(){}

    openGLRenderer::openGLRenderer(Camera camera)
    {
        setModelMatrix(glm::mat4(1.0));
        setProjectonMatrix(glm::perspective(glm::radians(camera.m_fov),1920.0f/ 1080.0f, 0.1f, 100.0f));
        setViewMatrix(glm::lookAt(camera.m_position, camera.m_position + camera.m_front, camera.m_up));
    }
    // openGLRenderer::~openGLRenderer(){

    // }

    void openGLRenderer::Draw(){
        // std::cout <<"Rendering through OPENGL API"<<std::endl;
        for(int i=0;i< models.size(); i++){
            // std::cout<<"IN RENDER LOOP"<<std::endl;

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(-1.0f, -1.0f, -1.0f)); // translate it down so it's at the center of the scene
            model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
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