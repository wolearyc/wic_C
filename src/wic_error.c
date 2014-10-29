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
 * File:    wic_error.c
 * ----------------------------------------------------------------------------
 */
#include "wic_error.h"
void wic_get_errno_string()
{
	char message[100];
	strcpy(message, "[WIC ERROR]: ");
	switch(wic_errno)
	{
		case WIC_ERRNO_NONE:
			strcat(message, "no error"); break;
        case WIC_ERRNO_GAME_ALREADY_INIT:
            strcat(message, "a game is already initialized"); break;
		case WIC_ERRNO_NO_HEAP:
			strcat(message, "out of heap memory"); break;
		case WIC_ERRNO_LOAD_FILE_FAIL:
			strcat(message, "file could not be found or loaded"); break;
		case WIC_ERRNO_NULL_TARGET:
			strcat(message, "target is null"); break;
		case WIC_ERRNO_NULL_GAME:
			strcat(message, "game is null"); break;
		case WIC_ERRNO_SMALL_X_DIMENSION:
			strcat(message, "dimensions.x is too small"); break;
        case WIC_ERRNO_SMALL_Y_DIMENSION:
            strcat(message, "dimensions.y is too small"); break;
        case WIC_ERRNO_NULL_TITLE:
            strcat(message, "title is null"); break;
        case WIC_ERRNO_SMALL_TITLE:
            strcat(message, "title has zero characters"); break;
        case WIC_ERRNO_SMALL_FPS:
            strcat(message, "fps is less than 1"); break;
        case WIC_ERRNO_GLFW_FAIL:
            strcat(message, "GLFW: initialization failed"); break;
        case WIC_ERRNO_MONITOR_FAIL:
            strcat(message, "GLFW: monitor fetch failed"); break;
        case WIC_ERRNO_WINDOW_FAIL:
            strcat(message, "GLFW: window creation failed"); break;
        case WIC_ERRNO_FREETYPE_FAIL:
            strcat(message, "Freetype: initialization failed"); break;
        case  WIC_ERRNO_NULL_BUFFER:
            strcat(message, "buffer is null"); break;
        case WIC_ERRNO_NO_GPU_MEM:
            strcat(message, "out of GPU memory"); break;
        case WIC_ERRNO_NULL_FILEPATH:
            strcat(message, "filepath is null"); break;
        case WIC_ERRNO_NULL_TEXTURE:
            strcat(message, "texture is null"); break;
        case WIC_ERRNO_NULL_VERTICES:
            strcat(message, "vertices is null"); break;
        case WIC_ERRNO_SMALL_NUM_VERTICES:
            strcat(message, "num_vertices is less than 3"); break;
        case WIC_ERRNO_SMALL_POINT:
            strcat(message, "point is 0"); break;
        case WIC_ERRNO_NULL_RESULT:
            strcat(message, "result is null"); break;
            
		
	}
	strcat(message, "\n");
	fprintf(stderr, message);
}
int wic_throw_error(enum WicError errno)
{
    wic_errno = errno;
    return 0;
}

