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
 *  A WicQuad should be initialized via wic_init_quad. A WicQuad should
 *  eventually be deallocated via wic_free_quad.
 */
typedef struct WicQuad
{
    WicPair location;               /**< the screen location */
    WicPair p_dimensions;           /**< the dimensions */
    WicPair* p_vertices;            /**< the vertices */
    WicColor color;                 /**< the color */
    WicPair center;                 /**< the center to scale, rotate, and draw 
                                     *  around (if draw_centered = true)
                                     */
    WicPair p_geometric_center;     /**< the geometric center */
    bool draw_centered;             /**< whether or not to draw around the 
                                     *   center 
                                     */
    WicPair scale;                  /**< the scale */
    double rotation;                /**< the rotation measured in radians from 
                                     *  the positive x-axis
                                     */
} WicQuad;
/** \brief initializes a WicQuad
 *  \param target the target WicQuad
 *  \param location the desired screen location
 *  \param dimensions the desired dimensions
 *  \param color the desired color
 *  \return the error code
 */
enum WicError wic_init_quad(WicQuad* target, WicPair location,
                            WicPair dimensions, WicColor color);
/** \brief changes a WicQuad's dimensions
 *
 *  This function also updates the WicQuad's geometric center
 *  \param target the target WicQuad
 *  \param vertices the desired dimensions
 *  \return the error code
 */
enum WicError wic_set_quad_dimensions(WicQuad* target, WicPair dimensions);
/** \brief draws a WicQuad
 *  \param target the target WicQuad
 *  \param game the WicGame
 *  \return the error code
 */
enum WicError wic_draw_quad(WicQuad* target, WicGame* game);
/** \brief deallocates a WicQuad
 *  \param target the target WicQuad
 *  \return the error code
 */
enum WicError wic_free_quad(WicQuad* target);
#endif
