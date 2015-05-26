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
 * File:    wic_text.h
 * ----------------------------------------------------------------------------
 */
/** \file */
#ifndef WIC_TEXT
#define WIC_TEXT
#include "wic_pair.h"
#include "wic_font.h"
#include "wic_image.h"
#include "wic_bounds.h"
/** \brief horizontal text that can be drawn to the screen
 *
 *  A WicText should be initialized with wic_init_text. A WicText should 
 *  eventually be freed via wic_free_text.
 */
typedef struct WicText
{
    WicPair location;        /**< the screen location */
    WicPair center;          /**< the center to scale, rotate, or draw around */
    double rotation;         /**< the rotation measured in radians from the
                              *   positive x-axis */
    WicPair scale;           /**< the scale */
    WicBounds bounds;        /**< the drawing bounds */
    WicColor color;          /**< the color multiplier */
    bool draw_centered;      /**< whether or not to draw around the center */
    char* string;            /**< the string to draw */
    size_t len_string;       /**< the length of string */
    WicPair* offsets;        /**< the offsets of each glyph from location */
    WicImage* images;        /**< the glyph images */
    WicFont* font;           /**< the font */
} WicText;
/** \brief initializes a WicText
 *  \param target the target WicText
 *  \param location the desired screen location
 *  \param string the desired string to draw
 *  \param len_string the length of the string
 *  \param font the desired font
 *  \param color the desired color
 *  \return true on success, false on failure
 */
bool wic_init_text(WicText* target, WicPair location, char* string,
                   size_t len_string, WicFont* font, WicColor color);
/** \brief sets a WicText's string, resizing the bounds to fit the entire 
 *         string.
 *  \param target the target WicText
 *  \param string the desired new string to draw
 *  \param len_string the length of the string
 */
bool wic_text_set_string(WicText* target, char* string, size_t len_string);
/** \brief draws a WicText to the screen
 *  \param target the target WicText
 *  \param game the WicGame
 *  \return true on success, false on failure
 */
bool wic_draw_text(WicText* target, WicGame* game);
/** \brief deallocates a WicText
 *  \param target the target WicText
 *  \return true on success, false on failure
 */
bool wic_free_text(WicText* target);
#endif
