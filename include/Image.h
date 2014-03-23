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
// File:    Image.h
// ----------------------------------------------------------------------------
#ifndef IMAGE_H
#define IMAGE_H
#include "Bounds.h"
#include "Quad.h"
#include "Texture.h"
#include "WickException.h"
namespace wick
{
    /// \brief An Image to be painted to the screen.
    ///
    /// An Image is defined by a Texture, and can be moved, rotated, scaled, and 
    /// centered. In essense, an Image behaves just like Quad. Multiple Image 
    /// objects can be defined by the same Texture.
    class Image : public Quad
    {
    public:
        /// \brief A constructor.
        ///
        /// Constructs an unrotated and unscaled Image.
        /// \param location the screen location
        /// \param texture the texture
        Image(Pair location, Texture* texture);
        /// \brief Default constructor.
        ///
        /// This constructor does NOT construct a valid, paintable Image.
        Image();
        /// \brief Copy constructor.
        Image(const Image& other);
        /// \brief Paints the Image to the screen.
        ///
        /// \param game the game
        void paint(Game* game);
        /// \brief Gets the current Texture.
        ///
        /// \return the current Texture
        Texture* getTexture();
        /// \brief Changes the current Texture.
        ///
        /// \param texture the desired new Texture
        void setTexture(Texture* texture);
        /// \brief Returns the current Texture bounds
        ///
        /// \return the rectangular bounds of the Texture currently in use
        Bounds getBounds();
        /// \brief Modifies the current Texture bounds
        ///
        /// \param bounds the desired rectanglar bounds of the Texture to use
        /// \exception WickException non-fatal exception when the bounds 
        ///            go beyond the Texture's dimensions
        void setBounds(Bounds bounds);
    protected:
        Texture* texture_;
        Bounds bounds_;
    };
}
#endif

