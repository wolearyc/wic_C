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
 * File:    wic_text.c
 * ----------------------------------------------------------------------------
 */
#include "wic_text.h"
enum WicError wic_init_text(WicText* target, WicPair location, char* string,
                            size_t num_chars, WicFont* font, WicColor color,
                            WicGame* game)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    if(string == 0)
        return wic_report_error(WICER_STRING);
    if(font == 0)
        return wic_report_error(WICER_FONT);
    if(game == 0)
        return wic_report_error(WICER_GAME);
    WicImage* images = malloc(sizeof(WicImage) * num_chars);
    if(images == 0)
        return wic_report_error(WICER_HEAP);
    enum WicError result = wic_render_string(images, font, string, num_chars,
                                             game);
    if(result != WICER_NONE)
    {
        free(images);
        return wic_report_error(result);
    }
    WicPair* offsets = malloc(sizeof(WicPair) * num_chars);
    if(offsets == 0)
    {
        free(images);
        return wic_report_error(WICER_HEAP);
    }
    for(int i = 0; i < num_chars; i++)
    {
        offsets[i] = images[i].center;
    }
    int boundsX = -offsets[num_chars-1].x +
                  images[num_chars-1].p_texture->p_dimensions.x;
    int boundsY = images[num_chars-1].p_texture->p_dimensions.y;
    WicBounds bounds = {(WicPair) {0,0}, (WicPair) {boundsX, boundsY}};
    WicPair geometric_center = wic_divide_pairs(bounds.upper_right,
                                                (WicPair) {2,2});
    
    target->location = location;
    target->p_string = string;
    target->p_num_chars = num_chars;
    target->p_font = font;
    target->p_images = images;
    target->p_offsets = offsets;
    target->p_bounds = bounds;
    target->color = color;
    target->center = (WicPair) {0,0};
    target->p_geometric_center = geometric_center;
    target->draw_centered = false;
    target->scale = (WicPair) {1,1};
    target->rotation = 0.0;
    return wic_report_error(WICER_NONE);
}
enum WicError wic_set_text_string(WicText* target, char* string,
                                  size_t num_chars, WicGame* game)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    if(string == 0)
        return wic_report_error(WICER_STRING);
    if(game == 0)
        return wic_report_error(WICER_GAME);
    WicImage* images = malloc(sizeof(WicImage) * num_chars);
    if(images == 0)
        return wic_report_error(WICER_HEAP);
    enum WicError result = wic_render_string(images, target->p_font, string,
                                             num_chars, game);
    if(result != WICER_NONE)
    {
        free(images);
        return wic_report_error(result);
    }
    WicPair* offsets = malloc(sizeof(WicPair) * num_chars);
    if(offsets == 0)
    {
        free(images);
        return wic_report_error(WICER_HEAP);
    }
    for(int i = 0; i < num_chars; i++)
    {
        offsets[i] = images[i].center;
    }
    int boundsX = -offsets[num_chars-1].x +
                  images[num_chars-1].p_texture->p_dimensions.x;
    int boundsY = images[num_chars-1].p_texture->p_dimensions.y;
    WicBounds bounds = {(WicPair) {0,0}, (WicPair) {boundsX, boundsY}};
    WicPair geometric_center = wic_divide_pairs(bounds.upper_right,
                                                (WicPair) {2,2});
    
    target->p_string = string;
    target->p_num_chars = num_chars;
    free(target->p_images);
    target->p_images = images;
    free(target->p_offsets);
    target->p_offsets = offsets;
    target->p_bounds = bounds;
    target->p_geometric_center = geometric_center;
    return wic_report_error(WICER_NONE);
}
enum WicError wic_set_text_font(WicText* target, WicFont* font, WicGame* game)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    if(font == 0)
        return wic_report_error(WICER_FONT);
    if(game == 0)
        return wic_report_error(WICER_GAME);
    WicImage* images = malloc(sizeof(WicImage) * target->p_num_chars);
    if(images == 0)
        return wic_report_error(WICER_HEAP);
    enum WicError result = wic_render_string(images, font, target->p_string,
                                             target->p_num_chars, game);
    if(result != WICER_NONE)
    {
        free(images);
        return wic_report_error(result);
    }
    WicPair* offsets = malloc(sizeof(WicPair) * target->p_num_chars);
    if(offsets == 0)
    {
        free(images);
        return wic_report_error(WICER_HEAP);
    }
    for(int i = 0; i < target->p_num_chars; i++)
    {
        offsets[i] = images[i].center;
    }
    int boundsX = -offsets[target->p_num_chars-1].x +
                  images[target->p_num_chars-1].p_texture->p_dimensions.x;
    int boundsY = images[target->p_num_chars-1].p_texture->p_dimensions.y;
    WicBounds bounds = {(WicPair) {0,0}, (WicPair) {boundsX, boundsY}};
    WicPair geometric_center = wic_divide_pairs(bounds.upper_right,
                                                (WicPair) {2,2});
    target->p_font = font;
    free(target->p_images);
    target->p_images = images;
    free(target->p_offsets);
    target->p_offsets = offsets;
    target->p_bounds = bounds;
    target->p_geometric_center = geometric_center;
    return wic_report_error(WICER_NONE);

}
enum WicError wic_draw_text(WicText* target, WicGame* game)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    if(game == 0)
        return wic_report_error(WICER_GAME);
    int num_chars = target->p_num_chars;
    for(int i = 0; i < num_chars; i++)
    {
        if(target->draw_centered)
            target->p_images[i].location = target->location;
        else
            target->p_images[i].location = wic_add_pairs(target->location,
                                                         target->center);
        target->p_images[i].color = target->color;
        target->p_images[i].center = wic_add_pairs(target->center,
                                                   target->p_offsets[i]);
        target->p_images[i].scale = target->scale;
        target->p_images[i].rotation = target->rotation;
        wic_draw_image(&(target->p_images[i]), game);
    }
    return wic_report_error(WICER_NONE);
}
enum WicError wic_free_text(WicText* target)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    free(target->p_images);
    free(target->p_offsets);
    
    target->location = (WicPair) {0,0};
    target->p_string = 0;
    target->p_num_chars = 0;
    target->p_font = 0;
    target->p_images = 0;
    target->p_offsets = 0;
    target->p_bounds = (WicBounds) {(WicPair) {0,0}, (WicPair) {0,0}};
    target->color = WIC_WHITE;
    target->center = (WicPair) {0,0};
    target->p_geometric_center = (WicPair) {0,0};
    target->draw_centered = false;
    target->scale = (WicPair) {1,1};
    target->rotation = 0.0;
    return wic_report_error(WICER_NONE);
}