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
// File:    Scaleable.cpp
// ----------------------------------------------------------------------------

#include "Scaleable.h"
namespace wick
{
    Scaleable::Scaleable(Pair scale)
    {
        scale_       = scale;
        scaleCenter_ = Pair();
    }
    Scaleable::Scaleable(const Scaleable& other)
    {
        scale_       = other.scale_;
        scaleCenter_ = other.scaleCenter_;
    }
    Scaleable::Scaleable()
              :Scaleable(Pair(1,1))
    {
    }

    Pair Scaleable::getScale()
    {
        return(scale_);
    }
    void Scaleable::setScale(Pair scale)
    {
        scale_ = scale;
    }
    void Scaleable::scale(Pair scale)
    {
        setScale(scale_ + scale);
    }

    Pair Scaleable::getScaleCenter()
    {
        return(scaleCenter_);
    }
    void Scaleable::setScaleCenter(Pair scaleCenter)
    {
        scaleCenter_ = scaleCenter;
    }
}
