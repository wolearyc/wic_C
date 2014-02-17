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
// File:    Quad.h
// ----------------------------------------------------------------------------
#ifndef QUAD_H
#define QUAD_H
#include "Polygon.h"
namespace wick
{
    /// \brief A rectangle that can be painted to the screen.
    /// 
    /// A Quad can be painted, rotated, and scaled. A quad acts just like a 
    /// polygon.
    class Quad : public Polygon
    {
    public:
        /// \brief A constructor.
        ///
        /// \param location the screen location
        /// \param dimensions the dimensions
        /// \param color the color
        Quad(Pair location, Pair dimensions, Color color);
        /// \brief Default constructor.
        ///
        /// Constructs a 32x32 white Quad located at (0,0).
        Quad();
        /// \brief Copy constructor.
        Quad(const Quad& other);
        /// \brief Gets the dimensions.
        ///
        /// \return the dimensions
        Pair getDimensions();
        /// \brief Modifies the dimensions.
        ///
        /// \param dimensions the desired dimensions
        void setDimensions(Pair dimensions);
    protected:
        Pair dimensions_;
    };
}
#endif
