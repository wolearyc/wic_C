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
WicError wic_errno = WIC_ERRNO_NONE;
bool wic_print_errors = false;
bool wic_pause_errors = false;
void wic_print_errno_string()
{
	char message[100];
	strcpy(message, "[WIC ERROR]: ");
	switch(wic_errno)
	{
		case WIC_ERRNO_NONE:
			strcat(message, "no error"); break;
        case WIC_ERRNO_ALREADY_INIT:
            strcat(message, "an instance is already initialized"); break;
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
        case WIC_ERRNO_NULL_FONT:
            strcat(message, "font is null"); break;
        case WIC_ERRNO_NULL_STRING:
            strcat(message, "string is null"); break;
        case WIC_ERRNO_INVALID_RED:
            strcat(message, "red is not in range 0-255"); break;
        case WIC_ERRNO_INVALID_GREEN:
            strcat(message, "green is not in range 0-255"); break;
        case WIC_ERRNO_INVALID_BLUE:
            strcat(message, "blue is not in range 0-255"); break;
        case WIC_ERRNO_INVALID_ALPHA:
            strcat(message, "alpha is not in range 0-255"); break;
        case WIC_ERRNO_NULL_PACKET:
            strcat(message, "packet is null"); break;
        case WIC_ERRNO_NULL_NAME:
            strcat(message, "name is null"); break;
        case WIC_ERRNO_RESERVED_PORT:
            strcat(message, "port is reserved"); break;
        case WIC_ERRNO_SMALL_NAME:
            strcat(message, "name has 0 characters"); break;
        case WIC_ERRNO_LARGE_NAME:
            strcat(message, "name has > 20 characters"); break;
        case WIC_ERRNO_NULL_SERVER_IP:
            strcat(message, "server_ip is null"); break;
        case WIC_ERRNO_SMALL_LEN_SERVER_IP:
            strcat(message, "len_server_ip is 0"); break;
        case WIC_ERRNO_SOCKET_FAIL:
            strcat(message, "socket creation failed"); break;
        case WIC_ERRNO_PORT_IN_USE:
            strcat(message, "port in use"); break;
        case WIC_ERRNO_SOCKET_BIND_FAIL:
            strcat(message, "socket binding failed"); break;
        case WIC_ERRNO_CLIENT_ALREADY_JOINED:
            strcat(message, "client is already joined");
        case WIC_ERRNO_JOIN_FAIL_FULL:
            strcat(message, "server is full"); break;
        case WIC_ERRNO_JOIN_FAIL_BANNED:
            strcat(message, "client is banned"); break;
        case WIC_ERRNO_CLIENT_NOT_JOINED:
            strcat(message, "client not joined"); break;
        case WIC_ERRNO_TIMEOUT:
            strcat(message, "operation timed out"); break;
        case WIC_ERRNO_PACKET_UNKNOWN_SOURCE:
            strcat(message, "packet from unknown source"); break;
        case WIC_ERRNO_SMALL_MAX_CLIENTS:
            strcat(message, "max_clients < 1"); break;
        case WIC_ERRNO_LARGE_MAX_CLIENTS:
            strcat(message, "max_clients > 254"); break;
        case WIC_ERRNO_NOT_CLIENT_INDEX:
            strcat(message, "index < 1 (not a client index)"); break;
        case WIC_ERRNO_IMPOSSIBLE_INDEX:
            strcat(message, "index impossible given max clients"); break;
        case WIC_ERRNO_INDEX_UNUSED:
            strcat(message, "index not in use"); break;
        case WIC_ERRNO_LARGE_REASON:
            strcat(message, "reason has > 50 characters"); break;
        case WIC_ERRNO_NULL_NAME_OR_IP:
            strcat(message, "name_or_ip is null");
        case WIC_ERRNO_LARGE_NAME_OR_IP:
            strcat(message, "name_or_ip has > 20 characters"); break;
        case WIC_ERRNO_UNBANNED_NAME_OR_IP:
            strcat(message, "name_or_ip was never banned"); break;
	}
	strcat(message, "\n");
	fprintf(stderr, "%s", message);
}
void wic_print_all_errors()
{
    wic_print_errors = true;
}
void wic_pause_at_errors()
{
    wic_pause_errors = true;
}
bool wic_throw_error(WicError error)
{
    wic_errno = error;
    if(wic_print_errors)
        wic_print_errno_string();
    if(wic_pause_errors)
    {
        printf("Execution paused. Press return to continue...");
        while(getchar() != '\n');
    }
    return false;
}

