// ------------------------------------------------------------------------------------------------
// File:            Texture.cpp
// ------------------------------------------------------------------------------------------------

#include "Texture.h"
namespace wick
{
    Texture::Texture(string filePath)
    {
        int x = 0;
        int y = 0;
        glGenTextures(1, &data_);
        glBindTexture(GL_TEXTURE_2D, data_);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        unsigned char* image = 0;
        image = SOIL_load_image(filePath.c_str(), &x, &y, 0, SOIL_LOAD_RGBA);
        if(image == 0)
        {
            throwError("Loading failed (" + filePath + ")");
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
        dimensions_ = Pair(x,y);
    }
    Texture::Texture(const Texture& other)
    {
        data_ = other.data_;
        dimensions_ = other.dimensions_;
    }
    Texture::Texture()
    {
        data_ = 0;
        dimensions_ = Pair();
    }
    Texture::~Texture()
    {
        glDeleteTextures(1, &data_);
    }

    Pair Texture::getDimensions()
    {
        return(dimensions_);
    }

    void Texture::select()
    {
        glBindTexture(GL_TEXTURE_2D, data_);
    }
}
