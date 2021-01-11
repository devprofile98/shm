#ifndef ENGINE_MODEL_H
#define ENGINE_MODEL_H

#include "Core.hpp"

#include "shader.hpp"
#include <vector>
#include <string>

#include "Mesh.hpp"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model{
public:
    Model(const char* path);
    void Draw(shader &shader);
    std::vector<Texture> textures_loaded; 
    std::vector<Mesh> meshes;

private:
    std::string directory;
    
    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTexture(aiMaterial *mat, aiTextureType type, std::string typeName);

};



#endif //ENGINE_MODEL_H