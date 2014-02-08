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
// File:    WickError.cpp
// ----------------------------------------------------------------------------
#include "WickError.h"
namespace wick
{
    string wickVersion_ = "0.1.2";
    void print(string message)
    {
            std::cout << message + "\n";
    }
    void throwWarning(enum WickLocation location, string message)
    {
            std::cerr << "WARNING - " + getName(location) + " : " + message
                         + "\n";
    }
    void throwError(enum WickLocation location, string message)
    {
            std::cerr << "ERROR --- " + getName(location) + " : " + message
                         + "\n";
            print("\nTerminated");
            std::exit(1);
    }
    string getName(enum WickLocation location)
    {
        switch(location)
        {
        case W_WICKERROR:
            return("WickError ");
        case W_PAINTABLE:
            return("Paintable ");
        case W_ROTATEABLE:
            return("Rotateable");
        case W_SCALEABLE:
            return("Scaleable ");
        case W_IMAGE:
            return("Image     ");
        case W_TEXTURE:
            return("Texture   ");
        case W_POLYGON:
            return("Polygon   ");
        case W_QUAD:
            return("Quad      ");
        case W_STATE:
            return("State     ");
        case W_FONT:
            return("Font      ");
        case W_TEXT:
            return("Text      ");
        case W_BOUNDS:
            return("Bounds    ");
        case W_COLOR:
            return("Color     ");
        case W_PAIR:
            return("Pair      ");
        case W_WINDOW:
            return("WWindow   ");
        default:
            return("Unknown   ");
        }
        return("Unknown   ");
    }
}
