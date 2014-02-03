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
// File:    Polygon.cpp
// ----------------------------------------------------------------------------

#include "Polygon.h"
namespace wick
{
    Polygon::Polygon(Pair location, Color color,
                     initializer_list<Pair> baseVertices)
            :Paintable(location), Rotateable(), Scaleable()
    {
        setColor(color);
        setBaseVertices(baseVertices);
    }
    Polygon::Polygon(const Polygon& other)
            :Paintable(other), Rotateable(other), Scaleable(other)
    {
        color_        = other.color_;
        baseVertices_ = other.baseVertices_;
        vertices_     = other.vertices_;
    }
    Polygon::Polygon()
            :Paintable(), Rotateable(), Scaleable()
    {
        color_ = Color();
    }

    void Polygon::paint(Window* window)
    {
        updateVertices();
        Pair dimensions = window->getDimensions();
        color_.select();
        glBegin(GL_POLYGON);
            for(unsigned int i = 0; i < baseVertices_.size(); i++)
            {
                Pair vertex = vertices_[i];
                vertex = convertCoordinates(vertex + location_, dimensions);
                glVertex2d(vertex.x_, vertex.y_);
            }
        glEnd();
    }

    Color Polygon::getColor()
    {
        return(color_);
    }
    void Polygon::setColor(Color color)
    {
        color_ = color;
    }

    vector<Pair> Polygon::getBaseVertices()
    {
        return(baseVertices_);
    }
    void Polygon::setBaseVertices(initializer_list<Pair> baseVertices)
    {
        baseVertices_.clear();
        baseVertices_ = baseVertices;
        if(baseVertices_.size() == 0)
            throwWarning(W_POLYGON, "No vertices supplied");
        vertices_.clear();
        vertices_ = vector<Pair>(baseVertices_.size(), Pair());
    }

    void Polygon::updateVertices()
    {
        for(unsigned int i = 0; i < baseVertices_.size(); i++)
        {
            Pair vertex = baseVertices_[i];

            vertex -= scaleCenter_;
            vertex = vertex * scale_;
            vertex += scaleCenter_;

            double cosine = cos(rotation_);
            double sine = sin(rotation_);
            vertex -= rotateCenter_;
            vertex = Pair(vertex.x_ * cosine - vertex.y_ * sine,
                          vertex.x_ * sine + vertex.y_ * cosine);
            vertex += rotateCenter_;

            vertices_[i] = vertex - paintCenter_;
        }
    }
}
