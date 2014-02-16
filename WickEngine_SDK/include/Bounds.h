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
// File:    Bounds.h
// ----------------------------------------------------------------------------
#ifndef BOUNDS_H
#define BOUNDS_H
#include "Pair.h"
namespace wick
{
    /// \brief Defines a rectangular area.
    ///
    /// Bounds is most commonly used when defining images that only use a
    /// a specific rectangular portion of a texture. 
    class Bounds
    {
    public:
        /// \brief A constructor taking two Pairs.
        ///
        /// Each Pair represents an x-y coordinate. The Pairs do not 
        /// necessarly need to define the lower-left or upper-right x-y 
        /// coordinate of the bounding rectangle, but if they do not, the
        /// resulting bounds will be inverted.
        /// \param lowerLeft the lower-left x-y coordinate of the bounding 
        ///        rectangle
        /// \param upperRight the upper-right x-y coordinate of the bounding
        ///        rectangle
        Bounds(Pair lowerLeft, Pair upperRight);
        /// \brief A constructor taking four ints.
        ///
        /// \param lowerLeftX x value of the lower-left x-y coordinate
        /// \param lowerLeftY y value of the lower-left x-y coordinate
        /// \param upperRightX x value of the upper-right x-y coordinate
        /// \param upperRightY y value of the upper-right x-y coordinate
        Bounds(int lowerLeftX, int lowerLeftY, int upperRightX, int upperRightY);
        /// \brief A constructor taking a location and dimensions.
        ///
        /// \param location the location of the lower-left x-y coordinate
        /// \xDimension width of the bounding rectangle
        /// \yDimension height of the bounding rectangle
        Bounds(Pair location, int xDimension, int yDimension);
        /// \brief Default constructor.
        Bounds();
        /// \brief Copy constructor.
        Bounds(const Bounds& other);
        /// \brief Gets the lower-left x-y coordinate.
        ///
        /// \return lower-left x-y coordinate
        Pair getLowerLeft();
        /// \brief Sets the lower-left x-y coordinate.
        ///
        /// \param lowerLeft desired lower-left x-y coordinate
        void setLowerLeft(Pair lowerLeft);
        /// \brief Translates the lower-left x-y coordinate.
        ///
        /// \param translation desired translation of the lower-left 
        ///        x-y coordinate
        void translateLowerLeft(Pair translation);
        /// \brief Gets the upper-right x-y coordinate.
        ///
        /// \return upper-right x-y coordinate
        Pair getUpperRight();
        /// \brief Sets the upper-right x-y coordinate.
        ///
        /// \param upperRight desired upper-right x-y coordinate
        void setUpperRight(Pair upperRight);
        /// \brief Translates the upper-right x-y coordinate.
        ///
        /// \param translation desired translation of the upper-right 
        ///        x-y coordinate
        void translateUpperRight(Pair translation);
        /// \brief Sets the lower-left and upper-right x-y coordinates
        ///        simultaneously.
        ///
        /// \param lowerLeft desired lower-left x-y coordinate
        /// \param upperRight desired upper-right x-y coordinate
        void setLowerLeftAndUpperRight(Pair lowerLeft, Pair upperRight);
    protected:
        Pair lowerLeft_;
        Pair upperRight_;
    };
}
#endif
