// ----------------------------------------------------------------------------
// wick - a simple, object-oriented 2D game engine for Mac OSX written in C++
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
// File:    Bounds.h
// ----------------------------------------------------------------------------
#ifndef BOUNDS_H
#define BOUNDS_H
#include "Pair.h"
namespace wick
{
    /// \brief Defines a rectangular area
    ///
    /// Bounds is most commonly used when defining images that only use a
	/// specific rectangular portion of a texture. 
    class Bounds
    {
    public:
        /// \brief A constructor taking two Pairs
        ///
        /// The Pairs do not necessarly need to define the lower-left or 
		/// upper-right x-y coordinates of the bounding rectangle, but if they 
		/// do not, the resulting bounds will be mirrored along some axis.
        /// \param lowerLeft lower-left x-y coordinate
        /// \param upperRight upper-right x-y coordinate
        Bounds(Pair lowerLeft, Pair upperRight);
        /// \brief A constructor taking four ints
        /// \param lowerLeftX the x value of the lower-left x-y coordinate
        /// \param lowerLeftY the y value of the lower-left x-y coordinate
        /// \param upperRightX the x value of the upper-right x-y coordinate
        /// \param upperRightY the y value of the upper-right x-y coordinate
        Bounds(int lowerLeftX, int lowerLeftY, int upperRightX, int upperRightY);
        /// \brief A constructor taking a x-y location and dimensions
        /// \param location the location of the lower-left x-y coordinate
        /// \xDimension the width from the lower-left x-y coordinate
        /// \yDimension the height from the lower-left x0y coordinate
        Bounds(Pair location, int xDimension, int yDimension);
        /// \brief The default constructor
        Bounds();
        /// \brief The copy constructor
        Bounds(const Bounds& other);
        /// \brief Retrieves the lower-left x-y coordinate
        /// \return lower-left the lower-left x-y coordinate
        Pair getLowerLeft();
        /// \brief Modifies the lower-left x-y coordinate
        /// \param lowerLeft the desired lower-left x-y coordinate
        void setLowerLeft(Pair lowerLeft);
        /// \brief Translates the lower-left x-y coordinate
        /// \param translation the desired translation vector for the 
		///        lower-left x-y coordinate
        void translateLowerLeft(Pair translation);
        /// \brief Retrieves the upper-right x-y coordinate
        /// \return upper-right the upper-right x-y coordinate
        Pair getUpperRight();
        /// \brief Modifies the upper-right x-y coordinate
        /// \param upperRight the desired upper-right x-y coordinate
        void setUpperRight(Pair upperRight);
        /// \brief Translates the upper-right x-y coordinate
        /// \param translation the desired translation vector for the 
		/// upper-right x-y coordinate
        void translateUpperRight(Pair translation);
        /// \brief Modifies the lower-left and upper-right x-y coordinates
        ///        simultaneously.
        /// \param lowerLeft the desired lower-left x-y coordinate
        /// \param upperRight the desired upper-right x-y coordinate
        void setLowerLeftAndUpperRight(Pair lowerLeft, Pair upperRight);
    protected:
        Pair lowerLeft_;
        Pair upperRight_;
    };
}
#endif
