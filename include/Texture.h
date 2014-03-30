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
 * File:    Texture.h
 * ----------------------------------------------------------------------------
 */
#ifndef TEXTURE_H
#define TEXTURE_H
#include "Pair.h"
#include "WickException.h"
#include "SOIL/SOIL.h"
#include "OpenGL/gl.h"
#include <iostream>
#include <string>
using std::string;
namespace wick
{
    /** \brief defines constants for Texture filtering (behavior when images are
      *        scaled beyond or below their resolution)
      */
    enum class WickFilter
    {
        NEAREST = GL_NEAREST, /**< nearest filtering (no filtering) */
        LINEAR = GL_LINEAR    /**< linear filtering */
    };
    /** \brief defines constants for buffer formats
      */
    enum WickFormat
    {
        MONO,      /**< each pixel has one 1 bit value (black or white) */
        GREYSCALE, /**< each pixel has one 8 bit value */
        RGB,       /**< Each pixel has three 8 bit values, red, green, and blue
                     */
        RGBA  /**< Each pixel has four 8 bit values, red, green, blue, and alpha
                */
    };
    /** \brief a single 2D Texture loaded from the file system or a unsigned
      *        char array
      *
      * Textures are used by Images. Textures should be initialized as
      * pointers (using "new") and deallocated after use. Texture can load the
      * following file formats: non-1bpp and non-RLE BMP, non-interlaced PNG,
      * JPEG, TGA, DDS, PSD, and HDR. 
      */
    class Texture
    {
    public:
        /** \brief constructs Texture from an array
          * \param buffer the array
          * \param dimensions the pixel dimensions of the array
          * \param format the format of the array
          * \param filter the texture filter
          * \throw ParameterException non-fatal exception if either dimension
          *        values are less than or equal to 0; constructed Texture is
          *        invalid
          *        is terminated
          * \throw WickException non-fatal exception if dimensions and/or format
          *        is not compatible with the char buffer; constructed Texture
          *        is invalid
          */
        Texture(unsigned char* buffer, Pair dimensions, enum WickFormat format,
                enum WickFilter filter);
        /** \brief constructs Texture from an array that uses nearest filtering
         * \param buffer the array
         * \param dimensions the pixel dimensions of the array
         * \param format the format of the array
         * \throw ParameterException non-fatal exception if either dimension
         *        values are less than or equal to 0; constructed Texture is
         *        invalid
         *        is terminated
         * \throw WickException non-fatal exception if dimensions and/or format
         *        is not compatible with the char buffer; constructed Texture
         *        is invalid
         */
        Texture(unsigned char* buffer, Pair dimensions, enum WickFormat format);
        /** \brief constructs Texture from a file
          * \param filepath the absolute or relative filepath to the image file
          * \param filter the texture filter
          * \throw FileException non-fatal exception if no file can be found at
          *        or the file cannot be loaded by wick (invalid format or
          *        curruption); constructed Texture is invalid
          * \throw WickException non-fatal exception when there is an unknown
          *        error in loading the texture; constructed Texture is invalid
          */
        Texture(string filepath, enum WickFilter filter);
        /** \brief constructs Texture from a file that uses nearest filtering
         * \param filepath the absolute or relative filepath to the image file
         * \throw FileException non-fatal exception if no file can be found at
         *        or the file cannot be loaded by wick (invalid format or
         *        curruption); constructed Texture is invalid
         * \throw WickException non-fatal exception when there is an unknown
         *        error in loading the texture; constructed Texture is invalid
         */
        Texture(string filepath);
        /** \brief constructs an invalid Texture
          */
        Texture();
        /** \brief deallocates Texture
          */
        ~Texture();
        /** \brief retrieves the dimensions
          * \return the dimensions in pixels
          */
        Pair getDimensions();
        /** \brief selects the texture for painting
          *
          * This method is used behind the scenes, and does not need to be
          * used by the average wick user.
          */
        void select();
    private:
        unsigned int data_;
        Pair dimensions_;
        unsigned char* formatBuffer(unsigned char* buffer,
                                    enum WickFormat format);
    };
}
#endif
