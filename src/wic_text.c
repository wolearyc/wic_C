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
struct WicTexture
{
    unsigned int data;
    WicPair dimensions;
};
struct WicFont
{
    FT_Face face;           /**< the face */
    WicTexture** textures;   /**< the glyph textures */
    unsigned short point;   /**< the point size measured in font points */
    bool antialias;         /**< whether or not to antialias the font */
};
static WicImage working_image;
/* populates offsets and images and return the bounds */
WicBounds wic_text_get_data(WicPair* offsets, WicImage* images,
                            WicPair location, char* string, size_t len_string,
                            WicFont* font)
{
    double x = 0, min_y = 0, max_y = 0;
    int previous_glyph_index = 0;
    bool do_kerning = FT_HAS_KERNING(font->face);
    for(size_t i = 0; i < len_string; i++)
    {
        char c = string[i];
        int glyph_index = FT_Get_Char_Index(font->face, c);
        FT_Load_Glyph(font->face, glyph_index, 0);
        if(do_kerning && previous_glyph_index != 0)
        {
            FT_Vector delta;
            FT_Get_Kerning(font->face, previous_glyph_index, glyph_index,
                           FT_KERNING_UNFITTED, &delta);
            x += delta.x;
        }
        offsets[i] = (WicPair) {-x, - (font->face->glyph->metrics.horiBearingY -
                                   font->face->glyph->metrics.height) / 64};
        x += font->face->glyph->advance.x / 64;
        if(-font->face->glyph->metrics.height +
           font->face->glyph->metrics.horiBearingY < min_y)
            min_y = -font->face->glyph->metrics.height +
            font->face->glyph->metrics.horiBearingY;
        if(font->face->glyph->metrics.horiBearingY > max_y)
            max_y = font->face->glyph->metrics.horiBearingY;
    }
    for(size_t i = 0; i < len_string; i++)
    {
        char c = string[i];
        if(c == ' ')
            images[i].texture = 0;
        else
        {
            wic_init_image(&images[i], location, font->textures[c]);
            images[i].draw_centered = true;
        }
    }
    return (WicBounds) {(WicPair) {0, min_y / 64}, (WicPair) {x, max_y / 64}};
}
bool wic_init_text(WicText* target, WicPair location, char* string,
                   size_t len_string, WicFont* font, WicColor color)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!string)
        return wic_throw_error(WIC_ERRNO_NULL_STRING);
    if(!font)
        return wic_throw_error(WIC_ERRNO_NULL_FONT);
    
    WicPair* offsets = malloc(sizeof(WicPair) * len_string);
    if(!offsets)
        return wic_throw_error(WIC_ERRNO_NO_HEAP);
    WicImage* images = malloc(sizeof(WicImage) * len_string);
    if(!images)
    {
        free(offsets);
        return wic_throw_error(WIC_ERRNO_NO_HEAP);
    }
    WicBounds bounds = wic_text_get_data(offsets, images, location, string,
                                         len_string, font);
    
    target->location = location;
    target->center = (WicPair) {0,0};
    target->rotation = 0.0;
    target->scale = (WicPair) {1,1};
    target->bounds = bounds;
    target->color = color;
    target->draw_centered = false;
    target->string = string;
    target->len_string = len_string;
    target->offsets = offsets;
    target->images = images;
    target->font = font;
    return true;
}
bool wic_text_set_string(WicText* target, char* string, size_t len_string)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!string)
        return wic_throw_error(WIC_ERRNO_NULL_STRING);
    
    WicPair* offsets = malloc(sizeof(WicPair) * len_string);
    if(!offsets)
        return wic_throw_error(WIC_ERRNO_NO_HEAP);
    WicImage* images = malloc(sizeof(WicImage) * len_string);
    if(!images)
    {
        free(offsets);
        return wic_throw_error(WIC_ERRNO_NO_HEAP);
    }
    WicBounds bounds = wic_text_get_data(offsets, images, target->location,
                                         string, len_string, target->font);
    free(target->offsets);
    free(target->images);
    target->string = string;
    target->len_string = len_string;
    target->bounds = bounds;
    target->offsets = offsets;
    target->images = images;
    return true;
}
bool wic_draw_text(WicText* target, WicGame* game)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!game)
        return wic_throw_error(WIC_ERRNO_NULL_GAME);
    for(unsigned i = 0; i < target->len_string; i++)
    {
        if(target->images[i].texture != 0)
        {
            double height = target->images[i].texture->dimensions.y;
            WicBounds bounds;
            bounds.lower_left = wic_add_pairs(target->bounds.lower_left,
                                              target->offsets[i]);
            bounds.upper_right = wic_add_pairs(target->bounds.upper_right,
                                               target->offsets[i]); 
            target->images[i].bounds = bounds;
            
            WicPair location = target->location;
            if(target->draw_centered)
                location = wic_subtract_pairs(location, target->center);
            target->images[i].location = location;
            
            target->images[i].rotation = target->rotation;
            target->images[i].scale = target->scale;
            target->images[i].center.x = target->center.x;
            target->images[i].center.y = target->center.y;
            wic_draw_image(&target->images[i], game);
        }
    }
    return true;
}
bool wic_free_text(WicText* target)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    free(target->offsets);
    free(target->images);
    
    target->location = (WicPair) {0,0};
    target->center = (WicPair) {0,0};
    target->rotation = 0.0;
    target->scale = (WicPair) {1,1};
    target->bounds = (WicBounds) {(WicPair) {0,0}, (WicPair) {0,0}};
    target->color = WIC_WHITE;
    target->draw_centered = false;
    target->string = 0;
    target->len_string = 0;
    target->offsets = 0;
    target->images = 0;
    target->font = 0;
    return true;
}