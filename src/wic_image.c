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
 * File:    wic_image.c
 * ----------------------------------------------------------------------------
 */
#include "wic_image.h"
int wic_init_image(WicImage* target, WicPair location, WicTexture* texture)
{
    if(target == 0)
        return wic_report_error(-81);
    if(texture == 0)
        return wic_report_error(-82);
    WicPair* new_vertices = malloc(4 * sizeof(WicPair));
    if(new_vertices == 0)
        return wic_report_error(-83);
    target->p_vertices = new_vertices;
    target->location = location;
    target->p_texture = texture;
    WicBounds bounds = {(WicPair) {0,0}, texture->p_dimensions};
    target->p_bounds = bounds;
    target->p_vertices[0] = (WicPair) {0,0};
    target->p_vertices[1] = (WicPair) {bounds.upper_right.x - bounds.lower_left.x,
                                  0};
    target->p_vertices[2] = wic_subtract_pairs(bounds.upper_right,
                                           bounds.lower_left);
    target->p_vertices[3] = (WicPair) {0, bounds.upper_right.y -
                                  bounds.lower_left.y};
    target->color = WIC_WHITE;
    target->center = (WicPair) {0,0};
    target->p_geometric_center = wic_divide_pairs(texture->p_dimensions,
                                              (WicPair) {2,2});
    target->draw_centered = false;
    target->scale = (WicPair) {1,1};
    target->rotation = 0.0;
    return wic_report_error(0);
}
int wic_set_image_texture(WicImage* target, WicTexture* texture)
{
    if(target == 0)
        return wic_report_error(-84);
    if(texture == 0)
        return wic_report_error(-85);
    WicPair* new_vertices = realloc(target->p_vertices, 4 * sizeof(WicPair));
    if(new_vertices == 0)
        return wic_report_error(-86);
    target->p_vertices = new_vertices;
    target->p_texture = texture;
    WicBounds bounds = {(WicPair) {0,0}, texture->p_dimensions};
    target->p_bounds = bounds;
    target->p_vertices[0] = (WicPair) {0,0};
    target->p_vertices[1] = (WicPair) {bounds.upper_right.x -
                                    bounds.lower_left.x, 0};
    target->p_vertices[2] = wic_subtract_pairs(bounds.upper_right,
                                           bounds.lower_left);
    target->p_vertices[3] = (WicPair) {0, bounds.upper_right.y -
                                  bounds.lower_left.y};
    target->p_geometric_center = wic_divide_pairs(texture->p_dimensions,
                                              (WicPair) {2,2});
    return wic_report_error(0);
}
int wic_set_image_bounds(WicImage* target, WicBounds bounds)
{
    if(target == 0)
        return wic_report_error(-87);
    if(bounds.lower_left.x < 0 || bounds.lower_left.y < 0 ||
       bounds.upper_right.x > target->p_texture->p_dimensions.x ||
       bounds.upper_right.y > target->p_texture->p_dimensions.x)
        return wic_report_error(-88);
    WicPair* new_vertices = realloc(target->p_vertices, 4 * sizeof(WicPair));
    if(new_vertices == 0)
        return wic_report_error(-89);
    target->p_vertices = new_vertices;
    target->p_vertices[0] = (WicPair) {0,0};
    target->p_vertices[1] = (WicPair) {bounds.upper_right.x -
                                    bounds.lower_left.x, 0};
    target->p_vertices[2] = wic_subtract_pairs(bounds.upper_right,
                                           bounds.lower_left);
    target->p_vertices[3] = (WicPair) {0, bounds.upper_right.y -
                                  bounds.lower_left.y};
    target->p_bounds = bounds;
    return wic_report_error(0);
}
int wic_draw_image(WicImage* target, WicGame* game)
{
    if(target == 0)
        return wic_report_error(-90);
    if(game == 0)
        return wic_report_error(-91);
    double cosine = cos(target->rotation);
    double sine = sin(target->rotation);
    WicPair window_dimensions = game->p_dimensions;
    WicPair tex_dimensions = target->p_texture->p_dimensions;
    p_wic_select_texture(target->p_texture);
    wic_select_color(&(target->color));
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    WicPair vertex = target->p_vertices[0];
    vertex = wic_subtract_pairs(vertex, target->center);
    vertex = wic_multiply_pairs(vertex, target->scale);
    double x = vertex.x * cosine - vertex.y * sine;
    double y = vertex.x * sine + vertex.y * cosine;
    vertex.x = x;
    vertex.y = y;
    if(!target->draw_centered)
        vertex = wic_add_pairs(vertex, target->center);
    vertex = wic_convert_location(wic_add_pairs(vertex, target->location),
                              window_dimensions);
    glTexCoord2f((target->p_bounds.lower_left.x + 1) / tex_dimensions.x,
                 -(target->p_bounds.lower_left.y + 1) / tex_dimensions.y);
    glVertex2d(vertex.x, vertex.y);
    vertex = target->p_vertices[1];
    vertex = wic_subtract_pairs(vertex, target->center);
    vertex = wic_multiply_pairs(vertex, target->scale);
    x = vertex.x * cosine - vertex.y * sine;
    y = vertex.x * sine + vertex.y * cosine;
    vertex.x = x;
    vertex.y = y;
    if(!target->draw_centered)
        vertex = wic_add_pairs(vertex, target->center);
    vertex = wic_convert_location(wic_add_pairs(vertex, target->location),
                              window_dimensions);
    glTexCoord2f((target->p_bounds.upper_right.x - 1) / tex_dimensions.x,
                 -(target->p_bounds.lower_left.y + 1) / tex_dimensions.y);
    glVertex2d(vertex.x, vertex.y);
    vertex = target->p_vertices[2];
    vertex = wic_subtract_pairs(vertex, target->center);
    vertex = wic_multiply_pairs(vertex, target->scale);
    x = vertex.x * cosine - vertex.y * sine;
    y = vertex.x * sine + vertex.y * cosine;
    vertex.x = x;
    vertex.y = y;
    if(!target->draw_centered)
        vertex = wic_add_pairs(vertex, target->center);
    vertex = wic_convert_location(wic_add_pairs(vertex, target->location),
                              window_dimensions);
    glTexCoord2f((target->p_bounds.upper_right.x - 1) / tex_dimensions.x,
                 -(target->p_bounds.upper_right.y - 1) / tex_dimensions.y);
    glVertex2d(vertex.x, vertex.y);
    vertex = target->p_vertices[3];
    vertex = wic_subtract_pairs(vertex, target->center);
    vertex = wic_multiply_pairs(vertex, target->scale);
    x = vertex.x * cosine - vertex.y * sine;
    y = vertex.x * sine + vertex.y * cosine;
    vertex.x = x;
    vertex.y = y;
    if(!target->draw_centered)
        vertex = wic_add_pairs(vertex, target->center);
    vertex = wic_convert_location(wic_add_pairs(vertex, target->location),
                              window_dimensions);
    glTexCoord2f((target->p_bounds.lower_left.x + 1) / tex_dimensions.x,
                 -(target->p_bounds.upper_right.y - 1) / tex_dimensions.y);
    glVertex2d(vertex.x, vertex.y);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    return wic_report_error(0);
}
int wic_free_image(WicImage* target)
{
    if(target == 0)
        return wic_report_error(-92);
    free(target->p_vertices);
    target->p_vertices = 0;
    return wic_report_error(0);
}