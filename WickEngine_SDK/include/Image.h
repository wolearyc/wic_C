// ------------------------------------------------------------------------------------------------
// File:            Image.h
// Author:          Will O'Leary
// Documentation:
// ------------------------------------------------------------------------------------------------

#ifndef IMAGE_H
#define IMAGE_H
#include "Texture.h"
namespace wick
{
    class Image
    {
    public:
        Image(Pair location, Texture* texture);
        Image(const Image& other);
        Image();

        void paint(Window* window);
    protected:
        Pair location_;
        Texture* texture_;
    };
}

#endif
