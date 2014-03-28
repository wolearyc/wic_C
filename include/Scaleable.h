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
// File:    Polygon.h
// ----------------------------------------------------------------------------
#ifndef SCALEABLE_H
#define SCALEABLE_H
#include "Pair.h"
namespace wick
{
    /// \brief An architectural superclass that should by inherited by any 
    ///        class that can be scaled.
    ///
    /// Any class that inherits from Scaleable can be scaled. The object is
    /// scaled around a center, which is defined in Paintable. A scale value of
    /// (1,1) is original size, (2,2) is twice the size, (0.5,0.5) is half the
    /// size, etc.
    class Scaleable
    {
    public:
        /// \brief A constructor
        /// \param scale the scale
        Scaleable(Pair scale);
        /// \brief The default constructor
        ///
        /// This constructor constructs an unscaled object.
        Scaleable();
        /// \brief The copy constructor
        /// \param other another Scaleable object
        Scaleable(const Scaleable& other);
        /// \brief Retrieves the scale
        /// \return the scale
        Pair getScale();
        /// \brief Modifies the scale
        /// \param scale the desired scale
        void setScale(Pair scale);
        /// \brief Scales the object
        /// \param scale the value to add to the current scale
        void scale(Pair scale);
    protected:
        Pair scale_;
    };
}
#endif
