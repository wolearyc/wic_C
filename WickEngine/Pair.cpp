// ------------------------------------------------------------------------------------------------
// File:			Pair.cpp
//-------------------------------------------------------------------------------------------------

#include "Pair.h"
namespace wick
{
	// Constructors.
	Pair::Pair(double x, double y)
	{
		x_ = x;
		y_ = y;
	}
	Pair::Pair(int x, int y)
	{
	    x_ = (double) x;
	    y_ = (double) y;
	}
	Pair::Pair(const Pair& other)
	{
		x_ = other.x_;
		y_ = other.y_;
	}
	Pair::Pair()
	{
		x_ = 0.0;
		y_ = 0.0;
	}

	// Methods determining distance and angle.
	double Pair::distance(const Pair& other)
	{
		return(sqrt(pow(other.x_-x_,2.0) + pow(other.y_-y_,2.0)));
	}
	double Pair::angle(const Pair& other)
	{
		return(atan(other.y_-y_)/ (other.x_-x_));
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
	bool Pair::operator==(const Pair& other)
	{
		return(fabs(x_ - other.x_) < 0.0000001 &&
              (fabs(y_ - other.y_) < 0.0000001));
	}
	bool Pair::operator!=(const Pair& other) const
	{
		return(fabs(x_ - other.x_) >= 0.0000001 &&
              (fabs(y_ - other.y_) >= 0.0000001));
	}
	Pair Pair::operator+(const double i) const
	{
		return(Pair(x_ + i, y_ + i));
	}
	Pair Pair::operator-(const double i) const
	{
		return(Pair(x_ - i, y_ - i));
	}
	Pair Pair::operator*(const double i) const
	{
		return(Pair(x_ * i, y_ * i));
	}
	Pair Pair::operator/(const double i) const
	{
		return(Pair(x_ / i, y_ / i));
	}
}
