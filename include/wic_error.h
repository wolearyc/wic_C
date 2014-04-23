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
 * File:    wic_error.h
 * ----------------------------------------------------------------------------
 */
#ifndef WIC_ERROR_H
#define WIC_ERROR_H
#include <stdio.h>
#include <stdbool.h>
static int wic_error_code;
/** \brief reports the latest error code
 *  \param code the latest error code
 *  \return the latest error code
 */
int wic_report_error(int code);
/** \brief retrieves the latest error code
 *  \return the latest error code
 */
int wic_get_last_error();
/** \brief translates an error code into a human-readable message
 *  \param code the error code
 *  \return the error code translated into a human-readable message
 */
const char* wic_translate_error_code(int code);
#endif
