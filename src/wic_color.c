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
 * File:    wic_color.c
 * ----------------------------------------------------------------------------
 */
#include "wic_color.h"
const WicColor WIC_WHITE   = {255,255,255,255};
const WicColor WIC_SILVER  = {208,208,208,255};
const WicColor WIC_GRAY    = {128,128,128,255};
const WicColor WIC_BLACK   = {0,0,0,255};
const WicColor WIC_RED     = {255,0,0,255};
const WicColor WIC_MAROON  = {128,0,0,255};
const WicColor WIC_YELLOW  = {255,255,0,255};
const WicColor WIC_ORANGE  = {255,165,0,255};
const WicColor WIC_OLIVE   = {128,128,0,255};
const WicColor WIC_LIME    = {0,255,0,255};
const WicColor WIC_GREEN   = {0,128,0,255};
const WicColor WIC_AQUA    = {0,255,255,255};
const WicColor WIC_TEAL    = {0,128,128,255};
const WicColor WIC_BLUE    = {0,0,255,255};
const WicColor WIC_NAVY    = {0,0,128,255};
const WicColor WIC_FUCHSIA = {255,0,255,255};
const WicColor WIC_PURPLE  = {128,0,128,255};
enum WicError wic_init_color(WicColor* target, unsigned char red, unsigned char green,
               unsigned char blue, unsigned char alpha)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    if(red > 255)
        return wic_report_error(WICER_RED);
    if(green > 255)
        return wic_report_error(WICER_GREEN);
    if(blue > 255)
        return wic_report_error(WICER_BLUE);
    if(alpha > 255)
        return wic_report_error(WICER_ALPHA);
        
    target->red = red;
    target->green = green;
    target->blue = blue;
    target->alpha = alpha;
    return wic_report_error(WICER_NONE);
}