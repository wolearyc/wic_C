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
    /// \brief A generic wick exception
    ///
    /// A WickException can be either fatal (program exits when handle is
    /// called) or non-fatal (nothing happens when handle is called).
    /// WickException is the superclass for all the exceptions pertaining to
    /// wick.
    class WickException : public std::exception
    {
    public:
        /// \brief A constructor that prints the error message to the terminal
        /// \param message the error message
        /// \param fatal whether or not the exception should be fatal
        WickException(string message, bool fatal);
        /// \brief The default constructor that prints the error message to the
        ///        terminal
        ///
        /// A WickException constructed using the default constructor as the
        /// message "unknown exception" and is fatal.
        WickException();
        /// \brief Retrieves the formatted error message
        /// \return the formatted error message
        string what();
        /// \brief Exits the program if the exception was fatal, and does
        ///        nothing if the exception is non-fatal.
        void handle();
        /// \brief Retrieves the error message
        ///
        /// When printing out the error message to the terminal, it's best to
        /// use what(), not getMessage().
        /// \return the error message
        string getMessage();
        /// \brief Retrieves whether or not the exception should be fatal
        /// \return whether or not the exception should be fatal
        bool isFatal();
    protected:
        string message_;
        bool fatal_;
    };
    /// \brief A non-fatal exception that is thrown when parameters are invalid
    class ParameterException : public WickException
    {
    public:
        /// \brief A constructor that prints the error message to the terminal
        /// \param name the name of the invalid parameter
        /// \param the valid values the parameter can take
        /// \param the value the invalid parameter corrected to
        ParameterException(string name, string validValues, string
                           correctedValue);
        /// \brief Retrieves the name of the invalid parameter
        /// \return the name of the invalid parameter
        string getName();
        /// \brief Retrieves the valid values of the invalid parameter
        /// \return the valid values of the invalid parameter
        string getValidValues();
        /// \breif Retrieves what value the invalid parameter was corrected to
        /// \return the value the invalid parameter was corrected to
        string getCorrectedValue();
    protected:
        string name_;
        string validValues_;
        string correctedValue_;
    };
    /// \brief A non-fatal exception that is thrown when a file cannot be
    ///        found or cannot be loaded.
    class FileException : public WickException
    {
    public:
        /// \brief A constructor
        /// \param filepath the filepath of the file that could not be found or
        ///        loaded
        FileException(string filepath);
        /// \brief Retrieves the filepath of the file that could not be found or
        ///        loaded
        /// \return the filepath of the file that could not be found or loaded
        string getFilepath();
    protected:
        string filepath_;
    };
    /// \brief A fatal exception that is thrown when some part of wick fails
    ///
    /// It's advisable to call handle() when an ArchitectureException is thrown,
    /// terminating the program.
    class ArchitectureException : public WickException
    {
    public:
        /// \brief A constructor
        /// \param message the error message
        ArchitectureException(string message);
    };
}
#endif
