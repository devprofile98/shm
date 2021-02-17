#include "openGLRenderer.hpp"


namespace SHM{


    openGLRenderer::openGLRenderer(){

    }
    openGLRenderer::~openGLRenderer(){

    }

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


}