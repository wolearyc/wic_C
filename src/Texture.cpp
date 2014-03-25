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
    Texture::Texture(unsigned char* buffer, Pair dimensions,
                     enum WickFormat format, enum WickFilter filter)
            :dimensions_(dimensions)
    {
        if(dimensions.x_ < 0)
        {
            throw(ParameterException("dimensions (x value)", ">= 0", "0"));
            dimensions.x_ = 0;
        }
        if(dimensions.y_ < 0)
        {
            throw(ParameterException("dimensions (y value)", ">= 0", "0"));
            dimensions.y_ = 0;
        }
        unsigned char* formattedBuffer = formatBuffer(buffer, format);
        if(formattedBuffer == nullptr)
        {
            throw(WickException((string) "dimensions and/or format are not " +
                                (string) "compatible with buffer, texture not" +
                                (string) " constructed", false));
        }
        else
        {
            glGenTextures(1, &data_);
            glBindTexture(GL_TEXTURE_2D, data_);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int) filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int) filter);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dimensions_.x_ + 2,
                         dimensions_.y_ + 2, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                         formattedBuffer);
            delete[] formattedBuffer;
        }
    }
    Texture::Texture(unsigned char* buffer, Pair dimensions,
                     enum WickFormat format)
            :Texture(buffer, dimensions, format, WickFilter::NEAREST)
    {
    }
    Texture::Texture(string filepath, enum WickFilter filter)
    {
        unsigned char* buffer = nullptr;
        int x = 0;
        int y = 0;
        buffer = SOIL_load_image(filepath.c_str(), &x, &y, 0, SOIL_LOAD_RGBA);
        dimensions_ = Pair(x,y);
        if(buffer == nullptr)
            throw(FileException(filepath));
        unsigned char* formattedBuffer = formatBuffer(buffer, WickFormat::RGBA);
        if(formattedBuffer == nullptr)
        {
            throw(WickException((string) "texture loading error, " +
                                (string) "texture not constructed", false));
        }
        else
        {
            glGenTextures(1, &data_);
            glBindTexture(GL_TEXTURE_2D, data_);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int) filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int) filter);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dimensions_.x_ + 2,
                         dimensions_.y_ + 2, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                         formattedBuffer);
            SOIL_free_image_data(buffer);
            delete[] formattedBuffer;
        }
    }
    Texture::Texture(string filepath)
            :Texture(filepath, WickFilter::NEAREST)
    {
    }
    Texture::Texture()
            :data_(0), dimensions_(Pair())
    {
    }
    Texture::Texture(const Texture& other)
            :data_(other.data_), dimensions_(other.dimensions_)
    {
    }
    Texture::~Texture()
    {
        glDeleteTextures(1, &data_);
        data_ = 0;
    }
    Pair Texture::getDimensions()
    {
        return(dimensions_);
    }
    void Texture::select()
    {
        glBindTexture(GL_TEXTURE_2D, data_);
    }
    unsigned char* Texture::formatBuffer(unsigned char* buffer,
                                         enum WickFormat format)
    {
        try
        {
            int xDimension = (int) (dimensions_.x_ + 2) * 4;
            int yDimension = (int) dimensions_.y_ + 2;
            unsigned char temp[xDimension][yDimension];
            for(unsigned int y = 0; y < yDimension; y++)
            {
                for(unsigned int x = 0; x < xDimension; x+=4)
                {
                    temp[x][y] = 255;
                    temp[x+1][y] = 255;
                    temp[x+2][y] = 255;
                    temp[x+3][y] = 0;
                }
            }
            int bufferIndex = 0;
            for(unsigned int y = 1; y < yDimension - 1; y++)
            {
                for(unsigned int x = 4; x < xDimension - 4; x+=4)
                {
                    if(format == WickFormat::MONO)
                    {
                        temp[x][y] = 255;
                        temp[x+1][y] = 255;
                        temp[x+2][y] = 255;
                        unsigned char character = buffer[bufferIndex];
                        if(character == 0)
                            temp[x+3][y] = 0;
                        else
                            temp[x+3][y] = 255;
                        bufferIndex++;
                    }
                    else if(format == WickFormat::GREYSCALE)
                    {
                        temp[x][y] = 255;
                        temp[x+1][y] = 255;
                        temp[x+2][y] = 255;
                        temp[x+3][y] = buffer[bufferIndex];
                        bufferIndex++;
                    }
                    else if(format == WickFormat::RGB)
                    {
                        temp[x][y] = buffer[bufferIndex];
                        temp[x+1][y] = buffer[bufferIndex+1];
                        temp[x+2][y] = buffer[bufferIndex+2];
                        temp[x+3][y] = 255;
                        bufferIndex += 3;
                    }
                    else if(format == WickFormat::RGBA)
                    {
                        temp[x][y] = buffer[bufferIndex];
                        temp[x+1][y] = buffer[bufferIndex+1];
                        temp[x+2][y] = buffer[bufferIndex+2];
                        temp[x+3][y] = buffer[bufferIndex+3];
                        bufferIndex+=4;
                    }
                }
            }
            unsigned char* formattedBuffer = new unsigned char [xDimension *
                                                                yDimension];
            int formattedBufferIndex = 0;
            for(unsigned int y = 0; y < yDimension; y++)
            {
                for(unsigned int x = 0; x < xDimension; x++)
                {
                    formattedBuffer[formattedBufferIndex] = temp[x][y];
                    formattedBufferIndex++;
                }
            }
            return(formattedBuffer);
        }
        catch(...)
        {
            return(nullptr);
        }
    }
}
