/* ----------------------------------------------------------------------------
 * wick - a simple, object-oriented 2D game engine for Mac OSX written in C++
 * Copyright (C) 2013-2014  Will O'Leary
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------------------------
 * File:    WickUtility.h
 * ----------------------------------------------------------------------------
 */
#ifndef WICKUTILITY_H
#define WICKUTILITY_H
#include <sstream>
#include <string>
using std::string;
namespace wick
{
    /** \brief converts an integer into a string
      * \return the integer in string form
      */
    string toString(int n);
}
#endif
