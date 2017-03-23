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
 * File:    wic_bounds.h
 * ----------------------------------------------------------------------------
 */
/** \file */
#ifndef BOUNDS_H
#define BOUNDS_H
#include "wic_pair.h"
/** \brief a bounding rectangle, consisting of a lower left and an upper right 
 *         coordinate
 *
 *  With an WicImage, the lower left coordinate defines what part of the WicImage to 
 *  draw at the lower left, while the upper right coordinate defines what part 
 *  of the WicImage to draw at the upper right. This mechanism can be used to 
 *  flip the WicImage along some axis.
 */
typedef struct WicBounds
{
    WicPair lower_left;  /**< the lower left coordinate */
    WicPair upper_right; /**< the upper right coordinate */
} WicBounds;


#endif
