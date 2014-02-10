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
// File:    Pair.h
// ----------------------------------------------------------------------------
#ifndef PAIR_H
#define PAIR_H
#include <math.h>
namespace wick
{
	class Pair
	{
	public:
		double x_;
		double y_;
		Pair(double x, double y);
		Pair(int x, int y);
		Pair(const Pair& other);
		Pair();
		double distance(const Pair& other);
		double angle(const Pair& other);
		Pair operator+(const Pair& other) const;
		Pair operator-(const Pair& other) const;
		Pair operator*(const Pair& other) const;
		Pair operator/(const Pair& other) const;
		Pair operator+=(const Pair& other);
		Pair operator-=(const Pair& other);
		Pair operator*=(const Pair& other);
		Pair operator/=(const Pair& other);
		bool operator==(const Pair& other);
		bool operator!=(const Pair& other) const;
		bool operator>=(const Pair& other);
		bool operator>(const Pair& other);
		bool operator<=(const Pair& other);
		bool operator<(const Pair& other);
		Pair operator+(const double i) const;
		Pair operator-(const double i) const;
		Pair operator*(const double i) const;
		Pair operator/(const double i) const;
		Pair operator+=(const double i);
		Pair operator-=(const double i);
		Pair operator*=(const double i);
		Pair operator/=(const double i);
	};
}
#endif
