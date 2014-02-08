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
// File:    WickError.h
// ----------------------------------------------------------------------------
#ifndef WICKERROR_H
#define WICKERROR_H
#include <cstdlib>
#include <iostream>
#include <string>
using std::string;
namespace wick
{
        enum WickLocation
        {
            W_WICKERROR, W_PAINTABLE, W_ROTATEABLE, W_SCALEABLE, W_IMAGE,
            W_TEXTURE, W_POLYGON, W_QUAD, W_STATE, W_FONT, W_TEXT, W_BOUNDS,
            W_COLOR, W_PAIR, W_WINDOW
        };
        extern string wickVersion_;
        void print(string message);
        void throwWarning(enum WickLocation location, string message);
        void throwError(enum WickLocation location, string message);
        string getName(enum WickLocation location);
}
#endif
