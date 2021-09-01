#include "openGLRenderer.hpp"


namespace SHM{

openGLRenderer::openGLRenderer(std::shared_ptr<Camera> camera)
{
    m_shadow_map_shader =std::shared_ptr<shader>{
            new shader{
            "F:/project/SHM/PlayGround/assets/second/depth_map_shader.vs",
            "F:/project/SHM/PlayGround/assets/second/depth_map_shader.fs"
            }
    };
    m_shadow_map_shader->createProgram();
    m_utils = std::shared_ptr<openGLUtility>{new openGLUtility{}};
    setModelMatrix(glm::mat4(1.0));
    setProjectonMatrix(glm::perspective(glm::radians(camera->m_fov),1920.0f/ 1080.0f, 0.01f, 100.0f));
    setViewMatrix(glm::lookAt(camera->m_position, camera->m_position + camera->m_front, camera->m_up));
    setupUBO();
}

void openGLRenderer::Draw(std::shared_ptr<shader> sh){
    for(unsigned long long i=0;i< models.size(); i++){
        if(sh) models[i].Draw(sh);
        else models[i].Draw();
    }
}

int openGLRenderer::LoadModel(const char* filepath, std::shared_ptr<shader> shader){
    uint32_t temp = models.size();
    Model model{filepath, shader};
    models.push_back(model);
    std::cout << "value is : " << models.size() << &models.at(temp) <<std::endl;
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
//    int b{-2};
    //        ubo_vp = SHM::BUFFERS::createNewUBO("VPMatrices", 2*sizeof(glm::mat4),&b);
    //        std::cout <<"From Renderer VPMatrices "<< ubo_vp << getUboIndex("VPMatrices")<<std::endl;
    //        ubo_lights = SHM::BUFFERS::createNewUBO("Lights", 16*4 + 16*3 + 16*5 + 4*4 + 5*4,&b);
    //        std::cout <<"From Renderer Lights "<< ubo_lights << getUboIndex("Lights")<<std::endl;

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

void openGLRenderer::enableShadows()
{
    glGenFramebuffers(1, &depth_map_fbo);
    shadow_map_texture = Texture::createTexture2D(GL_DEPTH_COMPONENT, 2048, 2048);
    glBindFramebuffer(GL_FRAMEBUFFER, depth_map_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadow_map_texture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

std::shared_ptr<Utility> openGLRenderer::GetUtility() const{
    return m_utils;
}

int openGLRenderer::getUboIndex(std::string ub_name) const
{
    return  shader::m_uniform_blocks[ub_name] -1;
}

Model *openGLRenderer::getModelByIndex(uint32_t index)
{
    return &models[index];
}

}
