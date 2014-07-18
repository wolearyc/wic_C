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
 * File:    wic_polygon.h
 * ----------------------------------------------------------------------------
 */
/** \file */
#ifndef WIC_POLYGON_H
#define WIC_POLYGON_H
#include "wic_pair.h"
#include "wic_color.h"
#include "wic_game.h"
/** \brief a filled polygon that can be drawn to the screen
 *
 *  A WicPolygon should be initialized via wic_init_polygon. A WicPolygon should
 *  eventually be deallocated via wic_free_polygon.
 */
typedef struct WicPolygon
{
    WicPair location;          /**< the screen location */
    WicPair* vertices_ro;       /**< the set of vertices */
    size_t num_vertices_ro;     /**< the number of vertices */
    WicColor color;            /**< the color */
    WicPair center;            /**< the center to scale, rotate, and draw around
                                *   (if draw_centered = true)
                                */
    WicPair geometric_center_ro;/**< the geometric center */
    bool draw_centered;        /**< whether or not to draw around the center */
    WicPair scale;             /**< the scale */
    double rotation;           /**< the rotation measured in radians from the
                                *   positive x-axis
                                */
} WicPolygon;
/** \brief initializes a WicPolygon
 *  \param target the target WicPolygon
 *  \param location the desired screen location
 *  \param vertices the desired vertices (relative to the object), in clockwise
 *         or counterclockwise order
 *  \param num_vertices the number of elements in vertices; must be > 2; an
 *         incorrect value will result in undefined behavior
 *  \param color the desired color
 *  \return the error code
 */
enum WicError wic_init_polygon(WicPolygon* target, WicPair location,
                               WicPair* vertices, size_t num_vertices,
                               WicColor color);
/** \brief changes a WicPolygon's vertices
 *
 *  This function also updates the WicPolygon's geometric center.
 *  \param target the target WicPolygon
 *  \param vertices the desired vertices (relative to the object), in clockwise
 *         or counterclockwise order
 *  \param num_vertices the number of elements in vertices; must be > 2; an
 *         incorrect value will result in undefined behavior
 *  \return the error code
 */
enum WicError wic_set_polygon_vertices(WicPolygon* target, WicPair* vertices,
                                       size_t num_vertices);
/** \brief draws a WicPolygon
 *  \param polygon the target WicPolygon
 *  \param game the WicGame
 *  \return the error code
 */
enum WicError wic_draw_polygon(WicPolygon* target, WicGame* game);
/** \brief deallocates a WicPolygon
 *  \param target the target WicPolygon
 *  \return the error code
 */
enum WicError wic_free_polygon(WicPolygon* target);
#endif
