#ifndef ENGINE_MODEL_H
#define ENGINE_MODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
//gl math
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>

#include <shader.hpp>
#include "Mesh.hpp"
#include "Common.hpp"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model{
public:
    Model(const char* path, std::shared_ptr<shader> shader_program);
    ~Model();
    void Draw(std::shared_ptr<shader> sh=nullptr);
    void DrawInstances(std::vector<glm::vec3>& positions, std::shared_ptr<shader> shader_program);
    std::vector<Texture_INT> textures_loaded;
    std::vector<Mesh> meshes;
    std::shared_ptr<shader> getShader();

    void setPosition(const glm::vec3& pos);
    void setScale(const glm::vec3& scale);
    void setRotation(const glm::vec3& rot, float radians=0);

    const glm::vec3 *getPosition() const;
    glm::vec3 *getPosition();
    const glm::vec3 *getScale() const;
    const glm::vec3 *getRotation() const;
    static uint32_t texture_layout_counter;
private:
    std::string directory;
    std::shared_ptr<shader> shader_program;
    void loadModel(std::string path);
    glm::vec3 m_position, m_rotation, m_scale;
    float m_rotation_radians;
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture_INT> loadMaterialTexture(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif //ENGINE_MODEL_H
