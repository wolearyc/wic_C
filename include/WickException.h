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
 * File:    WickException.h
 * ----------------------------------------------------------------------------
 */
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
    /** \brief a generic wick exception
      *
      * WickException can define either a fatal or non-fatal exception. When
      * an exception is thrown by wick, an error message is automatically 
      * printed to the terminal. The wick user should catch these exceptions
      * and can call the handle() method to either 1) stop the program if the
      * exception is fatal or 2) do nothing if the exception is non-fatal.
      *
      * WickException is the superclass for all the exceptions pertaining to
      * wick. All of WickException's subclasses act behave similarly to
      * WickException.
      */
    class WickException : public std::exception
    {
    public:
        /** \brief constructs WickException
          * \param message the error message
          * \param fatal whether or not the exception is fatal
          */
        WickException(string message, bool fatal);
        /** \brief constructs a fatal, "unknown error" exception
          */
        WickException();
        /**\brief retrieves the formatted error message
          * \return the formatted error message
          */
        string what();
        /** \brief exits the program if the exception was fatal, and does
          *        nothing if the exception is non-fatal
          */
        void handle();
        /** \brief retrieves the error message
          *
          * When printing out the error message to the terminal, it's best to
          * use what(), not getMessage(), since what() will format the error 
          * message for printing
          * \return the error message
          */
        string getMessage();
        /** \brief retrieves whether or not the exception should be fatal
          * \return true if the exception is fatal, false otherwise
          */
        bool isFatal();
    protected:
        string message_;
        bool fatal_;
    };
    /** \brief a non-fatal exception thrown when parameters are invalid
      *
      * A ParameterException contains information on which parameter was
      * invalid, the possible valid values for the parameter, and what the
      * parameter was corrected to.
      */
    class ParameterException : public WickException
    {
    public:
        /** \brief constructs ParameterException
          * \param name the name of the invalid parameter
          * \param validValues the valid values the parameter can take
          * \param correctedValue the value the invalid parameter corrected to
          */
        ParameterException(string name, string validValues, string
                           correctedValue);
        /** \brief retrieves the name of the invalid parameter
          * \return the name of the invalid parameter
          */
        string getName();
        /** \brief retrieves the valid values of the invalid parameter
          * \return the valid values of the invalid parameter
          */
        string getValidValues();
        /** \breif retrieves the value the invalid parameter was corrected to
          * \return the value the invalid parameter was corrected to
          */
        string getCorrectedValue();
    protected:
        string name_;
        string validValues_;
        string correctedValue_;
    };
    /** \brief a non-fatal exception thrown when a file cannot be found or 
      *        cannot be loaded
      *
      */
    class FileException : public WickException
    {
    public:
        /** \brief constructs FileException
          * \param filepath the filepath of the file that could not be found or
          *        loaded
          */
        FileException(string filepath);
        /** \brief retrieves the filepath of the file that could not be found or
          *        loaded
          * \return the filepath of the file that could not be found or loaded
          */
        string getFilepath();
    protected:
        string filepath_;
    };
    /** \brief a fatal exception that is thrown when some part of wick fails
      *
      * It is advisable to call handle() when an ArchitectureException is 
      * thrown since nothing can be done by the wick user to correct the error.
      */
    class ArchitectureException : public WickException
    {
    public:
        /** \brief constructs ArchitectureException
          * \param message the error message
          */
        ArchitectureException(string message);
    };
}
#endif
