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
 * File:    wic_pair.c
 * ----------------------------------------------------------------------------
 */
#include "wic_pair.h"
static const double WIC_EPSILON = 0.00001;
WicPair wic_add_pairs(WicPair a, WicPair b)
{
    return (WicPair) {a.x + b.x, a.y + b.y};
}
WicPair wic_subtract_pairs(WicPair a, WicPair b)
{
    return (WicPair) {a.x - b.x, a.y - b.y};
}
WicPair wic_multiply_pairs(WicPair a, WicPair b)
{
    return (WicPair) {a.x * b.x, a.y * b.y};
}
WicPair wic_divide_pairs(WicPair a, WicPair b)
{
    return (WicPair) {a.x / b.x, a.y / b.y};
}
bool wic_are_pairs_equal(WicPair a, WicPair b)
{
    return fabs(a.x - b.x) <= WIC_EPSILON && fabs(a.y - b.y) <= WIC_EPSILON;
}
double wic_get_distance_between_pairs(WicPair a, WicPair b)
{
    return sqrt(pow(a.x - b.x, 2.0) + pow(a.y - b.y, 2.0));
}
double wic_get_angle_between_pairs(WicPair a, WicPair b)
{
    return atan2(b.y - a.y, b.x - a.x);
}
double wic_get_norm_of_pair(WicPair pair)
{
    return sqrt(pow(pair.x, 2) + pow(pair.y ,2));
}
WicPair wic_transform_pair(WicPair pair, double rotation, WicPair scale,
                           WicPair center)
{
    double cosine = cos(rotation);
    double sine = sin(rotation);
    pair = wic_subtract_pairs(pair, center);
    pair = wic_multiply_pairs(pair, scale);
    double x = pair.x * cosine - pair.y * sine;
    double y = pair.x * sine + pair.y * cosine;
    pair.x = x;
    pair.y = y;
    return pair;
}
