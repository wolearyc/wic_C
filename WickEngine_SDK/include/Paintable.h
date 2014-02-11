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
// File:    Paintable.h
// ----------------------------------------------------------------------------
#ifndef PAINTABLE_H
#define PAINTABLE_H
#include "Pair.h"
#include "Game.h"
#include "GL/gl.h"
namespace wick
{
    class Paintable
    {
    public:
        Paintable(Pair location);
        Paintable();
        Paintable(const Paintable& other);
        Pair getLocation();
        void setLocation(Pair location);
        void translate(Pair translation);
        Pair getCenter();
        void setCenter(Pair center);
        bool isPaintedCentered();
        void paintCentered(bool paintCentered);
        Pair getGeometricCenter();
        virtual void paint(Game* game) = 0;
    protected:
        Pair location_;
        Pair center_;
        bool paintCentered_;
        Pair geometricCenter_;
        Pair convertCoordinates(Pair coordinates, Pair dimensions);
    };
}
#endif
