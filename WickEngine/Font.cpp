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
    Font::Font(string filePath, unsigned short point)
    {
        FT_Init_FreeType(&library_);
        int error = FT_New_Face(library_, filePath.c_str(), 0, &face_);
        if(error != 0)
            throwError(W_FONT, "Could not load font file " + filePath);
        FT_Set_Char_Size(face_, 0, point*64, 0, 0);
        point_ = point;
        for(unsigned int i = 0; i < 256; i++)
        {
            textures_[i] = NULL;
        }
    }
    Font::Font(const Font& other)
    {
        library_ = other.library_;
        face_ = other.face_;
        point_ = other.point_;
        for(unsigned int i = 0; i < 256; i++)
        {
            textures_[i] = NULL;
        }
    }
    Font::Font()
    {
        library_ = NULL;
        face_ = NULL;
        point_ = 12;
        for(unsigned int i = 0; i < 256; i++)
        {
            textures_[i] = NULL;
        }
    }
    Font::~Font()
    {
        FT_Done_Face(face_);
        FT_Done_FreeType(library_);
        for(unsigned int i = 0; i < 256; i++)
        {
            if(textures_[i] != NULL)
            {
                delete(textures_[i]);
                textures_[i] = NULL;
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
        FT_Set_Char_Size(face_, 0, point*64, 0, 0);
        for(unsigned int i = 0; i < 256; i++)
        {
            if(textures_[i] != NULL)
            {
                delete(textures_[i]);
                textures_[i] = NULL;
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
            if(textures_[character] == NULL)
            {
                int glyphIndex = FT_Get_Char_Index(face_, character);
                FT_Load_Glyph(face_, glyphIndex, 0);
                if(face_->glyph->format != FT_GLYPH_FORMAT_BITMAP)
                    FT_Render_Glyph(face_->glyph, FT_RENDER_MODE_NORMAL);
                Pair dimensions = Pair(face_->glyph->bitmap.width, face_->glyph->bitmap.rows);
                texture = new Texture(face_->glyph->bitmap.buffer, dimensions, 1);
                textures_[character] = texture;
                images.push_back(Image(texture,
                                 Pair(xPen, (face_->glyph->metrics.height - face_->glyph->metrics.horiBearingY) / 64)));
                xPen += (face_->glyph->metrics.horiAdvance / 64);
            }

        }

        return(images);
    }
}
