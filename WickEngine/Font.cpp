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
// File:    Font.cpp
// ----------------------------------------------------------------------------
#include "Font.h"
namespace wick
{
    Font::Font(string filePath, unsigned short point, bool antialias)
         :point_(point), antialias_(antialias)
    {
        FT_Init_FreeType(&library_);
        int error = FT_New_Face(library_, filePath.c_str(), 0, &face_);
        if(error != 0)
            throwError(W_FONT, "Could not load font " + filePath);
        FT_Set_Char_Size(face_, 0, point*64, 0, 0);
        for(unsigned int i = 0; i < 256; i++)
            textures_[i] = 0;
    }
    Font::Font(string filePath, unsigned short point)
         :Font(filePath, point, true)
    {
    }
    Font::Font()
         :library_(0), face_(0), point_(12), antialias_(true)
    {
        for(unsigned int i = 0; i < 256; i++)
            textures_[i] = 0;
    }
    Font::Font(const Font& other)
         :library_(other.library_), face_(other.face_), point_(other.point_),
          antialias_(other.antialias_)
    {
        for(unsigned int i = 0; i < 256; i++)
            textures_[i] = 0;
    }
    Font::~Font()
    {
        FT_Done_Face(face_);
        FT_Done_FreeType(library_);
        for(unsigned int i = 0; i < 256; i++)
        {
            if(textures_[i] != 0)
            {
                delete(textures_[i]);
                textures_[i] = 0;
            }
        }
    }
    unsigned short Font::getPoint()
    {
        return(point_);
    }
    void Font::setPoint(unsigned short point)
    {
        point_ = point;
        FT_Set_Char_Size(face_, 0, point_*64, 0, 0);
        for(unsigned int i = 0; i < 256; i++)
        {
            if(textures_[i] != 0)
            {
                delete(textures_[i]);
                textures_[i] = 0;
            }
        }
    }
    vector<Image> Font::getImages(string message)
    {
        vector<Image> images;
        int xPen = 0;
        for(unsigned int i = 0; i < message.length(); i++)
        {
            Texture* texture;
            char character = message[i];
            if(textures_[character] == 0)
            {
                int glyphIndex = FT_Get_Char_Index(face_, character);
                FT_Load_Glyph(face_, glyphIndex, 0);
                if(antialias_)
                    FT_Render_Glyph(face_->glyph, FT_RENDER_MODE_NORMAL);
                else
                    FT_Render_Glyph(face_->glyph, FT_RENDER_MODE_MONO);
                Pair dimensions = Pair(face_->glyph->bitmap.width,
                                       face_->glyph->bitmap.rows);
                texture = new Texture(face_->glyph->bitmap.buffer, dimensions,
                                      W_GREYSCALE);
                textures_[character] = texture;
            }
            texture = textures_[character];
            Image image = Image(Pair(xPen, face_->glyph->metrics.height -
                                face_->glyph->metrics.horiBearingY), texture);
            images.push_back(image);
            xPen += (face_->glyph->metrics.horiAdvance / 64);
        }
        return(images);
    }
}
