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
#include <stdbool.h>
enum WicError
{
    /* general errors */
    WICER_NONE,
    WICER_TARGET,
    WICER_HEAP,
    WICER_GAME,
    WICER_DIMENSIONS_X,
    WICER_DIMENSIONS_Y,
    WICER_FILEPATH,
    WICER_FONT,
    WICER_STRING,
    
    /* wic_game errors */
    WICER_TITLE,
    WICER_FPS,
    WICER_INIT_GLFW,
    WICER_FETCH_MONITOR,
    WICER_CREATE_WINDOW,
    WICER_FREETYPE,
    WICER_GLFW,
    
    /* wic_color errors */
    WICER_RED,
    WICER_GREEN,
    WICER_BLUE,
    WICER_ALPHA,
    
    /* wic_polygon errors */
    WICER_NUM_VERTICES,
    
    /* wic_texture errors */
    WICER_BUFFER,
    WICER_GPU,
    WICER_FILE,
    
    /* wic_image errors */
    WICER_TEXTURE,
    
    /* wic_quad errors */
    
    /* wic_font errors */
    WICER_POINT,

    /* wic_text errors */
    
    /* wic_server errors */
    WICER_SOCKET,
    WICER_RESERVED_PORT,
    WICER_PORT_IN_USE,
    WICER_ADDRESS_BIND,
    WICER_SERVER,
    WICER_PACKET,
    WICER_CLIENT_DNE,
    WICER_RESULT,
    WICER_RESERVED_PACKET,
    WICER_BANNED_PACKET,
    WICER_REJECTED_CONNECT_PACKET,
    WICER_NO_PACKET,
    WICER_ADDRESS,
    WICER_ADDRESS_NULL,
    WICER_RESULT_LEN,
    WICER_ADDRESS_DNE,
    
    /* wic_client errors */
    WICER_CLIENT,
    WICER_TIMEOUT,
    WICER_PACKET_UNKNOWN_SOURCE,
    WICER_NOT_JOINED,
    WICER_ALREADY_JOINED,
};
static enum WicError wic_error_code;
/** \brief reports the latest error code
 *  \param code the latest error code
 *  \return the latest error code
 */
enum WicError wic_report_error(enum WicError code);
/** \brief retrieves the latest error code
 *  \return the latest error code
 */
enum WicError wic_get_last_error();
/** \brief translates an error code into a human-readable message
 *  \param code the error code
 *  \return the error code translated into a human-readable message
 */
const char* wic_translate_error_code(enum WicError code);
#endif
