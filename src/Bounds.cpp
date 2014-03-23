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
// File:    Bounds.cpp
// ----------------------------------------------------------------------------
#include "Bounds.h"
namespace wick
{
    Bounds::Bounds(Pair lowerLeft, Pair upperRight)
           :lowerLeft_(lowerLeft), upperRight_(upperRight)
    {
    }
    Bounds::Bounds(int lowerLeftX, int lowerLeftY, int upperRightX, int upperRightY)
           :Bounds(Pair(lowerLeftX, lowerLeftY), Pair(upperRightX, upperRightY))
    {
    }
    Bounds::Bounds(Pair location, int xDimension, int yDimension)
           :Bounds(location, location + Pair(xDimension,yDimension))
    {
    }
    Bounds::Bounds(const Bounds& other)
           :Bounds(other.lowerLeft_, other.upperRight_)
    {
    }
    Bounds::Bounds()
           :Bounds(Pair(), Pair(32,32))
    {
    }
    Pair Bounds::getLowerLeft()
    {
        return(lowerLeft_);
    }
    void Bounds::setLowerLeft(Pair lowerLeft)
    {
        lowerLeft_ = lowerLeft;
    }
    void Bounds::translateLowerLeft(Pair translation)
    {
        lowerLeft_ += translation;
    }
    Pair Bounds::getUpperRight()
    {
        return(upperRight_);
    }
    void Bounds::setUpperRight(Pair upperRight)
    {
        upperRight_ = upperRight;
    }
    void Bounds::translateUpperRight(Pair translation)
    {
        upperRight_ += translation;
    }
    void Bounds::setLowerLeftAndUpperRight(Pair lowerLeft, Pair upperRight)
    {
        lowerLeft_ = lowerLeft;
        upperRight_ = upperRight;
    }
}
