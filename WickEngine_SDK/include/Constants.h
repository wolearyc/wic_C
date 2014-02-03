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
// File:    Constants.h
// ----------------------------------------------------------------------------

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "GL/gl.h"

// WickError
#define W_WICKERROR 0
#define W_PAINTABLE 1
#define W_ROTATEABLE 2
#define W_SCALEABLE 3
#define W_IMAGE 4
#define W_TEXTURE 5
#define W_POLYGON 6
#define W_QUAD 7
#define W_STATE 8
#define W_FONT 9
#define W_TEXT 10
#define W_BOUNDS 11
#define W_COLOR 12
#define W_PAIR 13
#define W_WWINDOW 14

// Texture
#define W_REPEAT GL_REPEAT
#define W_MIRRORED_REPEAT GL_REPEAT
#define W_CLAMP_TO_EDGE 2066
#define W_NEAREST GL_NEAREST
#define W_LINEAR GL_LINEAR
#define W_GREYSCALE 1
#define W_RGB 3
#define W_RGBA 4



#endif
