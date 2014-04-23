/* ----------------------------------------------------------------------------
 * wic - a simple 2D game engine for Mac OSX written in C
 * Copyright (C) 2013-2014  Will O'Leary
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.s
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------------------------
 * File:    wic_texture.h
 * ----------------------------------------------------------------------------
 */
#ifndef WIC_TEXTURE_H
#define WIC_TEXTURE_H
#include "stdlib.h"
#include "wic_pair.h"
#include "wic_error.h"
#include "SOIL/SOIL.h"
#include "OpenGL/gl.h"
/** \brief defines constants for texture filtering (behavior when images are
 *         scaled beyond or below their resolution)
 */
enum WicFilter
{
    WIC_NEAREST = GL_NEAREST, /**< nearest filtering (no filtering) */
    WIC_LINEAR = GL_LINEAR    /**< linear filtering */
};
/** \brief defines constants for buffer formats
 */
enum WicFormat
{
    WIC_MONO,      /**< each pixel has one 1 bit value (black or white) */
    WIC_GREYSCALE, /**< each pixel has one 8 bit value */
    WIC_RGB,       /**< each pixel has three 8 bit values, red, green, and 
                    *   blue 
                    */
   WIC_RGBA       /**< each pixel has four 8 bit values, red, green, blue, and
                   *   alpha
                   */
};
/** \brief a texture
 * 
 *  A WicTexture should be initialized via wic_init_texture_from_buffer or
 *  wic_init_texture_from_file. A WicTexture should eventually be deallocated
 *  via wic_free_texture.
 */
typedef struct WicTexture
{
    unsigned int p_data;
    WicPair p_dimensions;
} WicTexture;
/** \brief initializes a WicTexture from an existing buffer
 *  \param target the target WicTexture; must be valid
 *  \param buffer the buffer
 *  \param the dimensions; dimensions.x * dimensions.y not being equal to the
 *         number of elements in buffer will result in undefined behavior
 *  \param format the format of buffer; an incorrect format will result in a 
 *         warped texture and/or undefined behavior
 *  \param filter the desired texture filter (defines behavior when textures are
 *         scaled beyond or below their resolution
 *  \return 0 on success, < 0 on failure
 */
int wic_init_texture_from_buffer(WicTexture* target, unsigned char* buffer,
                                  WicPair dimensions, enum WicFormat format,
                                  enum WicFilter filter);
/** \brief initializes a WicTexture from a file
 *  \param target the target WicTexture; must be valid
 *  \param filepath the absolute of relative filepath to a non-1bpp and non-RLE 
 *         BMP, non-interlaced PNG, JPEG, TGA, DDS, PSD, or HDR image file; the
 *         file must exist and be one of the formentioned formats
 *  \param filter the desired texture filter (defines behavior when textures are
 *          scaled beyond or below their resolution
 *  \return 0 on success, < 0 on failure
 */
int wic_init_texture_from_file(WicTexture* target, const char* filepath,
                               enum WicFilter filter);
/** \brief deallocates a WicTexture
 *  \param target the target WicTexture; must be valid
 *  \return 0 on success, < 0 on failure
 */
int wic_free_texture(WicTexture* target);
void p_wic_select_texture(WicTexture* target);
#endif