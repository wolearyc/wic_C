// ------------------------------------------------------------------------------------------------
// File:            Image.cpp
// ------------------------------------------------------------------------------------------------

#include "Image.h"
namespace wick
{
    Image::Image(Pair location, Texture* texture)
    {
        location_ = location;
        texture_ = texture;
    }
    Image::Image(const Image& other)
    {
        location_ = other.location_;
        texture_ = other.location_;
    }
    Image::Image()
    {
        location_ = Pair();
        texture_ = Texture();
    }

    void Image::paint(Window* window)
    {
        texture_ -> select();
    }
}
