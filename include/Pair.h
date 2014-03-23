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
    /// \brief Stores two double precision floating point values.
    ///
    /// Pair is the workhorse of the Wick Engine. Pair objects are used to
    /// represent two dimensional vectors, dimensions, scaling parameters, and,
    /// most commonly, x-y coordinates. The usual mathematical operations and
    /// comparisons can be performed between Pairs, as well as angle and
    /// distance formulas (assuming the two Pairs represent x-y coordinates.
	class Pair
	{
	public:
		double x_; ///< The x coordinate/x dimension/x component etc.
		double y_; ///< The y coordinate/y dimension/y component etc.
		/// \brief A constructor taking two doubles.
		///
		/// \param x desired value of x_.
		/// \param y desired value of y_.
		Pair(double x, double y);
		/// \brief A constructor taking two ints.
		///
		/// Defined to make using integer Pairs easier without constantly
		/// casting ints to doubles.
		/// \param x desired value of x_.
		/// \param y desired value of y_.
		Pair(int x, int y);
		/// \brief The copy constructor.
		///
		/// \param other another Pair.
		Pair(const Pair& other);
		/// \brief The default constructor.
		///
		/// Constructs Pair(0.0,0.0).
		Pair();
		/// \brief Computes the distance to another Pair.
		///
		/// \param other another Pair.
		/// \return the distance in whatever unit of distance the Pairs used.
		double distance(const Pair& other);
		/// \brief Computes the angle to another Pair.
		///
		/// \param other another Pair.
		/// \return the angle, in radians measured from the positive x axis.
		double angle(const Pair& other);
		/// \brief Defines the addition of Pairs.
		///
		/// \param other another Pair.
		/// \return given Pair(a,b) and Pair(c,d), returns Pair(a+c,b+d).
		Pair operator+(const Pair& other) const;
		/// \brief Defines the subtraction of Pairs.
		///
		/// \param other another Pair.
		/// \return given Pair(a,b) and Pair(c,d), returns Pair(a-c,b-d).
		Pair operator-(const Pair& other) const;
		/// \brief Defines the multiplication of Pairs.
		///
		/// \param other another Pair.
		/// \return given Pair(a,b) and Pair(c,d), returns Pair(a*c,b*d).
		Pair operator*(const Pair& other) const;
		/// \brief Defines the division of Pairs.
		///
		/// \param other another Pair.
		/// \return given Pair(a,b) and Pair(c,d), returns Pair(a/c,b/d).
		Pair operator/(const Pair& other) const;
		/// \brief Defines a short cut to add a Pair to another.
		///
		/// \param other another Pair
		/// \return the final added Pair
		Pair operator+=(const Pair& other);
		/// \brief Defines a short cut to subtract a Pair from another.
		///
		/// \param other another Pair
		/// \return the final subtracted Pair
		Pair operator-=(const Pair& other);
		/// \brief Defines a short cut to multiply a Pair to another.
		///
		/// \param other another Pair
		/// \return the final multiplied Pair
		Pair operator*=(const Pair& other);
		/// \brief Defines a short cut to divide a Pair by another.
		///
		/// \param other another Pair
		/// \return the final divided Pair
		Pair operator/=(const Pair& other);
		/// \brief Defines the equality operator.
		///
		/// \param other another Pair
		/// \return true if both Pairs' values are the same (within epsilon),
		///         and false otherwise.
		bool operator==(const Pair& other);
		/// \brief Defines the opposite equality operator.
		///
		/// \param other another Pair
		/// \return false if bothPairs' values are the same (within epsilon),
		///         and true otherwise.
		bool operator!=(const Pair& other) const;
		/// \brief Defines the greater-than or equal operator.
		///
		/// \param other another Pair
		/// \return true if this Pair's values are both greater than or equal
		///         to the other's values, and false otherwise.
		bool operator>=(const Pair& other);
		/// \brief Defines the greater-than operator.
		///
		/// \param other another Pair
		/// \return true if this Pair's values are both greater than the
		///         other's values, and false otherwise.
		bool operator>(const Pair& other);
		/// \brief Defines the less-than or equal operator.
		///
		/// \param other another Pair
		/// \return true if this Pair's values are both less than or equal
		///         to the other's values, and false otherwise.
		bool operator<=(const Pair& other);
		/// \brief Defines the less-than operator.
		///
		/// \param other another Pair
		/// \return true if this Pair's values are both less than the other's
		///         values, and false otherwise.
		bool operator<(const Pair& other);
		/// \brief Defines addition of a double.
		///
		/// \param i a double
		/// \return given Pair(a,b) and i, returns Pair(a+i,b+i).
		Pair operator+(const double i) const;
		/// \brief Defines subtraction of a double.
		///
		/// \param i a double
		/// \return given Pair(a,b) and i, returns Pair(a-i,b-i).
		Pair operator-(const double i) const;
		/// \brief Defines multiplication of a double.
		///
		/// \param i a double
		/// \return given Pair(a,b) and i, returns Pair(a*i,b*i).
		Pair operator*(const double i) const;
		/// \brief Defines division of a double.
		///
		/// \param i a double
		/// \return given Pair(a,b) and i, returns Pair(a/i,b/i).
		Pair operator/(const double i) const;
		/// \brief Defines a short cut to add a double.
		///
		/// \param i a double
		/// \return the final added Pair
		Pair operator+=(const double i);
		/// \brief Defines a short cut to subtract a double.
		///
		/// \param i a double
		/// \return the final subtracted Pair
		Pair operator-=(const double i);
		/// \brief Defines a short cut to multiply a double.
		///
		/// \param i a double
		/// \return the final multiplied Pair
		Pair operator*=(const double i);
		/// \brief Defines a short cut to divide a double.
		///
		/// \param i a double
		/// \return the final divided Pair
		Pair operator/=(const double i);
	};
}
#endif
