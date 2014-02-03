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
// File:    Text.h
// ----------------------------------------------------------------------------

#ifndef TEXT_H
#define TEXT_H
#include "Font.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
namespace wick
{
    class Text : public Paintable, public Rotateable, public Scaleable
    {
    public:
        Text(string message, Pair location, Font* font);
        Text(const Text& other);
        Text();

        void paint(Window* window);

        string getMessage();
        void setMessage(string message);

        void setLocation(Pair location);
        void setCenter(Pair center);
        void setRotation(float rotation);
        void setScale(Pair scale);

    protected:
        string message_;
        Font* font_;
        vector<Image> images_;
        Pair oldLocation_;
    };
}
#endif
