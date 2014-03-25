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
// File:    WickException.h
// ----------------------------------------------------------------------------
#ifndef WICKEXCEPTION_H
#define WICKEXCEPTION_H
#include "WickUtility.h"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
using std::string;
namespace wick
{
    class WickException : public std::exception
    {
    public:
        WickException(string message, bool fatal);
        WickException();
        string what();
        void handle();
    protected:
        string message_;
        bool fatal_;
    };
    class ParameterException : public WickException
    {
    public:
        ParameterException(string name, string acceptedValues, string
                           correctedValue);
    };
    class FileException : public WickException
    {
    public:
        FileException(string filepath);
    };
    class ArchitectureException : public WickException
    {
    public:
        ArchitectureException(string message);
    };
}
#endif
