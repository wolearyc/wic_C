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
 * File:    Color.h
 * ----------------------------------------------------------------------------
 */
#ifndef COLOR_H
#define COLOR_H
#include "OpenGL/gl.h"
#include "WickException.h"
namespace wick
{
	/** \brief an RGB (24 bit) or RGBA (32 bit) color
	  *
	  * Color stores 8 bit red, green, blue, and alpha components. For the red,
      * green, and blue components, a value of 255 indicates complete 
      * expression, while a value of 0 indicates no expression. For the alpha 
      * component, a value of 255 indicates complete opacity while a value of 0 
      * indicates complete transparency.
      * 
      * Color contains some common pre-defined colors, stored as static
      * variables.
      */
	class Color
	{
	public:
		const static Color White;   /**< white (255,255,255) */
		const static Color Silver;  /**< silver (208,208,208) */
		const static Color Gray;    /**< gray (128,128,128) */
		const static Color Black;   /**< black (0,0,0) */
		const static Color Red;     /**< red (255,0,0) */
		const static Color Maroon;  /**< maroon (128,0,0) */
		const static Color Yellow;  /**< yellow (255,255,0) */
		const static Color Orange;  /**< orange (255,165,0) */
		const static Color Olive;   /**< olive (128,128,0) */
		const static Color Lime;    /**< lime (0,255,0) */
		const static Color Green;   /**< green (0,128,0) */
		const static Color Aqua;    /**< aqua (0,255,255) */
		const static Color Teal;    /**< teal (0,128,128) */
		const static Color Blue;    /**< blue (0,0,255) */
		const static Color Navy;    /**< navy (0,0,128) */
		const static Color Fuchsia; /**< fuschsia (255,0,255) */
		const static Color Purple;  /**< purple (128,0,128) */
		/** \brief constructs Color based on red, green, blue, and alpha
          *        components
		  * \param red the red component; value must be in the range [0,255]
		  * \param green the green component; value must be in the range [0,255]
		  * \param blue the blue component; value must be in the range [0,255]
		  * \param alpha the alpha component; value must be in the range [0,255]
		  * \exception ParameterException non-fatal exception when the value(s)
		  *			   of red, green, blue, and/or alpha exceed(s) 255; all
		  *            components that exceed 255 are set to 255
          */
		Color(unsigned char red, unsigned char green, unsigned char blue, 
			  unsigned char alpha);
		/** \brief constructs a completely opaque Color based on red, green, and
          *        blue components
		  * \param red the red component; value must be in the range [0,255]
          * \param green the green component; value must be in the range [0,255]
		  * \param blue the blue component; value must be in the range [0,255]
		  * \exception ParameterException non-fatal exception if the value(s)
	      *			   of red, green, blue, and/or alpha exceed(s) 255; all
		  *			   components that exceed 255 are set to 255
		  */
		Color(unsigned char red, unsigned char green, unsigned char blue);
		/** \brief constructs Color as white (255,255,255)
          */
		Color();
		/** \brief constructs a Color identical to another
          * \param other another Color
          */
        Color(const Color& other);
        /** \brief retrieves the red component
          * \return the red component
          */
		unsigned char getRed();
		/** \brief modifies the red component
		  * \param red the desired red component; value must be in the range
          *        [0-255]
		  * \exception ParameterException non-fatal exception if the value of
		  *			   red exceeds 255; the red component is set to 255
          */
		void setRed(unsigned char red);
		/** \brief retrieves the green component
          * \return the green component
          */
		unsigned char getGreen();
		/** \brief modifies the green component
		  * \param green the desired green component; value must be in the range
          *        [0-255]
		  * \exception ParameterException non-fatal exception if the value of
		  *			   green exceeds 255; the green component is set to 255
          */
		void setGreen(unsigned char green);
		/** \brief retrieves the blue component
          * \return the blue component
          */
		unsigned char getBlue();
		/** \brief modifies the blue component
		  * \param blue the desired blue component; value must be in the range
          *        [0-255]
		  * \exception ParameterException non-fatal exception if the value of
          *            blue exceeds 255; the blue component is set to 255
          */
		void setBlue(unsigned char blue);
		/** \brief retrieves the alpha component
          * \return the alpha component
          */
		unsigned char getAlpha();
		/** \brief modifies the alpha component
		  * \param alpha the desired alpha component; value must be in the range
          *        [0-255]
		  * \exception ParameterException non-fatal exception if the value of
		  *			   alpha exceeds 255; the alpha component is set to 255
          */
		void setAlpha(unsigned char alpha);
		/** \brief selects the color as the current painting color
          *
		  * This method is used behind the scenes and is of no interest to the
		  * average wick user.
          */
		void select();
	private:
		unsigned char red_;
		unsigned char green_;
		unsigned char blue_;
		unsigned char alpha_;
	};
}
#endif
