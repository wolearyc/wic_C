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
 * File:    wic_quad.c
 * ----------------------------------------------------------------------------
 */
#include "wic_quad.h"
struct WicGame
{
    GLFWwindow* window;
    WicPair dimensions;
    WicPair pixel_density;
    double seconds_per_frame;
    double previous_time;
    double delta;
    FT_Library freetype_library;
    
};
static WicPair vertices[4] = {(WicPair) {0,0}};
bool wic_init_quad(WicQuad* target, WicPair location, WicPair dimensions,
                   WicColor color)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    
    target->location = location;
    target->center = (WicPair) {0,0};
    target->rotation = 0.0;
    target->scale = (WicPair) {1,1};
    target->color = color;
    target->draw_centered = false;
    target->dimensions = dimensions;
    return true;
}
WicPair wic_quad_get_geometric_center(WicQuad* target)
{
    if(!target)
    {
        wic_throw_error(WIC_ERRNO_NULL_TARGET);
        return (WicPair) {-1,-1};
    }
    return wic_divide_pairs(target->dimensions, (WicPair) {2,2});
}
bool wic_draw_quad(WicQuad* target, WicGame* game)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!game)
        return wic_throw_error(WIC_ERRNO_NULL_GAME);
    double cosine = cos(target->rotation);
    double sine = sin(target->rotation);
    glColor4ub(target->color.red, target->color.green, target->color.blue,
               target->color.alpha);
    vertices[1].x = target->dimensions.x;
    vertices[2] = target->dimensions;
    vertices[3].y = target->dimensions.y; 
    glBegin(GL_QUADS);
    for(unsigned i = 0; i < 4; i++)
    {
        WicPair vertex = vertices[i];
        vertex = wic_subtract_pairs(vertex, target->center);
        vertex = wic_multiply_pairs(vertex, target->scale);
        double x = vertex.x * cosine - vertex.y * sine;
        double y = vertex.x * sine + vertex.y * cosine;
        vertex.x = x;
        vertex.y = y;
        if(!target->draw_centered)
            vertex = wic_add_pairs(vertex, target->center);
        vertex = wic_convert_location(wic_add_pairs(vertex, target->location),
                                      game->dimensions);
        glVertex2d(vertex.x, vertex.y);
    }
    glEnd();
    return true;
}

