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
 * File:    wic_texture.c
 * ----------------------------------------------------------------------------
 */
#include "wic_texture.h"
int wic_init_texture_from_buffer(WicTexture* target, unsigned char* buffer,
                             WicPair dimensions, enum WicFormat format,
                             enum WicFilter filter)
{
    if(target == 0)
        return wic_report_error(-61);
    if(buffer == 0)
        return wic_report_error(-62);
    if(dimensions.x < 1)
        return wic_report_error(-63);
    if(dimensions.y < 1)
        return wic_report_error(-64);
    int x_dimension = (int) (dimensions.x + 2) * 4;
    int y_dimension = (int) dimensions.y + 2;
    unsigned char** temp = malloc(x_dimension * sizeof(unsigned char*));
    if(temp == 0)
        return wic_report_error(-65);
    for(int x = 0; x < x_dimension; x++)
    {
        temp[x] = malloc(y_dimension * sizeof(unsigned char));
        if(temp[x] == 0)
        {
            for(int i = x-1; i < 0; i--)
                free(temp[i]);
            free(temp);
            return wic_report_error(-66);
        }
    }
    for(int y = 0; y < y_dimension; y++)
    {
        for(int x = 0; x < x_dimension; x+=4)
        {
            temp[x][y] = 255;
            temp[x+1][y] = 255;
            temp[x+2][y] = 255;
            temp[x+3][y] = 0;
        }
    }
    int buffer_index = 0;
    for(int y = 1; y < y_dimension - 1; y++)
    {
        for(int x = 4; x < x_dimension - 4; x+=4)
        {
            if(format == WIC_MONO)
            {
                unsigned char character = buffer[buffer_index];
                if(character == 0)
                    temp[x+3][y] = 0;
                else
                    temp[x+3][y] = 255;
                buffer_index++;
            }
            else if(format == WIC_GREYSCALE)
            {
                temp[x+3][y] = buffer[buffer_index];
                buffer_index++;
            }
            else if(format == WIC_RGB)
            {
                temp[x][y] = buffer[buffer_index];
                temp[x+1][y] = buffer[buffer_index+1];
                temp[x+2][y] = buffer[buffer_index+2];
                temp[x+3][y] = 255;
                buffer_index += 3;
            }
            else if(format == WIC_RGBA)
            {
                temp[x][y] = buffer[buffer_index];
                temp[x+1][y] = buffer[buffer_index+1];
                temp[x+2][y] = buffer[buffer_index+2];
                temp[x+3][y] = buffer[buffer_index+3];
                buffer_index += 4;
            }
        }
    }
    unsigned char* formatted_buffer = malloc(x_dimension * y_dimension *
                                             sizeof(unsigned char));
    if(formatted_buffer == 0)
    {
        for(int x = 0; x < x_dimension; x++)
            free(temp[x]);
        free(temp);
        return wic_report_error(-67);
    }
    int formatted_buffer_index = 0;
    for(int y = 0; y < y_dimension; y++)
    {
        for(int x = 0; x < x_dimension; x++)
        {
            formatted_buffer[formatted_buffer_index] = temp[x][y];
            formatted_buffer_index++;
        }
    }
    for(int x = 0; x < x_dimension; x++)
        free(temp[x]);
    free(temp);
    unsigned int data;
    glGenTextures(1, &data);
    glBindTexture(GL_TEXTURE_2D, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dimensions.x + 2, dimensions.y + 2,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, formatted_buffer);
    free(formatted_buffer);
    if(glGetError() == GL_OUT_OF_MEMORY)
    {
        glDeleteTextures(1, &data);
        return wic_report_error(-68);
    }
    target->p_data = data;
    target->p_dimensions = dimensions;
    return wic_report_error(0);
}
int wic_init_texture_from_file(WicTexture* target, const char* filepath,
                           enum WicFilter filter)
{
    if(target == 0)
        return wic_report_error(-69);
    unsigned char* buffer = 0;
    int x = 0;
    int y = 0;
    buffer = SOIL_load_image(filepath, &x, &y, 0, SOIL_LOAD_RGBA);
    WicPair dimensions = (WicPair) {x,y};
    if(buffer == 0)
        return wic_report_error(-70);
    int result = wic_init_texture_from_buffer(target, buffer, dimensions,
                                              WIC_RGBA, filter);
    SOIL_free_image_data(buffer);
    switch(result)
    {
        case 0:
            return wic_report_error(0);
        case -65:
            return wic_report_error(-71);
        case -66:
            return wic_report_error(-72);
        case -67:
            return wic_report_error(-73);
        case -68:
            return wic_report_error(-74);
        default:
            return wic_report_error(1000);
    }
}
int wic_free_texture(WicTexture* target)
{
    if(target == 0)
        return wic_report_error(-75);
    glDeleteTextures(1, &(target->p_data));
    target->p_data = 0;
    return wic_report_error(0);
}
void p_wic_select_texture(WicTexture* target)
{
    glBindTexture(GL_TEXTURE_2D, target->p_data);
}
