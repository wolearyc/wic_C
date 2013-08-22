// ------------------------------------------------------------------------------------------------
// File:			Pair.cpp
//-------------------------------------------------------------------------------------------------

#include "Pair.h"
namespace wick
{
	// Constructors.
	Pair::Pair(int x, int y)
	{ 
		x_ = x;
		y_ = y;
	}
	Pair::Pair(const Pair& other)
	{
		x_ = other.x_;
		y_ = other.y_;
	}
	Pair::Pair()
	{
		x_ = 0;
		y_ = 0;
	}

	// Methods determining distance and angle.
	double Pair::distance(const Pair& other)
	{
		return(sqrt(pow((double) (other.x_-x_),2.0) + pow((double) (other.y_-y_),2.0)));
	}
	double Pair::angle(const Pair& other)
	{
		return(atan((double) (other.y_-y_)/ ((double) (other.x_-x_))));
	}
	double Pair::angleInDegrees(const Pair& other)
	{
		return((angle(other) * 57.2958));
	}

	// Operator overloads.
	Pair Pair::operator+(const Pair& other) const
	{
		return(Pair(x_ + other.x_, y_ + other.y_));
	}
	Pair Pair::operator-(const Pair& other) const
	{
		return(Pair(x_ - other.x_, y_ - other.y_));
	}
	Pair Pair::operator*(const Pair& other) const
	{
		return(Pair(x_ * other.x_, y_ * other.y_));
	}
	Pair Pair::operator/(const Pair& other) const
	{
		return(Pair(x_ / other.x_, y_ / other.y_));
	}
	Pair Pair::operator%(const Pair& other) const
	{
		return(Pair(x_ % other.x_, y_ % other.y_));
	}
	bool Pair::operator==(const Pair& other) 
	{
		return(x_ == other.x_ && y_ == other.y_);
	}
	bool Pair::operator!=(const Pair& other) const
	{
		return(x_!=other.x_ || y_!=other.y_);
	}
	Pair Pair::operator+(const int i) const
	{
		return(Pair(x_ + i, y_ + i));
	}
	Pair Pair::operator-(const int i) const
	{
		return(Pair(x_ - i, y_ - i));
	}
	Pair Pair::operator*(const int i) const
	{
		return(Pair(x_ * i, y_ * i));
	}
	Pair Pair::operator/(const int i) const
	{
		return(Pair(x_ / i, y_ / i));
	}
	Pair Pair::operator%(const int i) const
	{
		return(Pair(x_ % i, y_ % i));
	}
}
