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
#ifndef WIC_IMAGE_H
#define WIC_IMAGE_H
#include "wic_pair.h"
#include "wic_bounds.h"
#include "wic_game.h"
#include "wic_texture.h"
#include "wic_color.h"
/** \brief an image that can be drawn to the screen
 *
 *  A WicImage should be initialized with wic_init_image. A WicImage should
 *  eventually be freed via wic_free_image;
 */
typedef struct WicImage
{
    WicPair location;           /**< the screen location */
    WicTexture* p_texture;      /**< the texture */
    WicBounds p_bounds;         /**< the bounds */
    WicPair* p_vertices;        /**< the set of four vertices */
    WicColor color;             /**< the color multiplier */
    WicPair center;             /**< the center to scale, rotate, and draw around
                                 *   (if draw_centered = true)
                                 */
    WicPair p_geometric_center; /**< the geometric center */
    bool draw_centered;         /**< whether or not to draw around the center */
    WicPair scale;              /**< the scale */
    double rotation;            /**< the rotation measured in radians from the
                                 *   positive x-axis
                                 */
} WicImage;
/** \brief initializes a WicImage
 *  \param target the target WicImage; must be valid
 *  \param location the desired screen location
 *  \param texture the desired WicTexture; must be valid
 *  \return 0 on success, < 0 on failure
 */
int wic_init_image(WicImage* target, WicPair location, WicTexture* texture);
/** \brief sets a WicImage's texture
 *
 *  This function also updates the geometric center of the WicImage and sets the
 *  WicImage's bounds to cover the entire new texture.
 *  \param target the target WicImage; must be valid
 *  \param texture the desired WicTexture; must be valid
 *  \return 0 on success, < 0 on failure
 */
int wic_set_image_texture(WicImage* target, WicTexture* texture);
/** \brief sets a WicImage's bounds
 *  \param target the target WicImage; must be valid
 *  \param bounds the desired bounds; must not extend behind the WicImage's 
 *         WicTexture's dimensions.
 *  \return 0 on success, < 0 on failure
 */
int wic_set_image_bounds(WicImage* target, WicBounds bounds);
/** \brief draws a WicImage to the screen
 *  \param target the target WicImage; must be valid
 *  \param game the WicGame; must be valid
 *  \return 0 on success, < 0 on failure
 */
int wic_draw_image(WicImage* target, WicGame* game);
/** \brief deallocates a WicImage
 *  \param target the target WicImage; must be valid
 *  \return 0 on success, < 0 on failure
 */
int wic_free_image(WicImage* target);
#endif
