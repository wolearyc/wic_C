previous_glyph_index = glyph_index;
int error = wic_init_image(&result[i], (WicPair) {0,0},
                           font->textures[character]);
result[i].center.x = -x;
target[i].center.y = (font->face->glyph->metrics.horiBearingY -
                      font->face->glyph->metrics.height)/64;
result[i].draw_centered = true;
x += font->face->glyph->advance.x / 64;






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
static WicImage working_image;
bool wic_init_text(WicText* target, WicPair location, char* string,
                   size_t len_string, WicFont* font, WicColor color)
{
    if(target == 0)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(string == 0)
        return wic_throw_error(WIC_ERRNO_NULL_STRING);
    if(font == 0)
        return wic_throw_error(WIC_ERRNO_NULL_FONT);
    
    double x = 0, min_y = 0, max_y = 0;
    int previous_glyph_index = 0;
    bool do_kerning = FT_HAS_KERNING(font->face);
    for(size_t i = 0; i < len_string; i++)
    {
        char c = string[i];
        int glyph_index = FT_Get_Char_Index(face, c);
        FT_Load_Glyph(font->face, glyph_index, 0);
        if(do_kerning && previous_glyph_index != 0)
        {
            FT_Vector delta;
            FT_Get_Kerning(font->face, previous_glyph_index, glyph_index,
                           FT_KERNING_UNFITTED, &delta);
            x += delta.x;
        }
        x += font->face->glyph->advance.x / 64;
        if(-font->face->glyph->height + font->face->glyph->horiBearingY < min_y)
            min_y = -font->face->glyph->height+font->face->glyph->horiBearingY;
        if(font->face->glyph->horiBearingY > max_y)
            max_y = font->face->glyph->horiBearingY;
    }
    min_y /= 64;
    max_y /= 64;

    target->location = location;
    target->center = (WicPair) {0,0};
    target->rotation = 0.0;
    target->scale = (WicPair) {1,1};
    target->bounds = (WicBounds) {(WicPair) {0,min_y}, (WicPair) {x,max_y}};
    target->color = color;
    target->draw_centered = false;
    target->string = string;
    target->len_string = len_string;
    target->font = font;
    return true;
}
bool wic_set_text_string(WicText* target, char* string, size_t len_string,
                         WicGame* game)
{
    if(target == 0)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(string == 0)
        return wic_throw_error(WIC_ERRNO_NULL_STRING);
    if(game == 0)
        return wic_throw_error(WIC_ERRNO_NULL_GAME);
   
}
enum WicError wic_set_text_font(WicText* target, WicFont* font, WicGame* game)
{
    if(target == 0)
        return wic_throw_error(WICER_TARGET);
    if(font == 0)
        return wic_throw_error(WICER_FONT);
    if(game == 0)
        return wic_throw_error(WICER_GAME);
    WicImage* images = malloc(sizeof(WicImage) * target->num_chars_ro);
    if(images == 0)
        return wic_throw_error(WICER_HEAP);
    enum WicError result = wic_render_string(images, font, target->string_ro,
                                             target->num_chars_ro, game);
    if(result != WICER_NONE)
    {
        free(images);
        return wic_throw_error(result);
    }
    WicPair* offsets = malloc(sizeof(WicPair) * target->num_chars_ro);
    if(offsets == 0)
    {
        free(images);
        return wic_throw_error(WICER_HEAP);
    }
    for(int i = 0; i < target->num_chars_ro; i++)
    {
        offsets[i] = images[i].center;
    }
    int boundsX = -offsets[target->num_chars_ro-1].x +
                  images[target->num_chars_ro-1].texture_ro->dimensions_ro.x;
    int boundsY = images[target->num_chars_ro-1].texture_ro->dimensions_ro.y;
    WicBounds bounds = {(WicPair) {0,0}, (WicPair) {boundsX, boundsY}};
    WicPair geometric_center = wic_divide_pairs(bounds.upper_right,
                                                (WicPair) {2,2});
    target->font_ro = font;
    free(target->images_ro);
    target->images_ro = images;
    free(target->offsets_ro);
    target->offsets_ro = offsets;
    target->bounds_ro = bounds;
    target->geometric_center_ro = geometric_center;
    return wic_throw_error(WICER_NONE);

}
bool wic_draw_text(WicText* target, WicGame* game)
{
    if(target == 0)
        return wic_throw_error(WICER_TARGET);
    if(game == 0)
        return wic_throw_error(WICER_GAME);
    int num_chars = target->num_chars_ro;
    for(int i = 0; i < num_chars; i++)
    {
        if(target->draw_centered)
            target->images_ro[i].location = target->location;
        else
            target->images_ro[i].location = wic_add_pairs(target->location,
                                                         target->center);
        target->images_ro[i].color = target->color;
        target->images_ro[i].center = wic_add_pairs(target->center,
                                                   target->offsets_ro[i]);
        target->images_ro[i].scale = target->scale;
        target->images_ro[i].rotation = target->rotation;
        wic_draw_image(&(target->images_ro[i]), game);
    }
    return wic_throw_error(WICER_NONE);
}
bool wic_free_text(WicText* target)
{
    if(target == 0)
        return wic_throw_error(WICER_TARGET);
    free(target->images_ro);
    free(target->offsets_ro);
    
    target->location = (WicPair) {0,0};
    target->string_ro = 0;
    target->num_chars_ro = 0;
    target->font_ro = 0;
    target->images_ro = 0;
    target->offsets_ro = 0;
    target->bounds_ro = (WicBounds) {(WicPair) {0,0}, (WicPair) {0,0}};
    target->color = WIC_WHITE;
    target->center = (WicPair) {0,0};
    target->geometric_center_ro = (WicPair) {0,0};
    target->draw_centered = false;
    target->scale = (WicPair) {1,1};
    target->rotation = 0.0;
    return wic_throw_error(WICER_NONE);
}