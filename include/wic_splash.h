/* ----------------------------------------------------------------------------
 * wic - a simple 2D game engine for Mac OSX written in C
 * Copyright (C) 2013-2014  Will O'Leary
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.s
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------------------------
 * File:    wic_splash.h
 * ----------------------------------------------------------------------------
 */
/** \file */
#ifndef WIC_SPLASH_H
#define WIC_SPLASH_H
#include <math.h>
#include "wic_image.h"
#include "wic_error.h"
#include "wic_color.h"
#include "wic_game.h"
#include "wic_quad.h"
extern const WicColor WIC_SPLASH_BACKGROUND_COLOR; /**< standard and preferred
                                                    *   splash screen background
                                                    *   color
                                                    */
extern const WicColor WIC_SPLASH_TEXT_COLOR; /**< standard and preferred splash
                                              *   screen text color 
                                              */
/** \brief draws the wic splash screen and exits when the animation completes
 *  
 *  A simple call to wic_draw_splash before entering your game code is not 
 *  required, but the publicity and credit is greatly appreciated. As a bonus,
 *  the wic splash screen makes your game more polished and professional.
 *  \param background_color the desired background color (use of
 *         WIC_SPLASH_BACKGROUND_COLOR is encouraged)
 *  \param text_color the desired text color (use of WIC_SPLASH_TEXT_COLOR is
 *         encouraged)
 *  \param game the game
 *  \return true on success, false on failure
 */
bool wic_draw_splash(WicColor background_color, WicColor text_color,
                     WicGame* game);
#endif