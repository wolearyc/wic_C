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
 * File:    wic_quad.h
 * ----------------------------------------------------------------------------
 */
/** \file */
#ifndef WIC_QUAD_H
#define WIC_QUAD_H
#include "wic_pair.h"
#include "wic_color.h"
#include "wic_game.h"
/**  \brief a filled rectangle that can be drawn to the screen
 *
 *  A WicQuad should be initialized via wic_init_quad.
 */
typedef struct WicQuad
{
    WicPair location;        /**< the screen location */
    WicPair center;          /**< the center to scale, rotate, or draw around */
    double rotation;         /**< the rotation measured in radians from the
                              *   positive x-axis */
    WicPair scale;           /**< the scale */
    WicColor color;          /**< the color multiplier */
    bool draw_centered;      /**< whether or not to draw around the center */
    WicPair dimensions;      /**< the dimensions */
} WicQuad;
/** \brief initializes a WicQuad
 *  \param target the target WicQuad
 *  \param location the desired screen location
 *  \param dimensions the desired dimensions
 *  \param color the desired color
 *  \return true on success, false on failure
 */
bool wic_init_quad(WicQuad* target, WicPair location, WicPair dimensions,
                   WicColor color);
/** \brief fetches the geometric center of a WicQuad
 *  \param target a WicQuad
 *  \return the geometric center of the WicQuad on success, {-1, -1} on failure
 */
WicPair wic_quad_get_geometric_center(WicQuad* target);
/** \brief draws a WicQuad
 *  \param target the target WicQuad
 *  \param game the WicGame
 *  \return true on success, false otherwise
 */
bool wic_draw_quad(WicQuad* target, WicGame* game);
#endif
