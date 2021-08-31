#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
//gl math
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <stdint.h>
#include <vector>
#include "shader.hpp"

// Struct container for single Vertex information
struct Vertex{
    glm::vec3 Position;
    glm::vec2 TexCoords;
    glm::vec3 Normal;
        // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;

};

// Struct container for Texture information 
// id : unique texture unit id
// type : type of Texture -> diffuse or specular map texture 
struct Texture_INT{
    uint32_t id;
    std::string type;
    std::string path;
    uint8_t bounded_slot;
};


class Mesh{
public:
    // mesh data
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<Texture_INT> textures;
    
    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture_INT> textures);
    void Draw(std::shared_ptr<shader> shadr);

private:
    //  render data
    uint32_t VAO, VBO, EBO;

    void setupMesh();

};



#endif //ENGINE_MESH_H
