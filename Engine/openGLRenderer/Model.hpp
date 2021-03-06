#ifndef ENGINE_MODEL_H
#define ENGINE_MODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
//gl math
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>

#include <shader.hpp>
#include "Mesh.hpp"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model{
public:
    Model(const char* path, std::shared_ptr<shader> shader_program);
    void Draw();
    std::vector<Texture> textures_loaded; 
    std::vector<Mesh> meshes;
    std::shared_ptr<shader> getShader() ;


private:
    std::string directory;
    std::shared_ptr<shader> shader_program;
    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTexture(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif //ENGINE_MODEL_H
