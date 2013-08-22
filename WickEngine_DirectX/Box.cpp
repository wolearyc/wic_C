// ------------------------------------------------------------------------------------------------
// File:			Box.cpp
// ------------------------------------------------------------------------------------------------
#include "Box.h"
namespace wick
{

	// Constructors.
	Box::Box(Pair upperLeft, Pair lowerRight)
	{
		setUpperLeftAndLowerRight(upperLeft, lowerRight);
	}
	Box::Box(int width, int height)
	{
		setUpperLeftAndLowerRight(Pair(),Pair(width,height));
	}
	Box::Box(Pair upperLeft, int width, int height)
	{
		setUpperLeftAndLowerRight(upperLeft, upperLeft + Pair(width,height));
	}
	Box::Box(int upperLeftX, int upperLeftY, int lowerRightX, int lowerRightY)
	{
		setUpperLeftAndLowerRight(Pair(upperLeftX,upperLeftY), Pair(lowerRightX,lowerRightY));
	}
	Box::Box(const Box& other)
	{
		upperLeft_ = other.upperLeft_;
		lowerRight_ = other.lowerRight_;
	}
	Box::Box()
	{
		upperLeft_ = Pair();
		lowerRight_ = Pair();
	}

	// Upper-left coordinate methods.
	Pair Box::getUpperLeft()
	{
		return(upperLeft_);
	}
	void Box::setUpperLeft(Pair upperLeft)
	{
		if(upperLeft.x_>lowerRight_.x_ || upperLeft.y_>lowerRight_.y_)
		{
			wickThrowError("Invalid upper-left coordinate.");
		}
		upperLeft_ = upperLeft;
	}

	// Lower-right coordinate methods.
	Pair Box::getLowerRight()
	{
		return(lowerRight_);
	}
	void Box::setLowerRight(Pair lowerRight)
	{
		if(upperLeft_.x_>lowerRight.x_ || upperLeft_.y_>lowerRight.y_)
		{
			wickThrowError("Invalid lower-right coordinate.");
		}
		lowerRight_ = lowerRight;
	}

	// Combined upper-left and lower-right method.
	void Box::setUpperLeftAndLowerRight(Pair upperLeft,Pair lowerRight)
	{
		if(upperLeft.x_>lowerRight.x_ || upperLeft.y_>lowerRight.y_)
		{
			wickThrowError("Invalid upper-left or lower-right coordinate.");
		}
		upperLeft_ = upperLeft;
		lowerRight_ = lowerRight;
	}
}
