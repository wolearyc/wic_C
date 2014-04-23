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
 * File:    wic_font.h
 * ----------------------------------------------------------------------------
 */
#ifndef WIC_FONT_H
#define WIC_FONT_H
#include "FreeType/ft2build.h"
#include FT_FREETYPE_H
#include FT_BITMAP_H
#include "wic_game.h"
#include "wic_texture.h"
#include "wic_image.h"
static const size_t WIC_FONT_NUM_TEXTURES;
/**
 */
typedef struct WicFont
{
    FT_Face p_face;
    WicTexture** p_textures;
    bool p_point;
    bool p_antialias;
    
} WicFont;
int wic_init_font(WicFont* target, const char* filepath, unsigned short point,
                  bool antialias, WicGame* game);
int wic_render_string(WicImage* result, WicFont* font, const char* string,
                      size_t num_characters, WicGame* game);
int wic_free_font(WicFont* target);

#endif
