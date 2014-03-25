// ----------------------------------------------------------------------------
// The Wick Engine - A simple, 2D, cross platform game library written in C++.
// Copyright (C) 2013-2014  Will O'Leary
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------
// File:    Texture.h
// ----------------------------------------------------------------------------
#ifndef TEXTURE_H
#define TEXTURE_H
#include "Pair.h"
#include "WickException.h"
#include "Dependencies/SOIL/SOIL.h"
#include "OpenGL/gl.h"
#include <iostream>
#include <string>
using std::string;
namespace wick
{
    enum class WickFilter
    {
        NEAREST = GL_NEAREST, LINEAR = GL_LINEAR
    };
    enum WickFormat
    {
        MONO, GREYSCALE, RGB, RGBA
    };
    class Texture
    {
    public:
        Texture(unsigned char* buffer, Pair dimensions, enum WickFormat format,
                enum WickFilter filter);
        Texture(unsigned char* buffer, Pair dimensions,
                enum WickFormat format);
        Texture(string filepath, enum WickFilter filter);
        Texture(string filepath);
        Texture();
        Texture(const Texture& other);
        ~Texture();
        Pair getDimensions();
        void select();
    private:
        unsigned int data_;
        Pair dimensions_;
        unsigned char* formatBuffer(unsigned char* buffer, enum WickFormat format);
    };
}
#endif
