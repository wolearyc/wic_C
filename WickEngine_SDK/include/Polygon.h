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
// File:    Polygon.h
// ----------------------------------------------------------------------------
#ifndef POLYGON_H
#define POLYGON_H
#include "Color.h"
#include "Paintable.h"
#include "Rotateable.h"
#include "Scaleable.h"
#include "GL/gl.h"
#include <initializer_list>
using std::initializer_list;
#include <vector>
using std::vector;
namespace wick
{
    class Polygon : public Paintable, public Rotateable, public Scaleable
    {
    public:


        Polygon(Pair location, vector<Pair> baseVertices, Color color);
        Polygon(Pair location, initializer_list<Pair> baseVertices,
                Color color);
        Polygon();
        Polygon(const Polygon& other);
        void paint(Window* window);
        vector<Pair> getBaseVertices();
        void setBaseVertices(vector<Pair> baseVertices);
        void setBaseVertices(initializer_list<Pair> baseVertices);
        Color getColor();
        void setColor(Color color);
    protected:
        vector<Pair> baseVertices_;
        vector<Pair> vertices_;
        Color color_;
        void updateVertices();
    };
}
#endif
