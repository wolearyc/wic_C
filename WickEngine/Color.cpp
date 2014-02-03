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
// File:    Color.cpp
// ----------------------------------------------------------------------------

#include "Color.h"
namespace wick
{
	Color Color::White   = Color(255,255,255);
	Color Color::Silver  = Color(208,208,208);
	Color Color::Gray    = Color(128,128,128);
	Color Color::Black   = Color(0,0,0);
	Color Color::Red     = Color(255,0,0);
	Color Color::Maroon  = Color(128,0,0);
	Color Color::Yellow  = Color(255,255,0);
	Color Color::Orange  = Color(255,165,0);
	Color Color::Olive   = Color(128,128,0);
	Color Color::Lime    = Color(0,255,0);
	Color Color::Green   = Color(0,128,0);
	Color Color::Aqua    = Color(0,255,255);
	Color Color::Teal    = Color(0,128,128);
	Color Color::Blue    = Color(0,0,255);
	Color Color::Navy    = Color(0,0,128);
	Color Color::Fuchsia = Color(255,0,255);
	Color Color::Purple  = Color(128,0,128);

	// Constructors.
	Color::Color(unsigned char red, unsigned char green, unsigned char blue)
	{
		setRed(red);
		setGreen(green);
		setBlue(blue);
		setAlpha(255);
	}
	Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
          :Color(red, green, blue)
	{
		setAlpha(alpha);
	}
	Color::Color(const Color &other)
	{
		red_     = other.red_;
		green_   = other.green_;
		blue_    = other.blue_;
		alpha_   = other.alpha_;
	}
	Color::Color()
	      :Color(255,255,255,255)
	{
	}

	unsigned char Color::getRed()
	{
		return(red_);
	}
	void Color::setRed(unsigned char red)
	{
		red_ = red;
		if(red_ > 255)
		{
			throwWarning(W_COLOR, "Invalid red value");
			red_ = 255;
		}
	}
	unsigned char Color::getGreen()
	{
		return(green_);
	}
	void Color::setGreen(unsigned char green)
	{
		green_ = green;
		if(green_ > 255)
		{
			throwWarning(W_COLOR, "Invalid green value");
			green_ = 255;
		}
	}
	unsigned char Color::getBlue()
	{
		return(blue_);
	}
	void Color::setBlue(unsigned char blue)
	{
		blue_ = blue;
		if(blue_ > 255)
		{
			throwWarning(W_COLOR, "Invalid blue value");
			blue_ = 255;
		}
	}

	unsigned char Color::getAlpha()
	{
		return(alpha_);
	}
	void Color::setAlpha(unsigned char alpha)
	{
		alpha_ = alpha;
		if(alpha_ > 255)
		{
			throwWarning(W_COLOR, "Invalid alpha value");
			alpha_ = 255;
		}
	}

	void Color::select()
	{
	    glColor4ub(red_, green_, blue_, alpha_);
	}
}
