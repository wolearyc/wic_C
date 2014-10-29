/* ----------------------------------------------------------------------------
 * wic - a simple 2D game engine for Mac OSX written in C
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
 * File:    wic_image.h
 * ----------------------------------------------------------------------------
 */
/** \file */
#ifndef WIC_IMAGE_H
#define WIC_IMAGE_H
#include "wic_pair.h"
#include "wic_bounds.h"
#include "wic_game.h"
#include "wic_texture.h"
#include "wic_color.h"
/** \brief an image that can be drawn to the screen
 *
 *  A WicImage should be initialized with wic_init_image. A WicImage does not 
 *  need to be deallocated, although the WicTexture* it contains does.
 */
typedef struct WicImage
{
    WicPair location;        /**< the screen location */
    WicPair center;          /**< the center to scale, rotate, or draw around */
    double rotation;         /**< the rotation measured in radians from the
                              *   positive x-axis */
    WicPair scale;           /**< the scale */
    WicBounds bounds;        /**< the drawing bounds */
    WicColor color;          /**< the color multiplier */
    bool draw_centered;      /**< whether or not to draw around the center */
    WicTexture* texture;     /**< the texture */
} WicImage;
/** \brief initializes a WicImage
 *  \param target the target WicImage
 *  \param location the desired screen location
 *  \param texture the desired WicTexture
 *  \return true on success, false on failure
 */
bool wic_init_image(WicImage* target, WicPair location, WicTexture* texture);
/** \brief fetches the geometric center of a WicImage
 *  \param target a WicImage
 *  \return the geometric center of the WicImage on success, {-1, -1} on failure
 */
WicPair wic_image_get_geometric_center(WicImage* target);
/** \brief draws a WicImage to the screen
 *  \param target the target WicImage
 *  \return true on success, false on failure
 */
bool wic_draw_image(WicImage* target, WicGame* game);
/** \brief deallocates a WicImage
 *  \param target the target WicImage
 *  \return true on success, false on failure
 */
#endif
