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
// File:    Rotateable.h
// ----------------------------------------------------------------------------
#ifndef ROTATEABLE_H
#define ROTATEABLE_H
#include "Pair.h"
namespace wick
{
    /// \brief An architectural superclass that should be inherited by any
    ///        class that is "rotateable"
    /// 
    /// Any class that inherits from Rotateable has a rotation. The object is
    /// rotated around a center, defined in Paintable.
    class Rotateable
    {
    public:
        /// \brief A constructor
        /// \param rotation the rotation in radians relative to the x-axis
        Rotateable(double rotation);
        /// \brief The default constructor
        ///
        /// Constructs an object with 0 radians of rotation relative to the
        /// x-axis.
        Rotateable();
        /// \brief The copy constructor
        /// \param another Rotabeable object
        Rotateable(const Rotateable& other);
        /// \brief Retrieves the rotation
        /// \return the rotation in radians relative to the x-axis
        double getRotation();
        /// \brief Modifies the rotation
        /// \param rotation the desired rotation in radians relative to the
        //         x-axis
        void setRotation(double rotation);
        /// \brief Rotates the object
        /// 
        /// \param rotation the amount to rotate by in radians
        void rotate(double rotation);
    protected:
        double rotation_;
    };
}
#endif
