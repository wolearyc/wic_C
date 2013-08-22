// ------------------------------------------------------------------------------------------------
// File:			Toggle.cpp 
//-------------------------------------------------------------------------------------------------

#include "Toggle.h"
namespace wick
{
	// Constructors.
	Toggle::Toggle(Image off, Image on, Pair location, Box target)
		  : Button(off, on, location, target)
	{
	}
	Toggle::Toggle(const Toggle& other) : Button(other)
	{
	}
	Toggle::Toggle() : Button()
	{
	}

	// Updates logic.
	void Toggle::update(Input* input, int fps, Graphics* graphics)
	{
		if(target_.intersects(input->getMouseLocation()))
		{
			over_ = true;
		}
		else
		{
			over_ = false;
		}
		if(input->isKeyPressed("LMB") && over_)
		{
			pressed_ = !pressed_;
		}
	}

	// Paints Toggle to screen.
	void Toggle::paint(Graphics* graphics)
	{
		if(pressed_)
		{
			on_.paint(graphics);
		}
		else
		{
			off_.paint(graphics);
		}
	}
}