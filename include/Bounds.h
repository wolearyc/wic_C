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
 * File:    Bounds.h
 * ----------------------------------------------------------------------------
 */
#ifndef BOUNDS_H
#define BOUNDS_H
#include "Pair.h"
namespace wick
{
    /** \brief a bounding rectangle
      *
      * Bounds is most commonly used when defining images that only use a
	  * specific rectangular portion of a texture. A single bounding rectangle
      * is defined by a lower-left coordinate and an upper-right coordinate.
      * The lower-left coordinate does not necessary need to be geometrically
      * at the lower-left, and similarly the upper-right coordinate does not 
      * need to be geometrically at the upper-right. Using this, textures
      * can be mirrored along the x or y axis. 
      * 
      * For example, say Image 'a' and Image 'b' use the same 32x32 texture
      * 'c'. 'a' has bounds Bounds(Pair(0,0), Pair(32,32)) while 'b' has bounds
      * Bounds(Pair(32,32), Pair(0,0)). When painted, 'b' will be 'a' reflected
      * on both the x and y axis.
      */
    class Bounds
    {
    public:
        /** \brief constructs Bounds based on two coordinates
          * \param lowerLeft the desired lower-left coordinate
          * \param upperRight the desired upper-right coordinate
          */
        Bounds(Pair lowerLeft, Pair upperRight);
        /** \brief constructs Bounds based on the components of two coordinates
          * \param lowerLeftX the desired x value of the lower-left coordinate
          * \param lowerLeftY the desired y value of the lower-left coordinate
          * \param upperRightX the desired x value of the upper-right coordinate
          * \param upperRightY the desired y value of the upper-right coordinate
          */
        Bounds(int lowerLeftX, int lowerLeftY, int upperRightX, int upperRightY);
        /** \brief constructs Bounds based on a base location and dimensions
          * \param location the desired location of the lower-left coordinate
          *        relative to whatever the Bounds is bounding
          * \xDimension the desired width from the lower-left coordinate
          * \yDimension the desired height from the lower-left coordinate
          */
        Bounds(Pair location, int xDimension, int yDimension);
        /** \brief constructs Bounds with a lower-left coordinate of (0,0) and
          *        an upper-right coordinate of (32,32)
          */
        Bounds();
        /** \brief contructs a Bounds identical to another
          * \param other another Bounds
          */
        Bounds(const Bounds& other);
        /** \brief retrieves the lower-left coordinate
          * \return the lower-left coordinate
          */
        Pair getLowerLeft();
        /** \brief modifies the lower-left coordinate
          * \param lowerLeft the desired lower-left coordinate
          */
        void setLowerLeft(Pair lowerLeft);
        /** \brief translates the lower-left coordinate
          * \param translation the translation vector to be applied to the 
          *        lower-left coordinate
          */
        void translateLowerLeft(Pair translation);
        /** \brief retrieves the upper-right coordinate
          * \return the upper-right coordinate
          */
        Pair getUpperRight();
        /** \brief modifies the upper-right coordinate
          * \param upperRight the desired upper-right coordinate
          */
        void setUpperRight(Pair upperRight);
        /** \brief translates the upper-right coordinate
          * \param translation the translation vector to be applied to the 
          *        upper-right coordinate
          */
        void translateUpperRight(Pair translation);
        /** \brief modifies the lower-left and upper-right coordinates
          *        simultaneously.
          * \param lowerLeft the desired lower-left coordinate
          * \param upperRight the desired upper-right coordinate
          */
        void setLowerLeftAndUpperRight(Pair lowerLeft, Pair upperRight);
    protected:
        Pair lowerLeft_;
        Pair upperRight_;
    };
}
#endif
