#include "CubeMaps.hpp"
#include "Logger.hpp"

// #define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "cube.h"

namespace SHM::opengl {
CubeMaps::CubeMaps() {}
CubeMaps::CubeMaps(std::vector<std::string> faces, std::shared_ptr<shader> sh) {
    mShader = sh;
    this->load(faces);
}

bool CubeMaps::load(std::vector<std::string> faces) {
    // first create the texture_slot
    // unsigned int textureId;
    SHM::Logger::error("Failed to load skybox Texture");

    glGenTextures(1, &this->m_cube_texture_id);
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_cube_texture_id);

    // load the texture
    int width, height, nrchannel;
    // upload texture to the gpu memory
    for (int i = 0; i < 6; i++) {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrchannel, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            SHM::Logger::error("Failed to load skybox Texture {} {}", faces[i], stbi_failure_reason());
        }
    }
    // setup texture properties
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    mShader->use();
    mShader->setInt("skybox", 1);
    glActiveTexture(GL_TEXTURE0 + 1);
    return true;
}

void CubeMaps::Draw(const glm::mat4 &view_mat, const glm::mat4 &proj_mat) {
    glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
    // glDepthMask(GL_FALSE);
    mShader->use();
    mShader->setMat4("view", glm::mat4(glm::mat3(view_mat)));
    // skyboxmShaderader->setMat4("view", m_renderer->getViewMatrix());
    mShader->setMat4("projection", proj_mat);
    // skybox cube
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_cube_texture_id);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth function back to default
}
} // namespace SHM::opengl