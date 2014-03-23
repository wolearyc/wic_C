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
// File:    Pair.cpp
// ----------------------------------------------------------------------------
#include "Pair.h"
namespace wick
{
	Pair::Pair(double x, double y)
	{
		x_ = x;
		y_ = y;
	}
	Pair::Pair(int x, int y)
	     :Pair((double) x, (double) y)
	{
	}
	Pair::Pair(const Pair& other)
         :Pair(other.x_, other.y_)
	{
	}
	Pair::Pair()
	     :Pair(0.0,0.0)
	{
	}
	double Pair::distance(const Pair& other)
	{
		return(sqrt(pow(other.x_ - x_, 2.0) + pow(other.y_ - y_, 2.0)));
	}
	double Pair::angle(const Pair& other)
	{
		return(atan2(other.y_ - y_, other.x_ - x_));
	}
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
	Pair Pair::operator+=(const Pair& other)
	{
	    x_ += other.x_;
	    y_ += other.y_;
	    return(Pair(x_, y_));
	}
    Pair Pair::operator-=(const Pair& other)
    {
        x_ -= other.x_;
	    y_ -= other.y_;
	    return(Pair(x_, y_));
    }
	Pair Pair::operator*=(const Pair& other)
	{
	    x_ *= other.x_;
	    y_ *= other.y_;
	    return(Pair(x_, y_));
	}
	Pair Pair::operator/=(const Pair& other)
	{
	    x_ /= other.x_;
	    y_ /= other.y_;
	    return(Pair(x_, y_));
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
	bool Pair::operator>=(const Pair& other)
	{
	    return(x_ - other.x_ >= 0.0000001 &&
              (y_ - other.y_ >= 0.0000001));
	}
    bool Pair::operator>(const Pair& other)
    {
        return(x_ - other.x_ > 0.0000001 &&
              (y_ - other.y_ > 0.0000001));
    }
    bool Pair::operator<=(const Pair& other)
    {
        return(x_ - other.x_ <= 0.0000001 &&
              (y_ - other.y_ <= 0.0000001));
    }
	bool Pair::operator<(const Pair& other)
	{
	    return(x_ - other.x_ < 0.0000001 &&
              (y_ - other.y_ < 0.0000001));
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
	Pair Pair::operator+=(const double i)
	{
	    x_ += i;
	    y_ += i;
	    return(Pair(x_, y_));
	}
    Pair Pair::operator-=(const double i)
    {
        x_ -= i;
	    y_ -= i;
	    return(Pair(x_, y_));
    }
    Pair Pair::operator*=(const double i)
    {
        x_ *= i;
	    y_ *= i;
	    return(Pair(x_, y_));
    }
    Pair Pair::operator/=(const double i)
    {
        x_ /= i;
	    y_ /= i;
	    return(Pair(x_, y_));
    }
}
