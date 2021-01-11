#ifndef TEXTURE_H
#define TEXTURE_H

#include "Core.hpp"

#include<iostream>
#include <stdint.h>


class Texture{
public:
    // load image, gentexture buffer, bound the texture, generate texture and it's mipmap, free the image data
    Texture(const char* texture_path,uint32_t layout_location=0);
    ~Texture();

    uint32_t getID() const;

private:
    uint32_t m_ID;

};

#endif