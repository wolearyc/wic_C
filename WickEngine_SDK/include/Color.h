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
// File:    Color.h
// ----------------------------------------------------------------------------
#ifndef COLOR_H
#define COLOR_H
#include "GL/gl.h"
#include "WickError.h"
namespace wick
{
	class Color
	{
	public:
		static Color White;
		static Color Silver;
		static Color Gray;
		static Color Black;
		static Color Red;
		static Color Maroon;
		static Color Yellow;
		static Color Orange;
		static Color Olive;
		static Color Lime;
		static Color Green;
		static Color Aqua;
		static Color Teal;
		static Color Blue;
		static Color Navy;
		static Color Fuchsia;
		static Color Purple;
		Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
		Color(unsigned char red, unsigned char green, unsigned char blue);
		Color();
        Color(const Color& other);
		unsigned char getRed();
		void setRed(unsigned char red);
		unsigned char getGreen();
		void setGreen(unsigned char green);
		unsigned char getBlue();
		void setBlue(unsigned char blue);
		unsigned char getAlpha();
		void setAlpha(unsigned char alpha);
		void select();
	protected:
		unsigned char red_;
		unsigned char green_;
		unsigned char blue_;
		unsigned char alpha_;
	};
}
#endif
