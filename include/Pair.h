/* ----------------------------------------------------------------------------
 * wick - a simple, object-oriented 2D game engine for Mac OSX written in C++
 * Copyright (C) 2013-2014  Will O'Leary
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------------------------
 * File:    Pair.h
 * ----------------------------------------------------------------------------
 */
#ifndef PAIR_H
#define PAIR_H
#include <math.h>
namespace wick
{
    /** \brief a pair of double precision floating point values
      *
      * Pairs can hold two dimensional vectors, dimensions, scaling parameters, 
      * and, most commonly, coordinates. Pairs support all the usual vector 
      * operations (vector and scalar addition, subtraction, multiplication)
      * as well as the usual comparisons. Pair also contains useful methods 
      * for determining angle and distance between two Pairs.
      */
	class Pair
	{
	public:
		double x_; /**< the x coordinate/x dimension/x component etc. */
		double y_; /**< the y coordinate/y dimension/y component etc. */
		/** \brief constructs Pair based on two doubles
		  * \param x the desired x coordinate/x dimension/x component etc.
		  * \param y the desired y coordinate/y dimension/y component etc.
          */
		Pair(double x, double y);
		/** \brief constructs Pair based on two ints
		  * \param x the desired x coordinate/x dimension/x component etc.
		  * \param y the desired y coordinate/y dimension/y component etc.
          */
		Pair(int x, int y);
        /** \brief constructs Pair with x coordinate/x dimension/x component 0
          *        and y coordinate/y dimension/y component 0 
          */
		Pair();
		/** \brief constructs a Pair identical to another
		  * \param other another Pair
          */
		Pair(const Pair& other);
		/** \brief computes the distance to another Pair
		  * \param other another Pair
		  * \return the distance between the Pairs, in whatever units the Pairs
          *         used
          */
		double distance(const Pair& other);
		/** \brief computes the angle to another Pair
		  * \param other another Pair
		  * \return the angle, in radians measured from the positive x axis
          */
		double angle(const Pair& other);
		/** \brief defines addition between Pairs
		  * \param other another Pair
		  * \return the component-wise sum of the Pairs
          */
		Pair operator+(const Pair& other) const;
		/** \brief defines subraction between Pairs
		  * \param other another Pair
		  * \return the component-wise difference between the Pairs
          */
		Pair operator-(const Pair& other) const;
		/** \brief defines multiplication between Pairs
		  * \param other another Pair
		  * \return the component-wise product of the Pairs
          */
		Pair operator*(const Pair& other) const;
		/** \brief defines division between Pairs
		  * \param other another Pair
		  * \return the component-wise quotient of the Pairs
          */
		Pair operator/(const Pair& other) const;
		/** \brief defines addition assignment between Pairs
		  * \param other another Pair
		  * \return the final added Pair
          */
		Pair operator+=(const Pair& other);
		/** \brief defines subraction assignment between Pairs
		  * \param other another Pair
		  * \return the final subtracted Pair
          */
		Pair operator-=(const Pair& other);
		/** \brief defines multiplication assignment between Pairs 
          * \param other another Pair
		  * \return the final multiplied Pair
          */
		Pair operator*=(const Pair& other);
		/** \brief defines division assiment between Pairs
		  * \param other another Pair
		  * \return the final divided Pair
          */
		Pair operator/=(const Pair& other);
		/** \brief defines equality operator between Pairs
		  * \param other another Pair
		  * \return true if both Pairs' respective components are within epsilon
          *         (0.0000001), false otherwise
          */
		bool operator==(const Pair& other);
		/** \brief defines the inequality operator between Pairs
		  * \param other another Pair
          * \return false if both Pairs' respective components are within 
          *         epsilon (0.0000001), true otherwise
          */
		bool operator!=(const Pair& other) const;
        /** \brief defines the greater than or equal to operator between Pairs
		  * \param other another Pair
		  * \return true if the Pair's respective components are both greater
          *         than or equal to the components of the other Pair
          */
		bool operator>=(const Pair& other);
		/** \brief defines the greater than operator between Pairs
		  * \param other another Pair
          * \return true if the Pair's respective components are both greater
          *         than to the components of the other Pair
          */
		bool operator>(const Pair& other);
        /** \brief defines the less than or equal to operator between Pairs
		  * \param other another Pair
         * \return true if the Pair's respective components are both less than
         *         or equal to the components of the other Pair
         */
		bool operator<=(const Pair& other);
		/** \brief defines the less than operator between Pairs
		  * \param other another Pair
		 * \return true if the Pair's respective components are both greater
         *         than or equal to the components of the other Pair
         */
		bool operator<(const Pair& other);
		/** \brief defines addition between a Pair and a double
		  * \param i a double
		  * \return the Pair with the double added to both components
          */
		Pair operator+(const double i) const;
        /** \brief defines subtraction between a Pair and a double
          * \param i a double
          * \return the Pair with the double subtracted from both components
          */
		Pair operator-(const double i) const;
		/** \brief defines multiplication between a Pair and a double
          * \param i a double
          * \return the Pair with the double multiplied by both components
          */
		Pair operator*(const double i) const;
		/** \brief defines division between a Pair and a double
          * \param i a double
          * \return the Pair with the double divided into  both components
          */
		Pair operator/(const double i) const;
		/** \brief defines addition assignment between a Pair and a double
          * \param i a double
		  * \return the final added Pair
          */
		Pair operator+=(const double i);
		/** \brief defines subtraction assignment between a Pair and a double
		  * \param i a double
		  * \return the final subtracted Pair
          */
		Pair operator-=(const double i);
        /** \brief defines multiplication assignment between a Pair and a double
		  * \param i a double
		  * \return the final multiplied Pair
          */
		Pair operator*=(const double i);
		/** \brief defines division assignment between a Pair and a double
          * \param i a double
		  * \return the final divided Pair
          */
		Pair operator/=(const double i);
	};
}
#endif
