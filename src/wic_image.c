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
enum WicError wic_init_image(WicImage* target, WicPair location,
                             WicTexture* texture)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    if(texture == 0)
        return wic_report_error(WICER_TEXTURE);
    WicBounds bounds = {(WicPair) {0,0}, texture->p_dimensions};
    WicPair* vertices = malloc(4 * sizeof(WicPair));
    if(vertices == 0)
        return wic_report_error(WICER_HEAP);
    vertices[0] = (WicPair) {0,0};
    vertices[1] = (WicPair) {bounds.upper_right.x - bounds.lower_left.x, 0};
    vertices[2] = wic_subtract_pairs(bounds.upper_right, bounds.lower_left);
    vertices[3] = (WicPair) {0, bounds.upper_right.y - bounds.lower_left.y};
    WicPair geometric_center = wic_subtract_pairs(bounds.upper_right,
                                                  bounds.lower_left);
    geometric_center = wic_divide_pairs(geometric_center, (WicPair) {2,2});
        
    target->location = location;
    target->p_texture = texture;
    target->p_bounds = bounds;
    target->p_vertices = vertices;
    target->color = WIC_WHITE;
    target->center = (WicPair) {0,0};
    target->p_geometric_center = geometric_center;
    target->draw_centered = false;
    target->scale = (WicPair) {1,1};
    target->rotation = 0.0;
    return wic_report_error(WICER_NONE);
}
enum WicError wic_set_image_texture(WicImage* target, WicTexture* texture)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    if(texture == 0)
        return wic_report_error(WICER_TEXTURE);
    WicBounds bounds = {(WicPair) {0,0}, texture->p_dimensions};
    WicPair* vertices = malloc(4 * sizeof(WicPair));
    if(vertices == 0)
        return wic_report_error(WICER_HEAP);
    vertices[0] = (WicPair) {0,0};
    vertices[1] = (WicPair) {bounds.upper_right.x - bounds.lower_left.x, 0};
    vertices[2] = wic_subtract_pairs(bounds.upper_right, bounds.lower_left);
    vertices[3] = (WicPair) {0, bounds.upper_right.y - bounds.lower_left.y};
    WicPair geometric_center = wic_subtract_pairs(bounds.upper_right,
                                                  bounds.lower_left);
    geometric_center = wic_divide_pairs(geometric_center, (WicPair) {2,2});
        
    target->p_texture = texture;
    target->p_bounds = bounds;
    free(target->p_vertices);
    target->p_vertices = vertices;
    target->p_geometric_center = geometric_center;
    return wic_report_error(WICER_NONE);
}
enum WicError wic_set_image_bounds(WicImage* target, WicBounds bounds)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    WicPair* vertices = malloc(4 * sizeof(WicPair));
    if(vertices == 0)
        return wic_report_error(WICER_HEAP);
    vertices[0] = (WicPair) {0,0};
    vertices[1] = (WicPair) {bounds.upper_right.x - bounds.lower_left.x, 0};
    vertices[2] = wic_subtract_pairs(bounds.upper_right, bounds.lower_left);
    vertices[3] = (WicPair) {0, bounds.upper_right.y - bounds.lower_left.y};
    WicPair geometric_center = wic_subtract_pairs(bounds.upper_right,
                                                  bounds.lower_left);
        
    target->p_bounds = bounds;
    free(target->p_vertices);
    target->p_vertices = vertices;
    target->p_geometric_center = geometric_center;
    return wic_report_error(WICER_NONE);
}
enum WicError wic_draw_image(WicImage* target, WicGame* game)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    if(game == 0)
        return wic_report_error(WICER_GAME);
    WicPair window_dimensions = game->p_dimensions;
    WicPair tex_dimensions = target->p_texture->p_dimensions;
    p_wic_select_texture(target->p_texture);
    p_wic_select_color(&(target->color));
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        
    /* lower left corner */
    WicPair vertex = target->p_vertices[0];
    vertex = wic_transform_pair(vertex, target->rotation, target->scale,
                                target->center);
    if(!target->draw_centered)
        vertex = wic_add_pairs(vertex, target->center);
    
    vertex = wic_convert_location(wic_add_pairs(vertex, target->location),
                                  window_dimensions);
    glTexCoord2f(target->p_bounds.lower_left.x / tex_dimensions.x,
                 target->p_bounds.lower_left.y / tex_dimensions.y);
    glVertex2d(vertex.x, vertex.y);
    /* lower right corner */
    vertex = target->p_vertices[1];
    vertex = wic_transform_pair(vertex, target->rotation, target->scale,
                                target->center);
    if(!target->draw_centered)
        vertex = wic_add_pairs(vertex, target->center);
    vertex = wic_convert_location(wic_add_pairs(vertex, target->location),
                              window_dimensions);
    glTexCoord2f(target->p_bounds.upper_right.x / tex_dimensions.x,
                 target->p_bounds.lower_left.y / tex_dimensions.y);
    glVertex2d(vertex.x, vertex.y);
    /* upper right corner */
    vertex = target->p_vertices[2];
    vertex = wic_transform_pair(vertex, target->rotation, target->scale,
                                target->center);
    if(!target->draw_centered)
        vertex = wic_add_pairs(vertex, target->center);
    vertex = wic_convert_location(wic_add_pairs(vertex, target->location),
                              window_dimensions);
    glTexCoord2f(target->p_bounds.upper_right.x / tex_dimensions.x,
                 target->p_bounds.upper_right.y / tex_dimensions.y);
    glVertex2d(vertex.x, vertex.y);
    /* upper left corner */
    vertex = target->p_vertices[3];
    vertex = wic_transform_pair(vertex, target->rotation, target->scale,
                                target->center);
    if(!target->draw_centered)
        vertex = wic_add_pairs(vertex, target->center);
    vertex = wic_convert_location(wic_add_pairs(vertex, target->location),
                                  window_dimensions);
    glTexCoord2f(target->p_bounds.lower_left.x / tex_dimensions.x,
                 target->p_bounds.upper_right.y / tex_dimensions.y);
    glVertex2d(vertex.x, vertex.y);
        
    glEnd();
    glDisable(GL_TEXTURE_2D);
    return wic_report_error(WICER_NONE);
}
enum WicError wic_free_image(WicImage* target)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    free(target->p_vertices);
    
    target->location = (WicPair) {0,0};
    target->p_texture = 0;
    target->p_bounds = (WicBounds) {(WicPair) {0,0}, (WicPair) {0,0}};
    target->p_vertices = 0;
    target->color = WIC_WHITE;
    target->center = (WicPair) {0,0};
    target->p_geometric_center = (WicPair) {0,0};
    target->draw_centered = false;
    target->scale = (WicPair) {1,1};
    target->rotation = 0.0;
    return wic_report_error(WICER_NONE);
}