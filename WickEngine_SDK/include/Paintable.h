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
// File:    Paintable.h
// ----------------------------------------------------------------------------
#ifndef PAINTABLE_H
#define PAINTABLE_H
#include "Pair.h"
#include "Game.h"
#include "GL/gl.h"
namespace wick
{
    /// \brief An architectural superclass that should be inherited by any class 
    ///        "paintable" to the screen.
    /// Any class that inherits from Paintable should define a paint method.
    /// All Paintable objects have a screen location, a center (which can
    /// be painted around), and a geometric center that is defined by subclasses. 
    /// The center and geometric centers are not relative to the screen, but 
    /// relative to the object they are defined in. Any rotation and scaling
    /// (defined in Rotateable and Scaleable respectively) is done around the
    /// center defined in Paintable.
    class Paintable
    {
    public:
        /// \brief A constructor.
        /// 
        /// Constructs a Paintable object which a center at (0,0) and
        /// a geometric center of (0,0).
        /// \param location the desired location
        Paintable(Pair location);
        /// \brief Default constructor.
        ///
        /// Constructs a Paintable object at location (0,0) with a center
        /// at (0,0) and a geometric center at (0,0).
        Paintable();
        /// \brief Copy constructor.
        Paintable(const Paintable& other);
        /// \brief Gets the screen location.
        ///
        /// \return the screen location
        Pair getLocation();
        /// \brief Modifies the screen location.
        ///
        /// \param the desired screen location
        void setLocation(Pair location);
        /// \brief Translated the screen location.
        ///
        /// \param translation the translation vector
        void translate(Pair translation);
        /// \brief Gets the center.
        ///
        /// \return the center
        Pair getCenter();
        /// \brief Modifies the center.
        ///
        /// \param center the desired center
        void setCenter(Pair center);
        /// \brief Gets whether or not the Paintable object is to be painted around
        ///        the center.
        ///
        /// \return whether or not the object is to be painted around the center
        bool isPaintedCentered();
        /// \brief Sets whether or not the Paintable object is to be painted around
        ///        the center.
        ///
        /// \param paintCentered whether or not the object should be painted around
        ///        the center.
        void paintCentered(bool paintCentered);
        /// \brief Returns the geometric center of the object.
        ///
        /// Keep in mind that the geometric center should be defined in subclasses.
        /// If it is not defined, the geometric center will always be (0,0).
        Pair getGeometricCenter();
        virtual void paint(Game* game) = 0;
    protected:
        Pair location_;        ///< The screen location.
        Pair center_;          ///< The center.
        bool paintCentered_;   ///< Whether or not to paint around the center.
        Pair geometricCenter_; ///< The geometric center.
        Pair convertCoordinates(Pair coordinates, Pair dimensions);
    };
}
#endif
