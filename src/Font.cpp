/* ----------------------------------------------------------------------------
 * wick - a simple, object-oriented 2D game engine for Mac OSX written in C++
 * Copyright (C) 2013-2014  Will O'Leary
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------------------------
 * File:    Font.cpp
 * ----------------------------------------------------------------------------
 */
#include "Font.h"
namespace wick
{
    Font::Font(string filepath, unsigned short point, Game* game,
               bool antialias)
    {
        FT_Init_FreeType(&library_);
        int error = FT_New_Face(library_, filepath.c_str(), 0, &face_);
        if(error != 0)
        {
            error = FT_New_Face(library_,
                                (string("/Library/Fonts/") + filepath).c_str(),
                                0, &face_);
        }
        if(error != 0)
        {
            error = FT_New_Face(library_,
                                (string("/System/Library/Fonts/") +
                                 filepath).c_str(), 0, &face_);
        }
        if(error != 0)
        {
            FT_Done_FreeType(library_);
            throw(FileException(filepath));
        }
        else
        {
            for(unsigned int i = 0; i < 256; i++)
                textures_[i] = nullptr;
            point_ = point;
            Pair deviceResolution = game->getDeviceResolution();
            FT_Set_Char_Size(face_, 0, point*64, deviceResolution.x_,
                             deviceResolution.y_);
            antialias_ = antialias;
        }

    }
    Font::Font(string filepath, unsigned short point, Game* game)
    :Font(filepath, point, game, true)
    {
    }
    Font::Font()
    :library_(nullptr), face_(nullptr), point_(0), antialias_(false)
    {
        for(unsigned int i = 0; i < 256; i++)
            textures_[i] = nullptr;
    }
    Font::~Font()
    {
        FT_Done_Face(face_);
        FT_Done_FreeType(library_);
        for(unsigned int i = 0; i < 256; i++)
        {
            if(textures_[i] != nullptr)
            {
                delete(textures_[i]);
                textures_[i] = nullptr;
                delete[] textures_[i];
            }
        }
    }
    unsigned short Font::getPoint()
    {
        return(point_);
    }
    bool Font::isAntialised()
    {
        return(antialias_);
    }
    vector<Image> Font::getImages(string message)
    {
        vector<Image> images;
        int penX = 0;
        int previousGlyphIndex = 0;
        bool hasKerning = FT_HAS_KERNING(face_);
        for(unsigned int i = 0; i < message.length(); i++)
        {
            Texture* texture;
            char character = message[i];
            int glyphIndex = FT_Get_Char_Index(face_, character);
            if(antialias_)
                FT_Load_Glyph(face_, glyphIndex, FT_LOAD_FORCE_AUTOHINT);
            else
                FT_Load_Glyph(face_, glyphIndex, 0);
            if(textures_[character] == nullptr)
            {
                if(antialias_)
                {
                    FT_Render_Glyph(face_->glyph, FT_RENDER_MODE_NORMAL);
                    Pair dimensions = Pair(face_->glyph->bitmap.width,
                                           face_->glyph->bitmap.rows);
                    texture = new Texture(face_->glyph->bitmap.buffer,
                                          dimensions, WickFormat::GREYSCALE);
                    textures_[character] = texture;
                }
                else
                {
                    FT_Render_Glyph(face_->glyph, FT_RENDER_MODE_MONO);
                    FT_Bitmap target;
                    FT_Bitmap_New(&target);
                    int error = FT_Bitmap_Convert(library_,
                                                  &(face_->glyph->bitmap),
                                                  &target, 1);
                    Pair dimensions = Pair(target.width, target.rows);
                    texture = new Texture(target.buffer, dimensions,
                                          WickFormat::MONO);
                    FT_Bitmap_Done(library_, &target);
                    Texture* pointer = textures_[character];
                    textures_[character] = texture;
                }
            }
            texture = textures_[character];
            if(hasKerning && previousGlyphIndex != 0)
            {
                FT_Vector delta;
                FT_Get_Kerning(face_, previousGlyphIndex, glyphIndex,
                               FT_KERNING_UNFITTED, &delta);
                penX += delta.x;
            }
            previousGlyphIndex = glyphIndex;
            Image image = Image(Pair(penX, (face_->glyph->metrics.horiBearingY - face_->glyph->metrics.height)/64), texture);
            images.push_back(image);
            penX += face_->glyph->advance.x / 64;
        }
        return(images);
    }
}
