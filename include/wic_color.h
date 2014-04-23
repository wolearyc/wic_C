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
 * File:    wic_color.h
 * ----------------------------------------------------------------------------
 */
#ifndef WIC_COLOR_H
#define WIC_COLOR_H
#include "OpenGL/gl.h"
#include "wic_error.h"
/** \brief an RGBA color
 *
 *  A WicColor can be initialized manually, but it's better to use 
 *  wic_init_color so errors can be caught. For the red, green, and blue 
 *  components, a value of 0 indicates no expression while a value of 255 
 *  indicates full expression. For the alpha component, a value of 0 indicates 
 *  full transparency, while a value of 255 indicates complete opacity.
 */
typedef struct WicColor
{
    unsigned char red;   /**< the red component; must be < 256 */
    unsigned char green; /**< the green component; must be < 256 */
    unsigned char blue;  /**< the blue component; must be < 256 */
    unsigned char alpha; /**< the alpha component; must be < 256 */
} WicColor;
extern const WicColor WIC_WHITE;   /**< white (255,255,255,255) */
extern const WicColor WIC_SILVER;  /**< silver (208,208,208,255) */
extern const WicColor WIC_GRAY;    /**< gray (128,128,128,255) */
extern const WicColor WIC_BLACK;   /**< black (0,0,0,255) */
extern const WicColor WIC_RED;     /**< red (255,0,0,255) */
extern const WicColor WIC_MAROON;  /**< maroon (128,0,0,255) */
extern const WicColor WIC_YELLOW;  /**< yellow (255,255,0,255) */
extern const WicColor WIC_ORANGE;  /**< orange (255,165,0,255) */
extern const WicColor WIC_OLIVE;   /**< olive (128,128,0,255) */
extern const WicColor WIC_LIME;    /**< lime (0,255,0,255) */
extern const WicColor WIC_GREEN;   /**< green (0,128,0,255) */
extern const WicColor WIC_AQUA;    /**< aqua (0,255,255,255) */
extern const WicColor WIC_TEAL;    /**< teal (0,128,128.255) */
extern const WicColor WIC_BLUE;    /**< blue (0,0,128,255) */
extern const WicColor WIC_NAVY;    /**< navy (0,0,128,255) */
extern const WicColor WIC_FUCHSIA; /**< fuchsia (255,0,255,255) */
extern const WicColor WIC_PURPLE;  /**< purple 128,0,128,255) */
/** \brief initializes an WicColor
 *  \param target the target WicColor; must be valid
 *  \param red the desired red component; must be < 256
 *  \param green the desired green component; must be < 256
 *  \param blue the desired blue component; must be < 256
 *  \param alpha the desired alpha component; must be < 256
 *  \return 0 on success, < 0 on failure
 */
int wic_init_color(WicColor* target, unsigned char red, unsigned char green,
               unsigned char blue, unsigned char alpha);
void wic_select_color(WicColor* target);
#endif
