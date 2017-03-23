/* ----------------------------------------------------------------------------
 * wic - a simple 2D game engine for Mac OSX written in C
 * Copyright (C) 2013-2017  Willis O'Leary
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
 * File:    wic_rect.h
 * ----------------------------------------------------------------------------
 */
/** \file */
#ifndef WIC_RECT_H
#define WIC_RECT_H
#include "wic_pair.h"
#include "wic_color.h"
#include "wic_game.h"
/**  \brief a filled rectangle that can be drawn to the screen
 *
 *  A WicRect should be initialized via wic_init_rect.
 */
typedef struct WicRect
{
    WicPair location;        /**< the screen location */
    WicPair center;          /**< the center to scale, rotate, or draw around */
    double rotation;         /**< the rotation measured in radians from the
                              *   positive x-axis */
    WicPair scale;           /**< the scale */
    WicColor color;          /**< the color multiplier */
    bool draw_centered;      /**< whether or not to draw around the center */
    WicPair dimensions;      /**< the dimensions */
} WicRect;
/** \brief initializes a WicRect
 *  \param target the target WicRect
 *  \param location the desired screen location
 *  \param dimensions the desired dimensions
 *  \param color the desired color
 *  \return true on success, false on failure
 */
bool wic_init_rect(WicRect* target, WicPair location, WicPair dimensions,
                   WicColor color);
/** \brief fetches the geometric center of a WicRect
 *  \param target a WicRect
 *  \return the geometric center of the WicRect on success, {-1, -1} on failure
 */
WicPair wic_rect_get_geo_center(WicRect* target);
/** \brief draws a WicRect
 *  \param target the target WicRect
 *  \param game the WicGame
 *  \return true on success, false otherwise
 */
bool wic_draw_rect(WicRect* target, WicGame* game);
#endif
