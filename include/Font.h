/* ----------------------------------------------------------------------------
 * wick - a simple, object-oriented 2D game engine for Mac OSX written in C++
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
 * File:    Font.h
 * ----------------------------------------------------------------------------
 */
#ifndef FONT_H
#define FONT_H
#include "Image.h"
#include "WickException.h"
#include "FreeType/ft2build.h"
#include FT_FREETYPE_H
#include FT_BITMAP_H
#include <string>
using std::string;
#include <vector>
using std::vector;
namespace wick
{
    /** \brief a font loaded from a file
      *
      * Font loads a font file from the file system and defines said font at a
	  * certain point size. TrueType fonts (TTF), TrueType collections (TTC),
	  * Type 1 fonts(PFA and PFB), CID-keyed Type 1 fonts, CFF fonts, OpenType
	  * fonts, OpenType collections, SFNT-based bitmap fonts, X11 PCF fonts,
	  * Windows FNT fonts, BDF fonts, and PFR fonts are supported. There is
	  * also limited support for Type 42 fonts. Font should be initialized as a
      * pointer (using "new") and destroyed after use via its destructor.
      *
      * Font can optionally antialias Fonts. Although antialiasing works well
      * at large point sizes, it can sometimes make smaller fonts harder to 
      * read. Therefore, it's often best to disable antialiasing when using
      * small point sizes.
      */
    class Font
    {
    public:
        /** \brief constructs Font
          * \param filepath the absolute or relative filepath to the font file
		  *        (only the name of the font file is required when the font is
		  *		   installed on the system)
          * \param point the desired font size in font points
          * \param game the game
          * \param antialias whether or not the font should be antialiased
          * \exception FileException non-fatal exception when the font file
		  *			   existing at filepath cannot be found, is currupted, or
		  *			   is not compatible with Wick; constructed Font is invalid
          */
        Font(string filepath, unsigned short point, Game* game, bool antialias);
        /** \brief constructs Font with antialiasing enabled
         * \param filepath the absolute or relative filepath to the font file
         *        (only the name of the font file is required when the font is
         *		   installed on the system)
         * \param point the desired font size in font points
         * \param game the game
         * \exception FileException non-fatal exception when the font file
         *			   existing at filepath cannot be found, is currupted, or
         *			   is not compatible with Wick; constructed Font is invalid
         */
        Font(string filepath, unsigned short point, Game* game);
        /** \brief constructs an invalid Font
          */
        Font();
        /** \brief deallocates Font
          */
        ~Font();
        /** \brief retrieves the size
          * \return the size in font points
          */
        unsigned short getPoint();
        /** \brief Retrieves whether or not antialiasing is enabled
          * \return true if antialiasing is enabled, false otherwise
          */
        bool isAntialised();
        /** \brief Retrieves a set of Images rendering a certain string
          * \param message the string to be rendered
          * \return a set of Images rendering the string (all of the Images's
		  *	        locations are (0,0), but their centers define the offset of
		  *			each character)
          */
        vector<Image> getImages(string message);
    protected:
        FT_Library library_;
        FT_Face face_;
        Texture* textures_[256];
        unsigned short point_;
        bool antialias_;
    };
}
#endif
