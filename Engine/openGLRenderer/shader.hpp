#ifndef SHADER_H
#define SHADER_H

// #include "Core.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
// gl math
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <utility>
#include <stdexcept>
#include <unordered_map>

class shader {

  public:
    shader(){};
    shader(const char *vertexPath, const char *fragmentPath);
    ~shader(){};

    bool createProgram();
    void use();
    void useGlobalVariables() const; // connect shader uniform block to binding points if any
    uint16_t ID;                     // shader program id

    void setVec3(const char *uniform_name, const glm::vec3 &value) const;
    void setVec3(const char *uniform_name, float x, float y, float z) const;
    void setVec4(const char *uniform_name, const glm::vec4 &) const;

    void setFloat(const char *uniform_name, float value) const;
    void setInt(const char *uniform_name, int value) const;
    void setBool(const char *uniform_name, bool value) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    static std::unordered_map<std::string, int> m_uniform_blocks; // key value pair

  private:
    std::string vShaderCode;
    std::string fShaderCode;
    uint32_t m_vertex, m_fragment; // fragment shader and vertex shader id
};

#endif
