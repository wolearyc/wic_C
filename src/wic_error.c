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
static int wic_error_code = 0;
int wic_report_error(int code)
{
    wic_error_code = code;
    return code;
}
int wic_get_last_error()
{
    return wic_error_code;
}
const char* wic_translate_error_code(int code)
{
    switch(code)
    {
        /* wic_game.h */
        case 0:
            return "no error";
        case -1:
            return "wic_init_game : target invalid";
        case -2:
            return "wic_init_game : empty title";
        case -3:
            return "wic_init_game : dimension.x < 1";
        case -4:
            return "wic_init_game : dimension.y < 1";
        case -5:
            return "wic_init_game : fps = 0";
        case -6:
            return "wic_init_game : glfw3 could not be initialized";
        case -7:
            return "wic_init_game : glfw3 monitor could not be fetched";
        case -8:
            return "wic_init_game : window could not be created";
        case -9:
            return "wic_init_game : freetype could not be initialized";
        case -10:
            return "wic_updt_game : target invalid";
        case -11:
            return "wic_exit_game : target invalid";
        case -12:
            return "wic_free_game : target invalid";
        case -13:
            return "glfw3 error";
        /* wic_color.h */
        case -21:
            return "wic_init_color : target invalid";
        case -22:
            return "wic_init_color : red value > 255";
        case -23:
            return "wic_init_color : green value > 255";
        case -24:
            return "wic_init_color : blue value > 255";
        case -25:
            return "wic_init_color : alpha value > 255";
        /* wic_polygon.h */
        case -41:
            return "wic_init_polygon : target invalid";
        case -42:
            return "wic_init_polygon : num_vertices < 3";
        case -43:
            return "init_polygon : out of heap memory";
        case -44:
            return "wic_set_polygon_vertices : target invalid";
        case -45:
            return "wic_set_polygon_vertices : num_vertices < 3";
        case -46:
            return "wic_set_polygon_vertices : out of heap memory";
        case -47:
            return "wic_draw_polygon : target invalid";
        case -48:
            return "wic_draw_polygon : game invalid";
        case -49:
            return "wic_free_polygon : target invalid";
        /* wic_texture.h */
        case -61:
            return "wic_init_texture_from_buffer : target invalid";
        case -62:
            return "wic_init_texture_from_buffer : buffer not allocated";
        case -63:
            return "wic_init_texture_from_buffer : dimensions.x < 1";
        case -64:
            return "wic_init_texture_from_buffer : dimensions.y < 1";
        case -65:
            return "wic_init_texture_from_buffer : out of heap memory";
        case -66:
            return "wic_init_texture_from_buffer : out of heap memory";
        case -67:
            return "wic_init_texture_from_buffer : out of heap memory";
        case -68:
            return "wic_init_texture_from_buffer : out of gpu memory";
        case -69:
            return "wic_init_texture_from_file : target invalid";
        case -70:
            return "wic_init_texture_from_file : file could not be found or loaded";
        case -71:
            return "wic_init_texture_from_file : out of heap memory";
        case -72:
            return "wic_init_texture_from_file : out of heap memory";
        case -73:
            return "wic_init_texture_from_file : out of heap memory";
        case -74:
            return "wic_init_texture_from_file : out of gpu memory";
        case -75:
            return "wic_free_texture : target invalid";
        /* image.h */
        case -81:
            return "wic_init_image : target invalid";
        case -82:
            return "wic_init_image : texture invalid";
        case -83:
            return "wic_init_image : out of heap memory";
        case -84:
            return "wic_set_image_texture : target invalid";
        case -85:
            return "wic_set_image_texture : texture invalid";
        case -86:
            return "wic_set_image_texture : out of heap memory";
        case -87:
            return "wic_set_image_bounds : target invalid";
        case -88:
            return "wic_set_image_bounds : bounds reaches outside of texture";
        case -89:
            return "wic_set_image_bounds : out of heap memory";
        case -90:
            return "wic_draw_image : target invalid";
        case -91:
            return "wic_draw_image : game invalid";
        case -92:
            return "wic_free_image : target invalid";
        /* wic_quad.h */
        case -101:
            return "wic_init_quad : target invalid";
        case -102:
            return "wic_init_quad : out of heap memory";
        case -103:
            return "wic_set_quad_dimensions : target invalid";
        case -104:
            return "wic_set_quad_dimensions : out of heap memory";
        case -105:
            return "wic_draw_quad : target invalid";
        case -106:
            return "wic_draw_quad : game invalid";
        case -107:
            return "wic_free_quad : target invalid";
        /* wic_font.h */
        case -121:
            return "wic_init_font : target invalid";
        case -122:
            return "wic_init_font : filepath invalid";
        case -123:
            return "wic_init_font : game invalid";
        case -124:
            return "wic_init_font : file could not be found or loaded";
        case -125:
            return "wic_init_font : out of heap memory";
        case -126:
            return "wic_init_font : point == 0";
        case -127:
            return "wic_render_string : result invalid";
        case -128:
            return "wic_render_string : font invalid";
        case -129:
            return "wic_render_string : string invalid";
        case -130:
            return "wic_render_string : game invalid";
        case -131:
            return "wic_render_string : out of heap memory";
        case -132:
            return "wic_free_font : target invalid";
            
            
        case -666:
            return "satan detected, core dumped";
        default: /* usually error_code = 1000 */
            return "unknown error";
    }
}
