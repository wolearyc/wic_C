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
int wic_init_quad(WicQuad* target, WicPair location, WicPair dimensions, WicColor color)
{
    if(target == 0)
        return wic_report_error(-101);
    WicPair* new_vertices = malloc(4 * sizeof(WicPair));
    if(new_vertices == 0)
        return wic_report_error(-102);
    target->location = location;
    target->p_dimensions = dimensions;
    target->p_vertices = new_vertices;
    target->p_vertices[0] = (WicPair) {0,0};
    target->p_vertices[1] = (WicPair) {dimensions.x, 0};
    target->p_vertices[2] = dimensions;
    target->p_vertices[3] = (WicPair) {0, dimensions.y};
    target->color = color;
    target->center = (WicPair) {0,0};
    target->p_geometric_center = wic_divide_pairs(dimensions, (WicPair) {2,2});
    target->draw_centered = false;
    target->scale = (WicPair) {1,1};
    target->rotation = 0.0;
    return wic_report_error(0);
}
int wic_set_quad_dimensions(WicQuad* target, WicPair dimensions)
{
    if(target == 0)
        return wic_report_error(-103);
    WicPair* new_vertices = realloc(target->p_vertices, 4 * sizeof(WicPair));
    if(new_vertices == 0)
        return wic_report_error(-104);
    target->p_dimensions = dimensions;
    target->p_vertices = new_vertices;
    target->p_vertices[0] = (WicPair) {0,0};
    target->p_vertices[1] = (WicPair) {dimensions.x,0};
    target->p_vertices[2] = dimensions;
    target->p_vertices[3] = (WicPair) {0, dimensions.y};
    target->p_geometric_center = wic_divide_pairs(dimensions, (WicPair) {2,2});
    return wic_report_error(0);
}
int wic_draw_quad(WicQuad* target, WicGame* game)
{
    if(target == 0)
        return wic_report_error(-105);
    if(game == 0)
        return wic_report_error(-106);
    double cosine = cos(target->rotation);
    double sine = sin(target->rotation);
    wic_select_color(&(target->color));
    glBegin(GL_QUADS);
    for(int i = 0; i < 4; i++)
    {
        WicPair vertex = target->p_vertices[i];
        vertex = wic_subtract_pairs(vertex, target->center);
        vertex = wic_multiply_pairs(vertex, target->scale);
        double x = vertex.x * cosine - vertex.y * sine;
        double y = vertex.x * sine + vertex.y * cosine;
        vertex.x = x;
        vertex.y = y;
        if(!target->draw_centered)
            vertex = wic_add_pairs(vertex, target->center);
        vertex = wic_convert_location(wic_add_pairs(vertex, target->location),
                                  game->p_dimensions);
        glVertex2d(vertex.x, vertex.y);
    }
    glEnd();
    return wic_report_error(0);
}
int wic_free_quad(WicQuad* target)
{
    if(target == 0)
        return wic_report_error(-107);
    free(target->p_vertices);
    target->p_vertices = 0;
    return wic_report_error(0);
}

