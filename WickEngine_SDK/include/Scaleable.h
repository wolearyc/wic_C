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
    /// rotated around a center, which is defined in Paintable. A scale value
    /// is a multiplier of the object's side.
    class Scaleable
    {
    public:
        /// \brief A constructor.
        ///
        /// \param scale the scale
        Scaleable(Pair scale);
        /// \brief Default constructor.
        ///
        /// This constructor constructs an unscaled object.
        Scaleable();
        /// \brief Copy constructor.
        Scaleable(const Scaleable& other);
        /// \brief Gets the scale.
        ///
        /// \return the scale
        Pair getScale();
        /// \brief Modifies the scale.
        ///
        /// \param scale the desired scale
        void setScale(Pair scale);
        /// \brief Scales the object.
        ///
        /// \param scale the value to add to the current scale
        void scale(Pair scale);
    protected:
        Pair scale_;
    };
}
#endif
