// ------------------------------------------------------------------------------------------------
// File:            Texture.h
// Author:          Will O'Leary
// Documentation:
// ------------------------------------------------------------------------------------------------

#ifndef TEXTURE_H
#define TEXTURE_H
#include "Pair.h"
#include <string>
#include "SOIL.h"
#include "GL/gl.h"
#include <iostream>
#include "WickError.h"
using std::string;
namespace wick
{
    class Texture
    {
    public:
        Texture(string filePath);
        Texture(const Texture& other);
        Texture();
        ~Texture();

        Pair getDimensions();

        void select();
    protected:
        GLuint data_;
        Pair dimensions_;
    };
}
#endif
