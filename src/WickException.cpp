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
// File:    WickException.cpp
// ----------------------------------------------------------------------------
#include "WickException.h"
namespace wick
{
    WickException::WickException(enum WickLocation location, int id,
                                 string information)
                  :location_(location), id_(id), information_(information),
                   message_(""), fatal_(false)
    {
        std::cerr << what();
    }
    WickException::WickException(enum WickLocation location, int id)
                  :WickException(location, id, "")
    {
    }
    WickException::WickException()
                  :WickException(W_UNKNOWN, -1)
    {
    }
    const char* WickException::what()
    {
        switch(location_)
        {
        case W_UNKNOWN:
            message_ += "Unknown    ";
            break;
        case W_WICKEXCEPTION:
            message_ += "WickError  ";
            break;
        case W_PAINTABLE:
            message_ += "Paintable  ";
            break;
        case W_ROTATEABLE:
            message_ += "Rotateable ";
            break;
        case W_SCALEABLE:
            message_ += "Scaleable  ";
            break;
        case W_IMAGE:
            message_ += "Image      ";
            break;
        case W_TEXTURE:
            message_ += "Texture    ";
            break;
        case W_POLYGON:
            message_ += "Polygon    ";
            break;
        case W_QUAD:
            message_ += "Quad       ";
            break;
        case W_STATE:
            message_ += "State      ";
            break;
        case W_FONT:
            message_ += "Font       ";
            break;
        case W_TEXT:
            message_ += "Text       ";
            break;
        case W_BOUNDS:
            message_ += "Bounds     ";
            break;
        case W_COLOR:
            message_ += "Color      ";
            break;
        case W_PAIR:
            message_ += "Pair       ";
            break;
        case W_GAME:
            message_ += "Game       ";
            break;
        case W_WICKUTILITY:
            message_ += "WickUtility";
        default:
            message_ += "Unknown    ";
            break;
        }
        message_ += " : ";
        switch(id_)
        {
        case 0:
            message_ += "Empty title. Title set to \"Wick Game\"";
            break;
        case 1:
            message_ += "X dimension cannot be less than zero. X dimension set to 500 pixels";
            break;
        case 2:
            message_ += "Y dimension cannot be less than zero. Y dimension set to 500 pixels";
            break;
        case 3:
            message_ += "GLFW library failed to initialize";
            fatal_ = true;
            break;
        case 4:
            message_ += "OS Window creation failed";
            fatal_ = true;
            break;
        case 5:
            message_ += "State ID " + information_ + " is already in use";
            fatal_ = false;
            break;
        case 6:
            message_ += "The State with ID " + information_ + " is the selected state, and thus cannot be deallocated";
            break;
        case 7:
            message_ += "The State with ID " + information_ + " is the selected state, and thus cannot be removed";
            break;
        case 8:
            message_ += "The State with ID " + information_ + " could not be found";
            break;
        case 9:
            message_ += "GLFW error [" + information_ + "]";
            fatal_ = true;
            break;
        case 10:
            message_ += "Could not load image file " + information_;
            fatal_ = true;
            break;
        case 11:
            message_ += "X dimension must be greater than 0";
            fatal_ = true;
            break;
        case 12:
            message_ += "Y dimension must be greater than 0";
            fatal_ = true;
            break;
        case 13:
            message_ += "Bounds must be within texture dimensions";
            fatal_ = true;
            break;
        case 14:
            message_ += "Red value must be equal or less than 255. Red value set to 255";
            break;
        case 15:
            message_ += "Green value must be equal or less than 255. Green value set to 255";
            break;
        case 16:
            message_ += "Blue value must be equal or less than 255. Blue value set to 255";
            break;
        case 17:
            message_ += "Alpha value must be equal or less than 255. Alpha value set to 255";
            break;
        case 18:
            message_ += "Could not load font file " + information_;
            fatal_ = true;
            break;
        default:
            message_ += "Unknown exception";
            fatal_ = true;
            break;
        }
        if(fatal_)
            message_ = "ERROR --- " + message_;
        else
            message_ = "WARNING - " + message_;
        message_ += " (" + toString(id_) + ").\n";
        return(message_.c_str());
    }
    void WickException::handle()
    {
        if(fatal_)
            std::exit(1);
    }
}
