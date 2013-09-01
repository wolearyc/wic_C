// ------------------------------------------------------------------------------------------------
// File:			Color.cpp
//-------------------------------------------------------------------------------------------------

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
	Color::Color(unsigned short red, unsigned short green, unsigned short blue)
	{
		setRed(red);
		setGreen(green);
		setBlue(blue);
		setAlpha(255);
	}
	Color::Color(unsigned short red, unsigned short green, unsigned short blue, unsigned short alpha)
          :Color(red, green, blue)
	{
		setAlpha(alpha);
	}
	Color::Color(const Color &other)
	{
		red_     = other.red_;
		glRed_   = other.glRed_;
		green_   = other.green_;
		glGreen_ = other.glGreen_;
		blue_    = other.blue_;
		glBlue_  = other.glBlue_;
		alpha_   = other.alpha_;
		glAlpha_ = other.glAlpha_;
	}
	Color::Color()
	      :Color(0,0,0,255)
	{
	}

	// Red methods.
	unsigned short Color::getRed()
	{
		return(red_);
	}
	void Color::setRed(unsigned short red)
	{
		red_ = red;
		if(red_ < 0 || red_ > 255)
		{
			throwWarning("Invalid red value");
			red_ = 255;
		}
		glRed_ = red_ / 255.f;
	}

	// Green methods.
	unsigned short Color::getGreen()
	{
		return(green_);
	}
	void Color::setGreen(unsigned short green)
	{
		green_ = green;
		if(green_ < 0 || green_ > 255)
		{
			throwWarning("Invalid green value");
		}
		glGreen_ = green_ / 255.f;
	}

	// Blue methods.
	unsigned short Color::getBlue()
	{
		return(blue_);
	}
	void Color::setBlue(unsigned short blue)
	{
		blue_ = blue;
		if(blue_ < 0 || blue_ > 255)
		{
			throwWarning("Invalid blue value");
		}
		glBlue_ = blue_ / 255.f;
	}

	unsigned short Color::getAlpha()
	{
		return(alpha_);
	}
	void Color::setAlpha(unsigned short alpha)
	{
		alpha_ = alpha;
		if(alpha_ < 0 || alpha_ > 255)
		{
			throwWarning("Invalid alpha value");
			alpha_ = 255;
		}
		glAlpha_ = alpha_ / 255.f;
	}

	void Color::select()
	{
	    glColor4f(glRed_, glGreen_, glBlue_, glAlpha_);
	}
}
