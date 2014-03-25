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
	const Color Color::White   = Color(255,255,255);
	const Color Color::Silver  = Color(208,208,208);
	const Color Color::Gray    = Color(128,128,128);
	const Color Color::Black   = Color(0,0,0);
    const Color Color::Red     = Color(255,0,0);
	const Color Color::Maroon  = Color(128,0,0);
	const Color Color::Yellow  = Color(255,255,0);
	const Color Color::Orange  = Color(255,165,0);
	const Color Color::Olive   = Color(128,128,0);
	const Color Color::Lime    = Color(0,255,0);
	const Color Color::Green   = Color(0,128,0);
	const Color Color::Aqua    = Color(0,255,255);
	const Color Color::Teal    = Color(0,128,128);
	const Color Color::Blue    = Color(0,0,255);
	const Color Color::Navy    = Color(0,0,128);
	const Color Color::Fuchsia = Color(255,0,255);
	const Color Color::Purple  = Color(128,0,128);
	Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
          :red_(red), green_(green), blue_(blue), alpha_(alpha)
	{
		if(red_ > 255)
		{
			throw(ParameterException("red", "0-255", "255"));
			red_ = 255;
		}
		if(green_ > 255)
		{
			throw(ParameterException("green", "0-255", "255"));
			green_ = 255;
		}
		if(blue_ > 255)
		{
			throw(ParameterException("blue", "0-255", "255"));
			blue_ = 255;
		}
	    if(alpha_ > 255)
		{
			throw(ParameterException("alpha", "0-255", "255"));
			alpha_ = 255;
		}
	}
	Color::Color(unsigned char red, unsigned char green, unsigned char blue)
          :Color(red, green, blue, 255)
	{
	}

	Color::Color(const Color &other)
          :red_(other.red_), green_(other.green_), blue_(other.blue_),
           alpha_(other.alpha_)
	{
	}
	Color::Color()
	      :Color(255,255,255)
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
			throw(ParameterException("red", "0-255", "255"));
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
			throw(ParameterException("green", "0-255", "255"));
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
			throw(ParameterException("blue", "0-255", "255"));
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
			throw(ParameterException("alpha", "0-255", "255"));
			alpha_ = 255;
		}
	}
	void Color::select()
	{
	    glColor4ub(red_, green_, blue_, alpha_);
	}
}
