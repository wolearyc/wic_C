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
 * File:    Image.h
 * ----------------------------------------------------------------------------
 */
#ifndef IMAGE_H
#define IMAGE_H
#include "Bounds.h"
#include "Quad.h"
#include "Texture.h"
#include "WickException.h"
namespace wick
{
    /** \brief an image that can be painted to the screen
      *
      * An Image is defined by a Texture, and can be moved, rotated, scaled, and
      * centered. In essense, an Image behaves just like Quad. Multiple Images
      * can use the same Texture.
      */
    class Image : public Quad
    {
    public:
        /** \brief constructs an unrotated, unscaled Image with its center at 
          *        lower-left corner
          * \param location the screen location
          * \param texture the texture
          */
        Image(Pair location, Texture* texture);
        /** \brief constructs an invalid Image
          */
        Image();
        /** \brief constructs an Image identical to another
          * \param other another Image
          */
        Image(const Image& other);
        /** \brief paints the Image to the screen
          * \param game the game
          */
        void paint(Game* game);
        /** \brief retrieves the Texture
          * \return the current Texture
          */
        Texture* getTexture();
        /** \brief modifies the Texture.
          *
          * \param texture the desired Texture
          */
        void setTexture(Texture* texture);
        /** \brief retrieves the rectangular Texture bounds
          * \return the bounds
          */
        Bounds getBounds();
        /** \brief modifies the rectangular Texture bounds
          * \param bounds the desired rectangular Texture bounds
          * \exception ParameterException non-fatal exception when the bounds
          *            go beyond the Texture's dimensions; the Texture bounds
          *            are corrected to cover the entire Texture
          */
        void setBounds(Bounds bounds);
    protected:
        Texture* texture_;
        Bounds bounds_;
    };
}
#endif

