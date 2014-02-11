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
    /// \brief Designates exception locations.
    enum WickLocation
    {
        W_UNKNOWN,       ///< Unknown class.
        W_WICKEXCEPTION, ///< WickException class
        W_PAINTABLE,     ///< Paintable class.
        W_ROTATEABLE,    ///< Rotateable class.
        W_SCALEABLE,     ///< Scaleable class.
        W_IMAGE,         ///< Image class.
        W_TEXTURE,       ///< Texture class.
        W_POLYGON,       ///< Polygon class.
        W_QUAD,          ///< Quad class.
        W_STATE,         ///< State class.
        W_FONT,          ///< Font class.
        W_TEXT,          ///< Text class.
        W_BOUNDS,        ///< Bounds class.
        W_COLOR,         ///< Color class.
        W_PAIR,          ///< Pair class.
        W_GAME,          ///< Game class.
        W_WICKUTILITY    ///< WickUtility.
    };
    /// \brief Defines the exceptions present in the Wick Engine.
    ///
    /// WickException extends the C++ standard library exception class.
    /// Different exceptions are defined through the constructors.
    class WickException : public std::exception
    {
    public:
        /// \brief Assembles a new exception with a location, ID, and some
        ///        additional information and prints the exception's message.
        ///
        /// @param location where the exception was thrown.
        /// @param id the ID of the exception (determines the message).
        /// @param information Additional information, which usually is helpful
        ///        when debugging.
        WickException(enum WickLocation location, int id, string information);
        /// \brief Assembles a new exception with a location and ID and prints
        ///        the exception's message.
        ///
        /// @param location where the exception was thrown.
        /// @param id the ID of the exception (determines the message).
        WickException(enum WickLocation location, int id);
        /// \brief Default constructor (assembles and prints unknown
        ///        exception).
        WickException();
        /// \brief Constructs and retrieves the exception's message.
        /// @return the assembled message.
        const char* what();
        /// \brief If the exception was fatal, stops execution. If the
        ///        the exception was not fatal, lets execution continue.
        void handle();
    private:
        enum WickLocation location_;
        int id_;
        string information_;
        string message_;
        bool fatal_;
    };
}
#endif
