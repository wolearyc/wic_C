// ----------------------------------------------------------------------------
// wick - a simple, object-oriented 2D game engine for Mac OSX written in C++
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
#include "OpenGL/gl.h"
#include <initializer_list>
using std::initializer_list;
#include <vector>
using std::vector;
namespace wick
{
    /// \brief A convex polygon that can be painted to the screen
    ///
    /// A Polygon can be painted, rotated, centered, scaled, and colored.
    class Polygon : public Paintable, public Rotateable, public Scaleable
    {
    public:
        /// \brief A constructor taking a vector of vertices
        /// \param location the screen location
        /// \param baseVertices the set of vertices (relative to object)
        /// \param color the color
        Polygon(Pair location, vector<Pair> baseVertices, Color color);
        /// \brief A constructor taking an initializer_list of vertices
        /// This constructor allows the vertices to be enclosed in curly
        /// braces ({Pair a, Pair b, etc.})
        /// \param location the screen location
        /// \param baseVertices the set of vertices (relative to object)
        /// \param color the color
        Polygon(Pair location, initializer_list<Pair> baseVertices,
                Color color);
        /// \brief The default constructor
        /// Constructs a Polygon with 0 vertices.
        Polygon();
        /// \brief The copy constructor
        /// \param other another Polygon
        Polygon(const Polygon& other);
        /// \brief Paints the Polygon to the screen
        /// \param game the game
        void paint(Game* game);
        /// \brief Retrieves the vertices
        /// \return the set of vertices
        vector<Pair> getBaseVertices();
        /// \brief Modifies the vertices
        /// \param baseVertices the desired set of vertices
        void setBaseVertices(vector<Pair> baseVertices);
        /// \brief Modifies the vertices
        /// The use of initializer_list allows the set of new vertices to be enclosed
        /// in curly braces ({Pair a, Pair b, etc.})
        /// \param baseVertices the desired set of vertices
        void setBaseVertices(initializer_list<Pair> baseVertices);
        /// \brief Retrieves the color
        /// \return the color
        Color getColor();
        /// \brief Modifies the color
        /// \param color the desired color
        void setColor(Color color);
    protected:
        vector<Pair> baseVertices_;
        vector<Pair> vertices_;
        Color color_;
        void updateVertices();
    };
}
#endif
