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
// File:    Font.h
// ----------------------------------------------------------------------------
#ifndef FONT_H
#define FONT_H
#ifdef _WIN64
    #define FONT_PATH_1 "C:/WINDOWS/Fonts/"
    #define FONT_PATH_2 "C:/WINDOWS/Fonts/"
#elif _WIN32
    #define FONT_PATH_1 "C:/WINDOWS/Fonts/"
    #define FONT_PATH_2 "C:/WINDOWS/Fonts/"
#elif __APPLE__
    #define FONT_PATH_1 "/Library/Fonts/"
    #define FONT_PATH_2 "/System/Library/Fonts/"
#elif __linux
    #define FONT_PATH_1 "/usr/share/fonts/"
    #define FONT_PATH_2 "/usr/local/share/fonts/"
#endif
#include "Image.h"
#include "WickException.h"
#include "Dependencies/FreeType/ft2build.h"
#include FT_FREETYPE_H
#include FT_BITMAP_H
#include <string>
using std::string;
#include <vector>
using std::vector;
namespace wick
{
    class Font
    {
    public:
        Font(string filePath, unsigned short point, Game* game, bool antialias);
        Font(string filePath, unsigned short point, Game* game);
        Font();
        Font(const Font& other);
        ~Font();
        unsigned short getPoint();
        void setPoint(unsigned short point);
        vector<Image> getImages(string message);
    private:
        FT_Library library_;
        FT_Face face_;
        unsigned short point_;
        bool antialias_;
        Texture* textures_[256];
    };
}
#endif
