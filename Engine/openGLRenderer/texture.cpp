#include "texture.hpp"
#include "Logger.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char *texture_path, uint32_t layout_location) {
    int width, height, channel;
    unsigned char *data = stbi_load(texture_path, &width, &height, &channel, 0);
    glGenTextures(1, &m_ID);
    glActiveTexture(GL_TEXTURE0 + layout_location);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (data) {
        glBindTexture(GL_TEXTURE_2D, m_ID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        // std::cout << " Texture loaded successfuly" << std::endl;
        SHM::Logger::debug("Texture [{}] loaded successfuly", texture_path);
    } else {
        // std::cout << " Failed to load texture from source " << std::endl;
        SHM::Logger::error("Failed to load texture from [{}] with error:\n\t{}", texture_path, stbi_failure_reason());
    }

    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(GL_TEXTURE_2D, &m_ID);
    // std::cout << " TEXTURE WITH ID: " << m_ID << " DESTROYED!" << std::endl;
    SHM::Logger::debug("Texture with ID: {} destroyed!", m_ID);
}

uint32_t Texture::getID() const { return m_ID; }

unsigned int Texture::createTexture2D(GLint format, uint16_t width, uint16_t height, const GLvoid *data) {
    unsigned int texture_id;
    // glActiveTexture(GL_TEXTURE0 + Model::texture_layout_counter);
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return texture_id;
}
