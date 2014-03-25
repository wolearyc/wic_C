// ----------------------------------------------------------------------------
// The Wick Engine - A simple, 2D, cross platform game library written in C++.
// Copyright (C) 2013-2014  Will O'Leary
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------
// File:    Font.h
// ----------------------------------------------------------------------------
#ifndef FONT_H
#define FONT_H
#ifdef _WIN64
    #define FONT_PATH_1 "C:/WINDOWS/Fonts/"
    #define FONT_PATH_2 "C:/WINDOWS/Fonts/"
#elif _WIN32
    #define FONT_PATH_1 "C:/WINDOWS/Fonts/"
    #define FONT_PATH_2 "C:/WINDOWS/Fonts/"
#elif __APPLE__
    #define FONT_PATH_1 "/Library/Fonts/"
    #define FONT_PATH_2 "/System/Library/Fonts/"
#elif __linux
    #define FONT_PATH_1 "/usr/share/fonts/"
    #define FONT_PATH_2 "/usr/local/share/fonts/"
#endif
#include "Image.h"
#include "WickException.h"
#include "Dependencies/FreeType/ft2build.h"
#include FT_FREETYPE_H
#include FT_BITMAP_H
#include <string>
using std::string;
#include <vector>
using std::vector;
namespace wick
{
    /// \brief Loads and stores a font
    ///
    /// Font loads a font file from the file system and defines said font at a 
	/// certain point size. TrueType fonts (TTF), TrueType collections (TTC), 
	/// Type 1 fonts(PFA and PFB), CID-keyed Type 1 fonts, CFF fonts, OpenType 
	/// fonts, OpenType collections, SFNT-based bitmap fonts, X11 PCF fonts, 
	/// Windows FNT fonts, BDF fonts, and PFR fonts are supported. There is 
	/// also limited support for Type 42 fonts. Font should be initialized as a 
    /// pointer (using "new") and destroyed after use via its destructor.
    class Font
    {
    public:
        /// \brief A constructor
        ///
    	/// Regarding antialiasing: Usually, smaller fonts are blurry when
    	/// antialiasing is turned on. Therefore, it is best to disable 
		/// antialiasing when rendering small fonts.
        /// \param filepath the absolute or relative filepath to the font file
		/// 	   (only the name of the font file is required when the font is
		///		   installed on the system)
        /// \param the point size of the font
        /// \param game the game 
        /// \param antialias whether or not the font should be antialiased
        /// \exception WickException fatal exception when the font file 
		///			   existing at filepath cannot be found, is currupted, or
		///			   is not compatible with Wick.
        Font(string filepath, unsigned short point, Game* game, bool antialias);
        /// \brief A constructor for an antialiased font
        ///
    	/// Regarding antialiasing: Usually, smaller fonts are blurry when
    	/// antialiasing is turned on. Therefore, it is best to disable 
		/// antialiasing when rendering small fonts.
        /// \param filepath the absolute or relative filepath to the font file
		/// 	   (only the name of the font file is required when the font is
		///		   installed on the system)
        /// \param the point size of the font
        /// \param game the game 
        /// \exception WickException fatal exception when the font file 
		///			   existing at filepath cannot be found, is currupted, or
		///			   is not compatible with Wick.
        Font(string filepath, unsigned short point, Game* game);
        /// \brief The default constructor
        ///
        /// The default constructor does NOT create a complete Font object. 
		/// Using a default font will result in an error. 
        Font();
        /// \brief The copy constructor
        Font(const Font& other);
        /// \brief The destructor
        ~Font();
        /// \brief Retrieves the size of the font
        /// \return the font size in font points
        unsigned short getPoint();
        /// \brief Modifies the font size 
        /// \param point the desired font size in font points
        void setPoint(unsigned short point);
        /// \brief Retrieves a set of Images rendering a certain string
        /// \param message the string to be rendered
        /// \return a set of Images rendering the string (all of the Images's   
		///	        locations are (0,0), but their centers define the offset of 
		///			each character)
        vector<Image> getImages(string message);
    private:
        FT_Library library_;
        FT_Face face_;
        unsigned short point_;
        bool antialias_;
        Texture* textures_[256];
    };
}
#endif
