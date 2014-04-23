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
int wic_init_font(WicFont* target, const char* filepath, unsigned short point,
                  bool antialias, WicGame* game)
{
    if(target == 0)
        return wic_report_error(-121);
    if(filepath == 0)
        return wic_report_error(-122);
    if(game == 0)
        return wic_report_error(-122);
    FT_Face face;
    int error = FT_New_Face(game->p_freetype_library, filepath, 0, &face);
    if(error != 0)
        return wic_report_error(-123);
    WicTexture** textures = malloc(WIC_FONT_NUM_TEXTURES * sizeof(WicTexture*));
    if(textures == 0)
    {
        FT_Done_Face(face);
        return wic_report_error(-124);
    }
    for(int i = 0; i < WIC_FONT_NUM_TEXTURES; i++)
        textures[i] = 0;
    if(point == 0)
        return wic_report_error(-125);
    target->p_face = face;
    target->p_textures = textures;
    target->p_point = point;
    target->p_antialias = antialias;
    return wic_report_error(0);
}
int wic_render_string(WicImage* result, WicFont* font, const char* string,
                      size_t num_characters, WicGame* game)
{
    if(result == 0)
        return wic_report_error(-127);
    if(font == 0)
        return wic_report_error(-128);
    if(string == 0)
        return wic_report_error(-129);
    if(game == 0)
        return wic_report_error(-130);
    int x = 0;
    int previous_glyph_index = 0;
    bool do_kerning = FT_HAS_KERNING(font->p_face);
    for(int i = 0; i < num_characters; i++)
    {
        char character = string[i];
        int glyph_index = FT_Get_Char_Index(font->p_face, character);
    
        
        
        font->p_textures[glyph_index] = malloc(sizeof(WicTexture));
        if(font->p_textures[glyph_index] == 0)
            return wic_report_error(-131);
        if(font->p_antialias)
            FT_Load_Glyph(font->p_face, glyph_index, FT_LOAD_FORCE_AUTOHINT);
        else
            FT_Load_Glyph(font->p_face, glyph_index, 0);
        if(font->p_textures[character] == 0)
        {
            if(font->p_antialias)
            {
                FT_Render_Glyph(font->p_face->glyph, FT_RENDER_MODE_NORMAL);
                WicPair dimensions = {font->p_face->glyph->bitmap.width,
                                      font->p_face->glyph->bitmap.rows};
                wic_init_texture_from_buffer(font->p_textures[glyph_index],
                                             font->p_face->glyph->bitmap.buffer,
                                             dimensions, WIC_GREYSCALE,
                                             WIC_NEAREST);
            }
            else
            {
                FT_Render_Glyph(font->p_face->glyph, FT_RENDER_MODE_MONO);
                FT_Bitmap target;
                FT_Bitmap_New(&target);
                int error = FT_Bitmap_Convert(game->p_freetype_library,
                                              &(font->p_face->glyph->bitmap),
                                              &target, 1);
                WicPair dimensions = {target.width, target.rows};
                wic_init_texture_from_buffer(font->p_textures[glyph_index],
                                             target.buffer, dimensions,
                                             WIC_MONO, WIC_NEAREST);
                FT_Bitmap_Done(game->p_freetype_library, &target);
            }
        }
        
        
        if(do_kerning && previous_glyph_index != 0)
        {
            FT_Vector delta;
            FT_Get_Kerning(font->p_face, previous_glyph_index, glyph_index,
                           FT_KERNING_UNFITTED, &delta);
            x += delta.x;
        }
        previous_glyph_index = glyph_index;
        WicImage image;
        WicPair location = {x, (font->p_face->glyph->metrics.horiBearingY -
                             font->p_face->glyph->metrics.height)/64};
        wic_init_image(&image, location, font->p_textures[character]);
        result[i] = image;
        x += font->p_face->glyph->advance.x / 64;
    }
    return wic_report_error(0);

}
int wic_free_font(WicFont* target)
{
    if(target == 0)
        return wic_report_error(-132);
    FT_Done_Face(target->p_face);
    target->p_face = 0;
    for(int i = 0; i < WIC_FONT_NUM_TEXTURES; i++)
    {
        if(target->p_textures[i] != 0)
        {
            wic_free_texture(target->p_textures[i]);
            free(target->p_textures[i]);
            target->p_textures[i] = 0;
        }
    }
    free(target->p_textures);
    target->p_textures = 0;
    return wic_report_error(0);
}