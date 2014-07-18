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
 * File:    wic_font.c
 * ----------------------------------------------------------------------------
 */
#include "wic_font.h"
static const size_t WIC_FONT_NUM_TEXTURES = 360;
enum WicError wic_init_font(WicFont* target, const char* filepath,
                            unsigned short point, bool antialias, WicGame* game)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    if(filepath == 0)
        return wic_report_error(WICER_FILEPATH);
    if(game == 0)
        return wic_report_error(WICER_GAME);
    if(point == 0)
        return wic_report_error(WICER_POINT);
    FT_Face face;
    int error = FT_New_Face(game->freetype_library_ro, filepath, 0, &face);
    if(error != 0)
        return wic_report_error(WICER_FILE);
    WicTexture** textures = malloc(WIC_FONT_NUM_TEXTURES * sizeof(WicTexture*));
    if(textures == 0)
    {
        FT_Done_Face(face);
        return wic_report_error(WICER_HEAP);
    }
    for(int i = 0; i < WIC_FONT_NUM_TEXTURES; i++)
        textures[i] = 0;
    FT_Set_Char_Size(face, 0, point*64, game->device_resolution_ro.x,
                     game->device_resolution_ro.y);
    
    target->face_ro = face;
    target->textures_ro = textures;
    target->point_ro = point;
    target->antialias_ro = antialias;
    return wic_report_error(WICER_NONE);
}
enum WicError wic_render_string(WicImage* target, WicFont* font,
                                const char* string, size_t num_characters,
                                WicGame* game)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    if(font == 0)
        return wic_report_error(WICER_FONT);
    if(string == 0)
        return wic_report_error(WICER_STRING);
    if(game == 0)
        return wic_report_error(WICER_GAME);
    int x = 0;
    int previous_glyph_index = 0;
    bool do_kerning = FT_HAS_KERNING(font->face_ro);
    for(int i = 0; i < num_characters; i++)
    {
        char character = string[i];
        int glyph_index = FT_Get_Char_Index(font->face_ro, character);
        
        if(font->antialias_ro)
            FT_Load_Glyph(font->face_ro, glyph_index, FT_LOAD_FORCE_AUTOHINT);
        else
            FT_Load_Glyph(font->face_ro, glyph_index, 0);
        if(font->textures_ro[character] == 0)
        {
            font->textures_ro[character] = malloc(sizeof(WicTexture));
            if(font->textures_ro[character] == 0)
                return wic_report_error(WICER_HEAP);
            if(font->antialias_ro)
            {
                FT_Render_Glyph(font->face_ro->glyph, FT_RENDER_MODE_NORMAL);
                WicPair dimensions = {font->face_ro->glyph->bitmap.width,
                                      font->face_ro->glyph->bitmap.rows};
                
                wic_init_texture_from_buffer(font->textures_ro[character],
                                             font->face_ro->glyph->bitmap.buffer,
                                             dimensions, WIC_GREYSCALE,
                                             WIC_NEAREST, WIC_STOP);
            }
            else
            {
                FT_Render_Glyph(font->face_ro->glyph, FT_RENDER_MODE_MONO);
                FT_Bitmap target;
                FT_Bitmap_New(&target);
                int error = FT_Bitmap_Convert(game->freetype_library_ro,
                                              &(font->face_ro->glyph->bitmap),
                                              &target, 1);
                WicPair dimensions = {target.width, target.rows};
                wic_init_texture_from_buffer(font->textures_ro[character],
                                             target.buffer, dimensions,
                                             WIC_MONO, WIC_NEAREST, WIC_STOP);
                FT_Bitmap_Done(game->freetype_library_ro, &target);
            }
        }
        
        
        if(do_kerning && previous_glyph_index != 0)
        {
            FT_Vector delta;
            FT_Get_Kerning(font->face_ro, previous_glyph_index, glyph_index,
                           FT_KERNING_UNFITTED, &delta);
            x += delta.x;
        }
        previous_glyph_index = glyph_index;
        int error = wic_init_image(&target[i], (WicPair) {0,0},
                                   font->textures_ro[character]);
        target[i].center.x = -x;
        target[i].center.y = (font->face_ro->glyph->metrics.horiBearingY -
                             font->face_ro->glyph->metrics.height)/64;
        target[i].draw_centered = true;
        x += font->face_ro->glyph->advance.x / 64;
    }
    return wic_report_error(WICER_NONE);
}
enum WicError wic_free_font(WicFont* target)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    FT_Done_Face(target->face_ro);
    target->face_ro = 0;
    for(int i = 0; i < WIC_FONT_NUM_TEXTURES; i++)
    {
        if(target->textures_ro[i] != 0)
        {
            wic_free_texture(target->textures_ro[i]);
            free(target->textures_ro[i]);
            target->textures_ro[i] = 0;
        }
    }
    free(target->textures_ro);
    
    target->face_ro = 0;
    target->textures_ro = 0;
    target->point_ro = 0;
    target->antialias_ro = false;
    return wic_report_error(WICER_NONE);
}