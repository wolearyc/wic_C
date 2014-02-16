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
// File:    Color.h
// ----------------------------------------------------------------------------
#ifndef COLOR_H
#define COLOR_H
#include "GL/gl.h"
#include "WickException.h"
namespace wick
{
	/// \brief Defines a RGB or RGBA color.
	///
	/// Color also constains some common pre-defined colors, stored as
	/// static variables.
	class Color
	{
	public:
		static Color White;   ///< White (255,255,255).
		static Color Silver;  ///< Silver (208,208,208).
		static Color Gray;    ///< Gray (128,128,128).
		static Color Black;   ///< Black (0,0,0).
		static Color Red;     ///< Red (255,0,0).
		static Color Maroon;  ///< Maroon (128,0,0).
		static Color Yellow;  ///< Yellow (255,255,0).
		static Color Orange;  ///< Orange (255,165,0).
		static Color Olive;   ///< Olive (128,128,0).
		static Color Lime;    ///< Lime (0,255,0).
		static Color Green;   ///< Green (0,128,0).
		static Color Aqua;    ///< Aqua (0,255,255).
		static Color Teal;    ///< Teal (0,128,128).
		static Color Blue;    ///< Blue (0,0,255).
		static Color Navy;    ///< Navy (0,0,128).
		static Color Fuchsia; ///< Fuschsia (255,0,255).
		static Color Purple;  ///< Purple (128,0,128)
		/// \brief A constructor defining an RGBA (red, green, blue, alpha) color.
		///
		/// All component values must range from 0 (no expression) to 255 (complete expression).
		/// An alpha value of 255 indicates complete opacity. 
		/// \param red red component value (0-255)
		/// \param green green component value (0-255)
		/// \param blue blue component value (0-255)
		/// \param alpha alpha component value (0-255)
		/// \exception WickException non-fatal exception when the value(s) of red, 
		///			   green, blue, and/or alpha exceeds 255. All components that exceed
		///			   255 are set to 255. 
		Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
		/// \brief A constructor defining an RGB(red, green, blue) color.
		///
		/// All component values must range from 0 (no expression) to 255 (complete expression).
		/// Colors are automatically constructed completely opaque.
		/// \param red red component value (0-255)
		/// \param green green component value (0-255)
		/// \param blue blue component value (0-255)
		/// \exception WickException non-fatal exception when the value(s) of red, 
		///			   green, and/or blue exceeds 255. All components that exceed
		///			   255 are set to 255.
		Color(unsigned char red, unsigned char green, unsigned char blue);
		/// \brief Default constructor.
		///
		/// Constructs a color representing white (255,255,255).
		Color();
		/// \brief Copy constructor.
        Color(const Color& other);
        /// \brief Gets the red component.
        ///
        /// \return red component
		unsigned char getRed();
		/// \brief Sets the red component.
		///
		/// The desired red component should be in the range 0-255.
		/// \param red desired red component (0-255)
		/// \exception WickException non-fatal exception if the value of red exceeds 255. 
		///	 		   The red component is then set to 255.
		void setRed(unsigned char red);
		/// \brief Gets the green component.
        ///
        /// \return green component
		unsigned char getGreen();
		/// \brief Sets the green component.
		///
		/// The desired green component should be in the range 0-255.
		/// \param green desired green component (0-255)
		/// \exception WickException non-fatal exception if the value of green exceeds 255. 
		///	 		   The green component is then set to 255.
		void setGreen(unsigned char green);
		/// \brief Gets the blue component.
        ///
        /// \return blue component
		unsigned char getBlue();
		/// \brief Sets the blue component.
		///
		/// The desired blue component should be in the range 0-255.
		/// \param blue desired blue component (0-255)
		/// \exception WickException non-fatal exception if the value of blue exceeds 255. 
		///	 		   The blue component is then set to 255.
		void setBlue(unsigned char blue);
		/// \brief Gets the alpha component.
        ///
        /// \return alpha component
		unsigned char getAlpha();
		/// \brief Sets the alpha component.
		///
		/// The desired alpha component should be in the range 0-255.
		/// \param alpha desired red component (0-255)
		/// \exception WickException non-fatal exception if the value of alpha exceeds 255. 
		///	 		   The alpha component is then set to 255.
		void setAlpha(unsigned char alpha);
		/// \brief Selects the color as the current painting color.
		///
		/// This method is used behind the scenes and should not be called by the Wick user.
		void select();
	private:
		unsigned char red_;
		unsigned char green_;
		unsigned char blue_;
		unsigned char alpha_;
	};
}
#endif
