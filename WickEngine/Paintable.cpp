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
              :location_(location), center_(Pair()),
               paintCentered_(false), geometricCenter_(Pair())
    {
    }
    Paintable::Paintable()
              :Paintable(Pair())
    {
    }
    Paintable::Paintable(const Paintable& other)
              :location_(other.location_), center_(other.center_),
               paintCentered_(other.paintCentered_),
               geometricCenter_(other.geometricCenter_)
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
    Pair Paintable::getCenter()
    {
        return(center_);
    }
    void Paintable::setCenter(Pair center)
    {
        center_ = center;
    }
    bool Paintable::isPaintedCentered()
    {
        return(paintCentered_);
    }
    void Paintable::paintCentered(bool paintCentered)
    {
        paintCentered_ = paintCentered;
    }
    Pair Paintable::getGeometricCenter()
    {
        return(geometricCenter_);
    }
    Pair Paintable::convertCoordinates(Pair coordinates, Pair dimensions)
    {
        return(coordinates * 2.0 / dimensions - 1);
    }
}

