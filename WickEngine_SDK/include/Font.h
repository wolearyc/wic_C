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
#include "Image.h"
#include "WickError.h"
#include "FreeType/ft2build.h"
#include FT_FREETYPE_H
#include <string>
using std::string;
#include <vector>
using std::vector;
namespace wick
{
    class Font
    {
    public:
        Font(string filePath, unsigned short point, bool antialias);
        Font(string filePath, unsigned short point);
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
