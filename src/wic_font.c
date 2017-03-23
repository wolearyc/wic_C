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
 * File:    wic_font.c
 * ----------------------------------------------------------------------------
 */
#include "wic_font.h"
static const unsigned char WIC_FONT_NUM_CHARS = 128;
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
WicFont* wic_init_font(const char* filepath, unsigned point, bool antialias,
                       WicGame* game)
{
    if(!filepath)
        return (void*) wic_throw_error(WIC_ERRNO_NULL_FILEPATH);
    if(!game)
        return (void*) wic_throw_error(WIC_ERRNO_NULL_GAME);
    if(!point)
        return (void*) wic_throw_error(WIC_ERRNO_SMALL_POINT);
    FT_Face face;
    int error = FT_New_Face(game->freetype_library, filepath, 0, &face);
    if(error != 0)
        return (void*) wic_throw_error(WIC_ERRNO_LOAD_FILE_FAIL);
    WicTexture** textures = malloc(WIC_FONT_NUM_CHARS * sizeof(WicTexture*));
    bzero(textures, WIC_FONT_NUM_CHARS * sizeof(WicTexture*));
    if(!textures)
    {
        FT_Done_Face(face);
        return (void*) wic_throw_error(WIC_ERRNO_NO_HEAP);
    }
    FT_Set_Char_Size(face, 0, point*64, game->pixel_density.x,
                     game->pixel_density.y);
    for(unsigned char c = 0; c < WIC_FONT_NUM_CHARS; c++)
    {
        int glyph_index = FT_Get_Char_Index(face, c);
        if(antialias)
            FT_Load_Glyph(face, glyph_index, FT_LOAD_FORCE_AUTOHINT);
        else
            FT_Load_Glyph(face, glyph_index, 0);
        if(antialias)
        {
            if(!FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL) &&
               face->glyph->bitmap.buffer != 0)
            {
                WicPair dimensions = {face->glyph->bitmap.width,
                                      face->glyph->bitmap.rows};
                textures[c] =
                wic_init_texture_from_buffer(face->glyph->bitmap.buffer,
                                             dimensions, WIC_GREYSCALE,
                                             WIC_NEAREST, WIC_STOP);
                if(!textures[c])
                {
                    c--;
                    for(; c >= 0; c--)
                        wic_free_texture(textures[c]);
                    free(textures);
                    FT_Done_Face(face);
                    return (void*) wic_throw_error(wic_errno);
                }
            }
        }
        else
        {
            if(!FT_Render_Glyph(face->glyph, FT_RENDER_MODE_MONO) &&
               face->glyph->bitmap.buffer != 0)
            {
                FT_Bitmap target;
                FT_Bitmap_New(&target);
                int error = FT_Bitmap_Convert(game->freetype_library,
                                              &face->glyph->bitmap,
                                              &target, 1);
                WicPair dimensions = {target.width, target.rows};
                textures[c] = wic_init_texture_from_buffer(target.buffer,
                                                           dimensions, WIC_MONO,
                                                           WIC_NEAREST,
                                                           WIC_STOP);
                FT_Bitmap_Done(game->freetype_library, &target);
                if(!textures[c])
                {
                    c--;
                    for(; c >= 0; c--)
                        wic_free_texture(textures[c]);
                    FT_Done_Face(face);
                    return (void*) wic_throw_error(wic_errno);
                }
            }
        }
    }
    
    WicFont* result = malloc(sizeof(WicFont));
    if(!result)
    {
        for(char c = 0; c < WIC_FONT_NUM_CHARS; c++)
            wic_free_texture(textures[c]);
        free(textures);
        FT_Done_Face(face);
        wic_throw_error(WIC_ERRNO_NO_HEAP);
    }
    result->face = face;
    result->textures = textures;
    result->point = point;
    result->antialias = antialias;
    return result;
}
bool wic_free_font(WicFont* target)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    FT_Done_Face(target->face);
    target->face = 0;
    for(unsigned char c = 0; c < WIC_FONT_NUM_CHARS; c++)
    {
        if(target->textures[c] != 0)
            wic_free_texture(target->textures[c]);
        target->textures[c] = 0;
    }
    free(target->textures);
    target->textures = 0;
    target->point = 0;
    target->antialias = false;
    return true;
}
