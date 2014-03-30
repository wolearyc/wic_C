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
 * File:    Paintable.h
 * ----------------------------------------------------------------------------
 */
#ifndef PAINTABLE_H
#define PAINTABLE_H
#include "Pair.h"
#include "Game.h"
#include "OpenGL/gl.h"
namespace wick
{
    /**
      * \brief an architectural superclass that should be inherited by any class
      *      that is "paintable" to the screen
      * 
      * Any subclass of Paintable should define a paint method. All Paintable 
      * objects have a screen location, a center (which can be painted around), 
      * and a geometric center that is defined within the subclass. The center 
      * and geometric centers are not relative to the screen, but are relative 
      * to the object they are defined in. Any rotation and scaling (defined in 
      * Rotateable and Scaleable respectively) is done around the center defined 
      * in Paintable.
      */
    class Paintable
    {
    public:
        /** \brief constructs Paintable based on a location
          *
          * This constructor constructs Paintable with a center at (0,0) and a
          * geometric center at (0,0). The Paintable constructed is painted 
          * around the center.
          * \param location the desired location
          */
        Paintable(Pair location);
        /** \brief constructs Paintable with location (0,0)
          *
          * This constructor constructs Paintable with a center at (0,0) and a
          * geometric center at (0,0). The Paintable constructed is painted
          * around the center.
          */
        Paintable();
        /** \brief constructs a Paintable identical to anotheer
          * \param other another Paintable
          */
        Paintable(const Paintable& other);
        /** \brief retrieves the screen location
          * \return the screen location
          */
        Pair getLocation();
        /** \brief modifies the screen location
          * \param the desired screen location
          */
        void setLocation(Pair location);
        /** \brief translates the screen location
          * \param translation the desired translation vector to be applied to
          *        the location
          */
        void translate(Pair translation);
        /** \brief retrieves the center
          * \return the center
          */
        Pair getCenter();
        /** \brief modifies the center
          * \param center the desired center
          */
        void setCenter(Pair center);
        /** \brief retrieves whether or not to paint around the center
          * \return true if the object is painted around the center, false 
          *         otherwise
          */
        bool isPaintedCentered();
        /** \brief modifies whether or not to paint around the center
          * \param paintCentered whether or not to paint around the center
          */
        void paintCentered(bool paintCentered);
        /** \brief retrieves the geometric center of the object
          *
          * The geometric center should be defined in subclasses. 
          * If it is not defined, the geometric center will always be (0,0), 
          * which is wrong is nearly all cases.
          */
        Pair getGeometricCenter();
        /** \brief paints the object to the screen
          *
          * This method must be defined by any subclass of Paintable
          */
        virtual void paint(Game* game) = 0;
    protected:
        Pair location_;        /**< the screen location */
        Pair center_;          /**< the center */
        bool paintCentered_;   /**< whether or not to paint around the center */
        Pair geometricCenter_; /**< the geometric center */
        Pair convertCoordinates(Pair coordinates, Pair dimensions);
    };
}
#endif
