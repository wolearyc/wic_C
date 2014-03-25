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
            return("fatal: " + message_);
        return(message_);
    }
    void WickException::handle()
    {
        if(fatal_)
            std::exit(1);
    }
    ParameterException::ParameterException(string name, string validValues,
                                           string correctedValue)
                       :WickException("parameter \"" + name + "\" was " +
                                      "invalid, valid values: " +
                                      validValues + ", value was " +
                                      "corrected to " + correctedValue, false)
    {
    }
    FileException::FileException(string filepath)
                  :WickException("File  at " + filepath + " cannot be found " +
                                     "or cannot be loaded", true)
    {
    }
    ArchitectureException::ArchitectureException(string message)
                          :WickException(message, true)
    {
        handle();
    }
}
