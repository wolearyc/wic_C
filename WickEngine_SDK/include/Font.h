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
#include <ft2build.h>
#include <algorithm>
#include FT_FREETYPE_H
#include <string>
#include <vector>
#include "WickError.h"
#include "Image.h"
using std::vector;
using std::string;
namespace wick
{
    class Font
    {
    public:
        Font(string filePath, unsigned short point);
        Font(const Font& other);
        Font();
        ~Font();

        unsigned short getPoint();
        void setPoint(unsigned short point);

        vector<Image> getImages(string message);

    protected:
        FT_Library library_;
        FT_Face face_;
        unsigned short point_;
        Texture* textures_[256];
    };
}
#endif
