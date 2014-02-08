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
    Text::Text(Pair location, string message, Font* font, vector<Color> colors)
         :Paintable(location), Rotateable(), Scaleable(),
          message_(message), font_(font), colors_(colors)
    {
        setMessage(message);
    }
    Text::Text(Pair location, string message, Font* font,
               initializer_list<Color> colors)
         :Text(location, message, font, (vector<Color>) colors)
    {
    }
    Text::Text(Pair location, string message, Font* font, Color color)
         :Text(location, message, font, {color})
    {
    }
    Text::Text(const Text& other)
         :Paintable(other), Rotateable(other), Scaleable(other),
          message_(other.message_), font_(other.font_), images_(other.images_),
          colors_(other.colors_)
    {
    }
    Text::Text()
         :Paintable(), Rotateable(), Scaleable(), message_(""), font_(0)
    {
    }
    void Text::paint(Window* window)
    {
        unsigned int length = images_.size();
        for(unsigned int i = 0; i < length; i++)
        {
            Pair offset = offsets_[i];
            images_[i].setCenter(center_ - offset);
            Pair location = location_;
            if(!paintCentered_)
                location += center_;
            images_[i].setLocation(location);
            images_[i].setScale(scale_);
            images_[i].setRotation(rotation_);
            images_[i].paint(window);
        }
    }
    string Text::getMessage()
    {
        return(message_);
    }
    void Text::setMessage(string message)
    {
        message_ = message;
        images_ = font_->getImages(message_);
        offsets_.clear();
        unsigned int length = images_.size();
        for(unsigned int i = 0; i < length; i++)
        {
            images_[i].paintCentered(true);
            offsets_.push_back(images_[i].getLocation());
        }
        if(length != 0)
        {
            geometricCenter_ = (offsets_[length-1] +
                                images_[length-1].getDimensions()) / 2.0;
        }
        setColors(colors_);
    }
    vector<Color> Text::getColors()
    {
        return(colors_);
    }
    void Text::setColors(vector<Color> colors)
    {
        colors_ = colors;
        int colorIndex = 0;
        unsigned int length = message_.length();
        for(unsigned int i = 0; i < length; i++)
        {
            if(colorIndex >= colors_.size())
                colorIndex = 0;
            if(message_[i] != 32)
            {
                images_[i].setColor(colors_[colorIndex]);
                colorIndex++;
            }
        }
    }
    void Text::setColors(initializer_list<Color> colors)
    {
        setColors((vector<Color>) colors);
    }
    void Text::setColor(Color color)
    {
        setColors({color});
    }
}

