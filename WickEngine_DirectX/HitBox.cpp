// ------------------------------------------------------------------------------------------------
// File:			HitBox.cpp
//-------------------------------------------------------------------------------------------------

#include "HitBox.h"
namespace wick
{

	// Constructors.
	HitBox::HitBox(Pair location, Pair upperLeft, Pair lowerRight):Box(upperLeft, lowerRight)
	{
		location_ = location;
	}
	HitBox::HitBox(Pair location, int width, int height):Box(width, height)
	{
		location_ = location;
	}
	HitBox::HitBox(Pair location, Pair upperLeft, int width, int height):Box(upperLeft, width, 
				   height)
	{
		location_ = location;
	}
	HitBox::HitBox(Pair location, int upperLeftX, int upperLeftY, int lowerRightX, int lowerRightY)
		   :Box(upperLeftX, upperLeftY, lowerRightX, lowerRightY)
	{
		location_ = location;
	}
	HitBox::HitBox(Pair location, Box box)
	{
		upperLeft_ = box.getUpperLeft();
		lowerRight_ = box.getLowerRight();
		location_ = location;
	}
	HitBox::HitBox(const HitBox& other):Box(other)
	{
		location_ = other.location_;
	}
	HitBox::HitBox():Box()
	{
		location_ = Pair();
	}

	// Location methods.
	Pair HitBox::getLocation()
	{
		return(location_);
	}
	void HitBox::setLocation(Pair location)
	{
		location_ = location;
	}

	// Intersection methods.
	bool HitBox::intersects(const HitBox& other)
	{
		return(upperLeft_.x_ + location_.x_ <= other.lowerRight_.x_ + other.location_.x_ && 
			   lowerRight_.x_ + location_.x_ >= other.upperLeft_.x_ + other.location_.x_ &&
			   upperLeft_.y_ + location_.y_ <= other.lowerRight_.y_ + other.location_.y_ && 
			   lowerRight_.y_ + location_.y_ >= other.upperLeft_.y_ + other.location_.y_);
	}
	bool HitBox::intersects(const Pair& pair)
	{
		return(upperLeft_.x_ + location_.x_ <= pair.x_ &&
			   lowerRight_.x_ + location_.x_ >= pair.x_ &&
			   upperLeft_.y_ + location_.y_ <= pair.y_ &&
			   lowerRight_.y_ + location_.y_ >= pair.y_);
	}
}