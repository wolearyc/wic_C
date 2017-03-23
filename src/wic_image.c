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
 * File:    wic_image.c
 * ----------------------------------------------------------------------------
 */
#include "wic_image.h"
struct WicTexture
{
    unsigned int data;
    WicPair dimensions;
};
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
bool wic_init_image(WicImage* target, WicPair location, WicTexture* texture)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!texture)
        return wic_throw_error(WIC_ERRNO_NULL_TEXTURE);
    
    target->location = location;
    target->center = (WicPair) {0,0};
    target->rotation = 0.0;
    target->scale = (WicPair) {1,1};
    target->bounds = (WicBounds) {(WicPair) {0.0}, texture->dimensions};
    target->color = WIC_WHITE;
    target->draw_centered = false;
    target->texture = texture;
    return true;
}
WicPair wic_image_get_geo_center(WicImage* target)
{
    if(!target)
    {
        wic_throw_error(WIC_ERRNO_NULL_TARGET);
        return (WicPair) {-1,-1};
    }
    WicPair diagonal = wic_subtract_pairs(target->bounds.upper_right,
                                          target->bounds.lower_left);
    return wic_divide_pairs(diagonal, (WicPair) {2,2});
}
bool wic_draw_image(WicImage* target, WicGame* game)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!game)
        return wic_throw_error(WIC_ERRNO_NULL_GAME);
    WicPair window_dimensions = game->dimensions;
    WicPair tex_dimensions = target->texture->dimensions;
    glBindTexture(GL_TEXTURE_2D, target->texture->data);
    glColor4ub(target->color.red, target->color.green, target->color.blue,
               target->color.alpha);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        
    /* lower left corner */
    WicPair vertex = {0,0};
    vertex = wic_transform_pair(vertex, target->rotation, target->scale,
                                target->center);
    if(!target->draw_centered)
        vertex = wic_add_pairs(vertex, target->center);
    
    vertex = wic_convert_location(wic_add_pairs(vertex, target->location),
                                  window_dimensions);
    glTexCoord2f(target->bounds.lower_left.x / tex_dimensions.x,
                 target->bounds.lower_left.y / tex_dimensions.y);
    glVertex2d(vertex.x, vertex.y);
    /* lower right corner */
    vertex = (WicPair) {target->bounds.upper_right.x -
                        target->bounds.lower_left.x, 0};

    vertex = wic_transform_pair(vertex, target->rotation, target->scale,
                                target->center);
    if(!target->draw_centered)
        vertex = wic_add_pairs(vertex, target->center);
    vertex = wic_convert_location(wic_add_pairs(vertex, target->location),
                              window_dimensions);
    glTexCoord2f(target->bounds.upper_right.x / tex_dimensions.x,
                 target->bounds.lower_left.y / tex_dimensions.y);
    glVertex2d(vertex.x, vertex.y);
    /* upper right corner */
    vertex = wic_subtract_pairs(target->bounds.upper_right,
                                target->bounds.lower_left);
    vertex = wic_transform_pair(vertex, target->rotation, target->scale,
                                target->center);
    if(!target->draw_centered)
        vertex = wic_add_pairs(vertex, target->center);
    vertex = wic_convert_location(wic_add_pairs(vertex, target->location),
                              window_dimensions);
    glTexCoord2f(target->bounds.upper_right.x / tex_dimensions.x,
                 target->bounds.upper_right.y / tex_dimensions.y);
    glVertex2d(vertex.x, vertex.y);
    /* upper left corner */
    vertex = (WicPair) {0, target->bounds.upper_right.y -
                           target->bounds.lower_left.y};
    vertex = wic_transform_pair(vertex, target->rotation, target->scale,
                                target->center);
    if(!target->draw_centered)
        vertex = wic_add_pairs(vertex, target->center);
    vertex = wic_convert_location(wic_add_pairs(vertex, target->location),
                                  window_dimensions);
    glTexCoord2f(target->bounds.lower_left.x / tex_dimensions.x,
                 target->bounds.upper_right.y / tex_dimensions.y);
    glVertex2d(vertex.x, vertex.y);
        
    glEnd();
    glDisable(GL_TEXTURE_2D);
        return true;
}
