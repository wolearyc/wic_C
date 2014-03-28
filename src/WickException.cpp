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
// File:    WickException.cpp
// ----------------------------------------------------------------------------
#include "WickException.h"
namespace wick
{
    WickException::WickException(string message, bool fatal)
    :message_(message), fatal_(fatal)
    {
        std::cout << what();
    }
    WickException::WickException()
    :WickException("unkown exception", true)
    {
    }
    string WickException::what()
    {
        if(fatal_)
            return("fatal: " + message_ + "\n");
        return(message_ + "\n");
    }
    void WickException::handle()
    {
        if(fatal_)
            std::exit(1);
    }
    string WickException::getMessage()
    {
        return(message_);
    }
    bool WickException::isFatal()
    {
        return(fatal_);
    }
    ParameterException::ParameterException(string name, string validValues,
                                           string correctedValue)
    :WickException("parameter \"" + name + "\" was invalid, valid value(s): " +
                   validValues + ", value was corrected to " + correctedValue,
                   false),
    name_(name), validValues_(validValues), correctedValue_(correctedValue)
    {
    }
    string ParameterException::getName()
    {
        return(name_);
    }
    string ParameterException::getValidValues()
    {
        return(validValues_);
    }
    string ParameterException::getCorrectedValue()
    {
        return(correctedValue_);
    }
    FileException::FileException(string filepath)
    :WickException("file " + filepath + " cannot be found or cannot be loaded",
                   true),
    filepath_(filepath)
    {
    }
    string FileException::getFilepath()
    {
        return(filepath_);
    }
    ArchitectureException::ArchitectureException(string message)
    :WickException(message, true)
    {
    }
}
