

#include "Texture.h"
namespace wick
{
    Texture::Texture(string filePath)
    {
        glGenTextures(1, &data_);
        int x = 0;
        int y = 0;
        unsigned char* image = SOIL_load_image(filePath.c_str(), &x, &y, 0, SOIL_LOAD_RGBA);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        dimensions_ = Pair(x,y);
        SOIL_free_image_data(image);
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
