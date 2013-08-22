// ------------------------------------------------------------------------------------------------
// File:			Color.cpp
//-------------------------------------------------------------------------------------------------

#include "Color.h"
namespace wick
{
	Color Color::White = Color(255,255,255);
	Color Color::Silver = Color(208,208,208);
	Color Color::Gray = Color(128,128,128);
	Color Color::Black = Color(0,0,0);
	Color Color::Red = Color(255,0,0);
	Color Color::Maroon = Color(128,0,0);
	Color Color::Yellow = Color(255,255,0);
	Color Color::Olive = Color(128,128,0);
	Color Color::Lime = Color(0,255,0);
	Color Color::Green = Color(0,128,0);
	Color Color::Aqua = Color(0,255,255);
	Color Color::Teal = Color(0,128,128);
	Color Color::Blue = Color(0,0,255);
	Color Color::Navy = Color(0,0,128);
	Color Color::Fuchsia = Color(255,0,255);
	Color Color::Purple = Color(128,0,128);

	// Constructors.
	Color::Color(int red, int green, int blue)
	{
		setAlpha(255);
		setRed(red);
		setGreen(green);
		setBlue(blue);
		data_ = D3DCOLOR_ARGB(alpha_, red_, green_, blue_);
	}
	Color::Color(int alpha, int red, int green, int blue)
	{
		setAlpha(alpha);
		setRed(red);
		setGreen(green);
		setBlue(blue);
		data_ = D3DCOLOR_ARGB(alpha_, red_, green_, blue_);
	}
	Color::Color(const Color &other)
	{
		alpha_ = other.alpha_;
		red_ = other.red_;
		green_ = other.green_;
		blue_ = other.blue_;
		data_ = other.data_;
	}
	Color::Color()
	{
		setAlpha(255);
		setRed(0);
		setGreen(0);
		setBlue(0);
		data_ = D3DCOLOR_ARGB(alpha_, red_, green_ , blue_);
	}

	// Alpha methods.
	int Color::getAlpha()
	{
		return(alpha_);
	}
	void Color::setAlpha(int alpha)
	{
		if(alpha<0 || alpha>255)
		{
			wickThrowError("Invalid alpha value.");
		}
		alpha_ = alpha;
		data_ = D3DCOLOR_ARGB(alpha_, red_, green_, blue_);
	}

	// Red methods.
	int Color::getRed()
	{
		return(red_);
	}
	void Color::setRed(int red)
	{
		if(red<0 || red>255)
		{
			wickThrowError("Invalid red value.");
		}
		red_ = red;
		data_ = D3DCOLOR_ARGB(alpha_, red_, green_, blue_);
	}

	// Green methods.
	int Color::getGreen()
	{
		return(green_);
	}
	void Color::setGreen(int green)
	{
		if(green<0 || green>255)
		{
			wickThrowError("Invalid green value.");
		}
		green_ = green;
		data_ = D3DCOLOR_ARGB(alpha_, red_, green_, blue_);
	}

	// Blue methods.
	int Color::getBlue()
	{
		return(blue_);
	}
	void Color::setBlue(int blue)
	{
		if(blue<0 || blue>255)
		{
			wickThrowError("Invalid blue value.");
		}
		blue_ = blue;
		data_ = D3DCOLOR_ARGB(alpha_, red_, green_, blue_);
	}

	// Fetches DirectX data.
	D3DCOLOR Color::getData()
	{
		return(data_);
	}
}
