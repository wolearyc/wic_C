

#include "Texture.h"
namespace wick
{
    Texture::Texture(string filePath)
    {
        glGenTextures(1, &data_);
        unsigned char* image = SOIL_load_image(filePath.c_str(), &(dimensions_.x_), &(dimensions_.y_), 0, SOIL_LOAD_RGBA);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dimensions_.x_, dimensions_.y_, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
    }
    Texture::Texture(const Texture& other)
    {
        data_ = other.data_;
        dimensions_ = other.dimensions_;
    }
    Texture::Texture()
    {
        data_ = NULL;
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
