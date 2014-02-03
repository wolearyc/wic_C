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
// File:    Quad.cpp
// ----------------------------------------------------------------------------

#include "Quad.h"
namespace wick
{
    Quad::Quad(Pair location, Color color, Pair dimensions)
         :Polygon(location, color, {Pair(), Pair(dimensions.x_,0.0),
                                    dimensions, Pair(0.0, dimensions.y_)})
    {
        setDimensions(dimensions);
    }
    Quad::Quad(const Quad& other)
         :Polygon(other)
    {
        dimensions_ = other.dimensions_;
    }
    Quad::Quad()
         :Polygon()
    {
        dimensions_ = Pair();
    }

    Pair Quad::getDimensions()
    {
        return(dimensions_);
    }
    void Quad::setDimensions(Pair dimensions)
    {
        dimensions_ = dimensions;
        if(dimensions_.x_ == 0)
            throwWarning(W_QUAD, "X dimension is 0");
        if(dimensions_.y_ == 0)
            throwWarning(W_QUAD, "Y dimension is 0");
        setBaseVertices({Pair(), Pair(dimensions.x_,0.0), dimensions,
                         Pair(0.0, dimensions.y_)});
    }
}
