// ------------------------------------------------------------------------------------------------
// File:			Button.cpp 
//-------------------------------------------------------------------------------------------------

#include "Button.h"
namespace wick
{
	// Constructors.
	Button::Button(Image off, Image on, Pair location, Box target) 
		  : Paintable(), Rotateable(), Scaleable()
	{
		off_ = off;
		on_ = on;
		location_ = location;
		on_.setLocation(location_);
		off_.setLocation(location_);
		target_ = HitBox(location_, target);
		over_ = false;
		pressed_ = false;
	}
	Button::Button(const Button& other) : Paintable(other), Rotateable(other), Scaleable(other)
	{
		off_ = other.off_;
		on_ = other.on_;
		target_ = other.target_;
		over_ = other.over_;
		pressed_ = other.pressed_;
	}
	Button::Button() : Paintable(), Rotateable(), Scaleable()
	{
		off_ = Image();
		on_ = Image();
		target_ = HitBox();
		over_ = false;
		pressed_ = false;
	}

	// Updates logic.
	void Button::update(Input* input, int fps, Graphics* graphics)
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
			pressed_ = true;
		}
		else
		{
			pressed_ = false;
		}
	}

	// Paints Button to screen.
	void Button::paint(Graphics* graphics)
	{
		if(!over_ || pressed_)
		{
			off_.paint(graphics);
		}
		else
		{
			on_.paint(graphics);
		}
	}

	// Sets location.
	void Button::setLocation(Pair location)
	{
		Paintable::setLocation(location);
		off_.setLocation(location_);
		on_.setLocation(location_);
		target_.setLocation(location_);
	}

	// Rotation methods.
	void Button::setRotation(double rotation)
	{
		Rotateable::setRotation(rotation);
		off_.setRotation(rotation_);
		on_.setRotation(rotation_);
	}
	void Button::setRotationInDegrees(double rotation)
	{
		Rotateable::setRotationInDegrees(rotation);
		off_.setRotation(rotation_);
		on_.setRotation(rotation_);
	}

	// Sets center.
	void Button::setCenter(Pair center)
	{
		Rotateable::setCenter(center);
		off_.setCenter(center);
		on_.setCenter(center);
	}

	// Sets scale.
	void Button::setScale(Pair scale)
	{
		Scaleable::setScale(scale);
		off_.setScale(scale);
		on_.setScale(scale);
	}

	// Returns whether or not the curser is over the button.
	bool Button::mouseOver()
	{
		return(over_);
	}

	// Button press methods.
	bool Button::pressed()
	{
		return(pressed_);
	}
	void Button::setPressed(bool pressed)
	{
		pressed_ = pressed;
	}
}