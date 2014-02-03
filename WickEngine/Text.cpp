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
// File:    Text.cpp
// ----------------------------------------------------------------------------

#include "Text.h"
namespace wick
{
    Text::Text(string message, Pair location, Font* font)
         :Paintable(location), Rotateable(), Scaleable()
    {
        oldLocation_ = Pair();
        font_ = font;
        message_ = message;
        setMessage(message_);
    }
    Text::Text(const Text& other)
    {
        message_ = other.message_;
        font_ = other.font_;
        images_ = other.images_;
    }
    Text::Text()
    {
        message_ = "";
        font_ = new Font();
    }

    void Text::paint(Window* window)
    {
        for(unsigned int i = 0; i < images_.size(); i++)
            images_[i].paint(window);
    }

    string Text::getMessage()
    {
        return(message_);
    }
    void Text::setMessage(string message)
    {
        message_ = message;
        images_.clear();
        images_ = font_->getImages(message);
        setLocation(location_);
        //setCenter(center_);
    }

    void Text::setLocation(Pair location)
    {
        Pair temp = location_;
        Paintable::setLocation(location);
        Pair translation = location - oldLocation_;
        for(unsigned int i = 0; i < images_.size(); i++)
            images_[i].translate(translation);
        oldLocation_ = temp;
    }
    void Text::setCenter(Pair center)
    {
        //Rotateable::setCenter(center);
        //for(unsigned int i = 0; i < images_.size(); i++)
        //{
            //Pair imageCenter = center_ - images_[i].getLocation() + location_;
            //images_[i].setCenter(imageCenter);
        //}
    }
    void Text::setRotation(float rotation)
    {
        Rotateable::setRotation(rotation);
        for(unsigned int i = 0; i < images_.size(); i++)
        {
            images_[i].setRotation(rotation_);
        }
    }
    void Text::setScale(Pair scale)
    {
        Scaleable::setScale(scale);
        for(unsigned int i = 0; i < images_.size(); i++)
        {
            images_[i].setScale(scale);
        }
    }
}
