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
 * File:    wic_pair.h
 * ----------------------------------------------------------------------------
 */
/** \file */
#ifndef WIC_PAIR_H
#define WIC_PAIR_H
#include <math.h>
#include <stdbool.h>
/** \brief holds an x and a y double precision floating point value
 *
 *  WicPair is the workhorse of wic. A WicPair can represent 2D dimensions, a 2D
 *  vector, 2D scaling information, and, most commonly, coordinates.
 */
typedef struct WicPair
{
    double x;
    double y;
} WicPair;
/** \brief adds two WicPairs
 *  \param a a WicPair
 *  \param b another WicPair
 *  \return the component-wise sum of a and b
 */
WicPair wic_add_pairs(WicPair a, WicPair b);
/** \brief subtracts two WicPairs
 *  \param a a WicPair
 *  \param b another WicPair
 *  \return the component-wise difference between a and b
 */
WicPair wic_subtract_pairs(WicPair a, WicPair b);
/** \brief multiplies two WicPairs
 *  \param a a WicPair
 *  \param b another WicPair
 *  \return the component-wise product of a and b
 */
WicPair wic_multiply_pairs(WicPair a, WicPair b);
/** \brief divides two WicPairs
 *  \param a a WicPair
 *  \param b another WicPair
 *  \return the component-wise division between a and b
 */
WicPair wic_divide_pairs(WicPair a, WicPair b);
/** \brief determines whether two WicPairs are equal (respective components are
 *         within 0.00001)
 *  \param a a WicPair
 *  \param b another WicPair
 *  \return true if a and b are equal, and false otherwise
 */
bool wic_are_pairs_equal(WicPair a, WicPair b);
/** \brief computes the distance between two WicPairs
 *  \param a a WicPair
 *  \param b another WicPair
 *  \return the distance between a and b on the x,y plane
 */
double wic_get_distance_between_pairs(WicPair a, WicPair b);
/** \brief computes the angle between two WicPairs
 *  \param a a WicPair
 *  \param b another WicPair
 *  \return the angle between a and b
 */
double wic_get_angle_between_pairs(WicPair a, WicPair b);
/** \brief computes the norm of a WicPair
 *  \param pair a WicPair
 *  \return the norm of the WicPair
 */
double wic_get_norm_of_pair(WicPair pair);
/** \brief transforms a WicPair based on a rotation, scale, and center
 *  \param pair the WicPair
 *  \param rotation the rotation
 *  \param scale the scale
 *  \param center the center to rotate and scale around
 *  \return the transformed WicPair
 */
WicPair wic_transform_pair(WicPair pair, double rotation, WicPair scale,
                           WicPair center);
#endif
