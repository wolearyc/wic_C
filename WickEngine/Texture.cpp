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
// File:    Texture.cpp
// ----------------------------------------------------------------------------

#include "Texture.h"
namespace wick
{
    Texture::Texture(string filePath, int wrap, int filter)
    {
        glGenTextures(1, &data_);
        glBindTexture(GL_TEXTURE_2D, data_);
        if(wrap != W_REPEAT && wrap != W_MIRRORED_REPEAT &&
           wrap != W_CLAMP_TO_EDGE)
        {
            throwWarning(W_TEXTURE, "Invalid wrap value");
            wrap = W_REPEAT;
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
        if(filter != W_NEAREST && filter != W_LINEAR)
        {
            throwWarning(W_TEXTURE, "Invalid filter value");
            filter = W_NEAREST;
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

        unsigned char* buffer = 0;
        int x = 0;
        int y = 0;
        buffer = SOIL_load_image(filePath.c_str(), &x, &y, 0, SOIL_LOAD_RGBA);
        dimensions_ = Pair(x,y);

        if(buffer == 0)
            throwError(W_TEXTURE, "Loading failed (" + filePath + ")");
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, buffer);
        SOIL_free_image_data(buffer);
    }

    Texture::Texture(string filePath)
            :Texture(filePath, W_REPEAT, W_NEAREST)
    {
    }
    Texture::Texture(unsigned char* buffer, Pair dimensions,
                     unsigned short bytes, int wrap, int filter)
    {
        glGenTextures(1, &data_);
        glBindTexture(GL_TEXTURE_2D, data_);
        if(wrap != W_REPEAT && wrap != W_MIRRORED_REPEAT &&
           wrap != W_CLAMP_TO_EDGE)
        {
            throwWarning(W_TEXTURE, "Invalid wrap value");
            wrap = W_REPEAT;
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
        if(filter != W_NEAREST && filter != W_LINEAR)
        {
            throwWarning(W_TEXTURE, "Invalid filter value");
            filter = W_NEAREST;
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);


        dimensions_ = dimensions;
        unsigned char rgbaBuffer[(int) (dimensions.x_ * dimensions.y_) * 4];
        for(unsigned int i = 0; i < sizeof(rgbaBuffer); i+=4)
        {
            if(bytes == W_GREYSCALE)
            {
                rgbaBuffer[i] = 255;
                rgbaBuffer[i+1] = 255;
                rgbaBuffer[i+2] = 255;
                rgbaBuffer[i+3] = buffer[i/4];
            }
            else if(bytes == W_RGB)
            {
                rgbaBuffer[i] = buffer[i/4];
                rgbaBuffer[i+1] = buffer[i/4+1];
                rgbaBuffer[i+2] = buffer[i/4+2];
                rgbaBuffer[i+3] = 255;
            }
            else if(bytes != W_RGBA)
                throwError(W_TEXTURE, "Invalid bytes");
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dimensions.x_, dimensions.y_, 0, GL_RGBA, GL_UNSIGNED_BYTE, &rgbaBuffer[0]);
    }
    Texture::Texture(unsigned char* buffer, Pair dimensions, unsigned short bytes)
            :Texture(buffer, dimensions, bytes, W_REPEAT, W_NEAREST)
    {
    }
    Texture::Texture(const Texture& other)
    {
        data_       = other.data_;
        dimensions_ = other.dimensions_;
    }
    Texture::Texture()
    {
        data_       = 0;
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
