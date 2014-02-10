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
// File:    WickException.h
// ----------------------------------------------------------------------------
#ifndef WICKEXCEPTION_H
#define WICKEXCEPTION_H
#include "WickUtility.h"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
using std::string;
namespace wick
{
    enum WickLocation
    {
        W_UNKNOWN, W_WICKEXCEPTION, W_PAINTABLE, W_ROTATEABLE, W_SCALEABLE,
        W_IMAGE, W_TEXTURE, W_POLYGON, W_QUAD, W_STATE, W_FONT, W_TEXT,
        W_BOUNDS, W_COLOR, W_PAIR, W_WINDOW, W_UTILITY
    };
    class WickException : public std::exception
    {
    public:
        WickException(enum WickLocation, int id, string information);
        WickException(enum WickLocation location, int id);
        WickException();
        const char* what();
        void handle();
    private:
        enum WickLocation location_;
        int id_;
        string information_;
        string message_;
        bool fatal_;
    };
}
#endif
