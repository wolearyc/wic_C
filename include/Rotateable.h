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
 * File:    Rotateable.h
 * ----------------------------------------------------------------------------
 */
#ifndef ROTATEABLE_H
#define ROTATEABLE_H
#include "Pair.h"
namespace wick
{
    /** \brief an architectural superclass that should be inherited by any
      *        class that is "rotateable"
      *
      * Any subclass of Rotateable has a roation. The subclass is rotated 
      * around a center, defined in Paintable.
      */
    class Rotateable
    {
    public:
        /** \brief constructs Rotateable based on rotation
          * \param rotation the rotation in radians relative to the x-axis
          */
        Rotateable(double rotation);
        /** \brief constructs Rotatatable with a rotation of 0
          */
        Rotateable();
        /** \brief constructs a Rotateable identical to another
          * \param another Rotabeable
          */
        Rotateable(const Rotateable& other);
        /** \brief retrieves the rotation
          * \return the rotation in radians relative to the x-axis
          */
        double getRotation();
        /** \brief modifies the rotation
          * \param rotation the desired rotation in radians relative to the
          *        x-axis
          */
        void setRotation(double rotation);
        /** \brief rotates the object by a certain amount
          * \param rotation the amount to rotate by in radians
          */
        void rotate(double rotation);
    protected:
        double rotation_; /**< the rotation in radians relative to the x-axis */
    };
}
#endif
