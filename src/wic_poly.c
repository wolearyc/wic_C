/* ----------------------------------------------------------------------------
 * wic - a simple 2D game engine for Mac OSX written in C
 * Copyright (C) 2013-2017  Willis O'Leary
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
 * File:    wic_poly.c
 * ----------------------------------------------------------------------------
 */
#include "wic_poly.h"
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
bool wic_init_poly(WicPoly* target, WicPair location, WicPair* vertices,
                      unsigned num_vertices, WicColor color)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!vertices)
        return wic_throw_error(WIC_ERRNO_NULL_VERTICES);
    if(num_vertices < 3)
        return wic_throw_error(WIC_ERRNO_SMALL_NUM_VERTICES);
    WicPair* new_vertices = malloc(sizeof(WicPair) * num_vertices);
    if(!new_vertices)
        return wic_throw_error(WIC_ERRNO_NO_HEAP);
    memcpy(new_vertices, vertices, num_vertices * sizeof(WicPair));
    
    target->location = location;
    target->center = (WicPair) {0,0};
    target->rotation = 0.0;
    target->scale = (WicPair) {1,1};
    target->color = color;
    target->draw_centered = false;
    target->vertices = new_vertices;
    target->num_vertices = num_vertices;
    return true;
}
WicPair wic_poly_get_geo_center(WicPoly* target)
{
    if(!target)
    {
        wic_throw_error(WIC_ERRNO_NULL_TARGET);
        return (WicPair) {-1,-1};
    }
    WicPair result = {0,0};
    for(unsigned i = 0; i < target->num_vertices; i++)
        result = wic_add_pairs(result, target->vertices[i]);
    result = wic_divide_pairs(result, (WicPair) {target->num_vertices,
                                                target->num_vertices});
    return result;
}
bool wic_draw_poly(WicPoly* target, WicGame* game)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!game)
        return wic_throw_error(WIC_ERRNO_NULL_GAME);
    double cosine = cos(target->rotation);
    double sine = sin(target->rotation);
    glColor4ub(target->color.red, target->color.green, target->color.blue,
               target->color.alpha);
    glBegin(GL_POLYGON);
    for(unsigned i = 0; i < target->num_vertices; i++)
    {
        WicPair vertex = target->vertices[i];
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
bool wic_free_poly(WicPoly* target)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    free(target->vertices);
    
    target->location = (WicPair) {0,0};
    target->center = (WicPair) {0,0};
    target->rotation = 0.0;
    target->scale = (WicPair) {0,0};
    target->color = WIC_WHITE;
    target->draw_centered = false;
    target->vertices = 0;
    target->num_vertices = 0;
    return true;
}
