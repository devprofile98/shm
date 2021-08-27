#ifndef TEXTURE_H
#define TEXTURE_H

#include "Core.hpp"

#include <iostream>
#include <stdint.h>


class Texture{
public:
    // load image, gentexture buffer, bound the texture, generate texture and it's mipmap, free the image data
    Texture(const char* texture_path,uint32_t layout_location=0);
    ~Texture();

    uint32_t getID() const;

    // create 2D texture from format and data in width and height
    static unsigned int createTexture2D(GLint format = GL_RGBA,
                                        uint16_t width = 1024,
                                        uint16_t height = 1024,
                                        const GLvoid* data=nullptr);

private:
    uint32_t m_ID;

};

#endif
