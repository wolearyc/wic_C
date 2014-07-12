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
    WicPair location;           /**< the screen location */
    char* p_string;             /**< the string to draw */
    size_t p_num_chars;         /**< the number of characters in string */
    WicFont* p_font;            /**< the font */
    WicImage* p_images;         /**< the actual images to draw */
    WicPair* p_offsets;         /**< the distance from each image to logical 
                                 *   text location
                                 */
    WicBounds p_bounds;         /**< the bounds of text */
    WicColor color;             /**< the color */
    WicPair center;             /**< the center to scale, rotate, and draw
                                 *   around (if draw_centered = true)
                                 */
    WicPair p_geometric_center; /**< the geometric center */
    bool draw_centered;         /**< whether or not to draw around the center */
    WicPair scale;              /**< the scale */
    double rotation;            /**< the rotation measured in radians from the
                                 *   positive x-axis
                                 */
    
} WicText;
/** \brief initializes a WicText
 *  \param target the target WicText
 *  \param location the desired screen location
 *  \param string the desired string to draw
 *  \param num_chars the desired number of visible characters in string
 *  \param font the desired font
 *  \param color the desired color
 *  \param game the WicGame
 *  \return the error code
 */
enum WicError wic_init_text(WicText* target, WicPair location, char* string,
                            size_t num_chars, WicFont* font, WicColor color,
                            WicGame* game);
/** \brief sets a WicText's string
 *  \param target the target WicText
 *  \param string the desired string to draw
 *  \param num_chars the desired number of visible characters in string
 *  \param game the WicGame
 *  \return the error code
 */
enum WicError wic_set_text_string(WicText* target, char* string,
                                  size_t num_chars, WicGame* game);
/** \brief sets a WicText's font
 *  \param target the target WicText
 *  \param font the desired font
 *  \param game the WicGame
 *  \return the error code
 */
enum WicError wic_set_text_font(WicText* target, WicFont* font, WicGame* game);
/** \brief draws a WicText to the screen
 *  \param target the target WicText
 *  \param game the WicGame
 *  \return the error code
 */
enum WicError wic_draw_text(WicText* target, WicGame* game);
/** \brief deallocates a WicText
 *  \param target the target WicText
 *  \return the error code
 */
enum WicError wic_free_text(WicText* target);
#endif
