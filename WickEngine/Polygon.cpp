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
    Polygon::Polygon(Pair location, vector<Pair> baseVertices, Color color)
            :Paintable(location), Rotateable(), Scaleable(),
             baseVertices_(baseVertices), color_(color)
    {
        unsigned int length = baseVertices.size();
        for(unsigned int i = 0; i < length; i++)
            geometricCenter_ += baseVertices_[i];
        geometricCenter_ /= (double) length;
        vertices_ = vector<Pair>(length, Pair());
    }
    Polygon::Polygon(Pair location, initializer_list<Pair> baseVertices,
                     Color color)
            :Polygon(location, (vector<Pair>) baseVertices, color)
    {
    }
    Polygon::Polygon()
            :Paintable(), Rotateable(), Scaleable(), color_(Color())
    {
    }
    Polygon::Polygon(const Polygon& other)
            :Paintable(other), Rotateable(other), Scaleable(other),
             color_(other.color_), baseVertices_(other.baseVertices_),
             vertices_(other.vertices_)
    {
    }
    void Polygon::paint(Window* window)
    {
        updateVertices();
        Pair dimensions = window->getDimensions();
        unsigned int length = vertices_.size();
        color_.select();
        glBegin(GL_POLYGON);
            for(unsigned int i = 0; i < length; i++)
            {
                Pair vertex = vertices_[i];
                vertex = convertCoordinates(vertex + location_, dimensions);
                glVertex2d(vertex.x_, vertex.y_);
            }
        glEnd();
    }
    void Polygon::updateVertices()
    {
        double cosine = cos(rotation_);
        double sine = sin(rotation_);
        unsigned int length = baseVertices_.size();
        for(unsigned int i = 0; i < length; i++)
        {
            Pair vertex = baseVertices_[i];
            vertex -= (center_);
            vertex *= scale_;
            vertex = Pair(vertex.x_ * cosine - vertex.y_ * sine,
                          vertex.x_ * sine + vertex.y_ * cosine);
            if(!paintCentered_)
                vertex += center_;
            vertices_[i] = vertex;
        }
    }
    vector<Pair> Polygon::getBaseVertices()
    {
        return(baseVertices_);
    }
    void Polygon::setBaseVertices(vector<Pair> baseVertices)
    {
        baseVertices_.clear();
        baseVertices_ = baseVertices;
        unsigned int length = baseVertices_.size();
        geometricCenter_ = Pair();
        for(unsigned int i = 0; i < length; i++)
            geometricCenter_ += baseVertices_[i];
        geometricCenter_ /= (double) length;
        vertices_.clear();
        vertices_ = vector<Pair>(length, Pair());
    }
    void Polygon::setBaseVertices(initializer_list<Pair> baseVertices)
    {
        setBaseVertices((vector<Pair>) baseVertices);
    }
    Color Polygon::getColor()
    {
        return(color_);
    }
    void Polygon::setColor(Color color)
    {
        color_ = color;
    }
}

