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
 * File:    Quad.cpp
 * ----------------------------------------------------------------------------
 */
#include "Quad.h"
namespace wick
{
    Quad::Quad(Pair location, Pair dimensions, Color color)
    :Polygon(location, {Pair(), Pair(dimensions.x_,0.0), dimensions,
    Pair(0.0, dimensions.y_)}, color), dimensions_(dimensions)
    {
    }
    Quad::Quad()
    :Quad(Pair(), Pair(32,32), Color::White)
    {
    }
    Quad::Quad(const Quad& other)
    :Polygon(other), dimensions_(other.dimensions_)
    {
    }
    Pair Quad::getDimensions()
    {
        return(dimensions_);
    }
    void Quad::setDimensions(Pair dimensions)
    {
        dimensions_ = dimensions;
        setBaseVertices({Pair(), Pair(dimensions.x_,0.0), dimensions,
                         Pair(0.0, dimensions.y_)});
    }
}

