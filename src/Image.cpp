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
// File:    Image.cpp
// ----------------------------------------------------------------------------
#include "Image.h"
namespace wick
{
    Image::Image(Pair location, Texture* texture)
    :Quad(location, texture->getDimensions(), Color::White), texture_(texture),
    bounds_(Bounds(Pair(), texture->getDimensions()))
    {
    }
    Image::Image()
          :Quad(), texture_(0), bounds_(Bounds())
    {
    }
    Image::Image(const Image& other)
    :Quad(other), texture_(other.texture_), bounds_(other.bounds_)
    {
    }
    void Image::paint(Game* game)
    {
        updateVertices();
        Pair wDimensions = game->getDimensions();
        Pair tDimensions = texture_->getDimensions();
        texture_->select();
        color_.select();
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
            Pair vertex = vertices_[0];
            glTexCoord2f ((bounds_.getLowerLeft().x_ + 1) / tDimensions.x_,
                          (-bounds_.getLowerLeft().y_ - 1) / tDimensions.y_);
            vertex = convertCoordinates(vertex + location_, wDimensions);
            glVertex2d(vertex.x_, vertex.y_);
            vertex = vertices_[1];
            glTexCoord2f ((bounds_.getUpperRight().x_ - 1) / tDimensions.x_,
                          (-bounds_.getLowerLeft().y_ - 1) / tDimensions.y_);
            vertex = convertCoordinates(vertex + location_, wDimensions);
            glVertex2d(vertex.x_, vertex.y_);
            vertex = vertices_[2];
            glTexCoord2f ((bounds_.getUpperRight().x_ - 1) / tDimensions.x_,
                          (-bounds_.getUpperRight().y_ + 1) / tDimensions.y_);
            vertex = convertCoordinates(vertex + location_, wDimensions);
            glVertex2d(vertex.x_, vertex.y_);
            vertex = vertices_[3];
            glTexCoord2f ((bounds_.getLowerLeft().x_ + 1) / tDimensions.x_,
                          (-bounds_.getUpperRight().y_ + 1) / tDimensions.y_);
            vertex = convertCoordinates(vertex + location_, wDimensions);
            glVertex2d(vertex.x_, vertex.y_);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    Texture* Image::getTexture()
    {
        return(texture_);
    }
    void Image::setTexture(Texture* texture)
    {
        setDimensions(texture->getDimensions());
        bounds_ = Bounds(Pair(), getDimensions());
        texture_ = texture;
    }
    Bounds Image::getBounds()
    {
        return(bounds_);
    }
    void Image::setBounds(Bounds bounds)
    {
        if(bounds.getLowerLeft() < Pair() || bounds.getUpperRight() >
           texture_->getDimensions())
        {
            throw(ParameterException("bounds", "within texture dimensions",
                                     "previous value (unchanged)"));
        }
        else
        {
            bounds_ = bounds;
            setDimensions(bounds_.getUpperRight() - bounds_.getLowerLeft());
        }
    }
}

