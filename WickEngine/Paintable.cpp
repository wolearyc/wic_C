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
// File:    Paintable.cpp
// ----------------------------------------------------------------------------

#include "Paintable.h"
namespace wick
{
    Paintable::Paintable(Pair location)
    {
        location_     = location;
        paintCenter_  = Pair();
    }
    Paintable::Paintable(const Paintable& other)
    {
        location_    = other.location_;
        paintCenter_ = other.paintCenter_;
    }
    Paintable::Paintable()
              :Paintable(Pair())
    {
    }

    Pair Paintable::getLocation()
    {
        return(location_);
    }
    void Paintable::setLocation(Pair location)
    {
        location_ = location;
    }
    void Paintable::translate(Pair translation)
    {
        setLocation(location_ + translation);
    }

    Pair Paintable::getPaintCenter()
    {
        return(paintCenter_);
    }
    void Paintable::setPaintCenter(Pair paintCenter)
    {
        paintCenter_ = paintCenter;
    }

    Pair Paintable::convertCoordinates(Pair coordinates, Pair dimensions)
    {
        return(coordinates / dimensions * 2.0 - 1);
    }
}
