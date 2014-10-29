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
 * File:    wic_error.h
 * ----------------------------------------------------------------------------
 */
/** \file */
#ifndef WIC_ERROR_H
#define WIC_ERROR_H
#include <stdio.h>
#include <string.h>
extern enum WicError wic_errno;
enum WicError
{
    WIC_ERRNO_NONE,                 /**< no error */
    WIC_ERRNO_GAME_ALREADY_INIT,
    WIC_ERRNO_NO_HEAP,              /**< out of heap memory */
    WIC_ERRNO_LOAD_FILE_FAIL,	    /**< file could not be found or loaded */
    WIC_ERRNO_NULL_TARGET,          /**< target is null */
    WIC_ERRNO_NULL_GAME,            /**< game is null */
    WIC_ERRNO_SMALL_X_DIMENSION,    /**< dimensions.x is less than 1 */
    WIC_ERRNO_SMALL_Y_DIMENSION,    /**< dimensions.y is less than 1 */
    WIC_ERRNO_NULL_TITLE,
    WIC_ERRNO_SMALL_TITLE,
    WIC_ERRNO_SMALL_FPS,
    WIC_ERRNO_GLFW_FAIL,
    WIC_ERRNO_MONITOR_FAIL,
    WIC_ERRNO_FREETYPE_FAIL,
    WIC_ERRNO_NULL_BUFFER,
    WIC_ERRNO_NO_GPU_MEM,
    WIC_ERRNO_NULL_FILEPATH,
    WIC_ERRNO_NULL_TEXTURE,
    WIC_ERRNO_NULL_VERTICES,
    WIC_ERRNO_SMALL_NUM_VERTICES,
    WIC_ERRNO_SMALL_POINT,
    WIC_ERRNO_NULL_RESULT,
    WIC_ERRNO_NULL_FONT,
    WIC_ERRNO_NULL_STRING,
};
/** \brief translates the lastest wic_errno into a meaningful string and 
 *  	   prints the string to stderr.
 */
void wic_print_errno_string();
int wic_throw_error(enum WicError errno);
#endif

