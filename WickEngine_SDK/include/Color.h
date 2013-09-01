// ------------------------------------------------------------------------------------------------
// File:			Color.h
// Author:			Will O'Leary
// Documentation:
//-------------------------------------------------------------------------------------------------

#ifndef COLOR_H
#define COLOR_H
#include "GL/gl.h"
#include "WickError.h"
namespace wick
{
	class Color
	{
	public:

		static Color White;
		static Color Silver;
		static Color Gray;
		static Color Black;
		static Color Red;
		static Color Maroon;
		static Color Yellow;
		static Color Olive;
		static Color Lime;
		static Color Green;
		static Color Aqua;
		static Color Teal;
		static Color Blue;
		static Color Navy;
		static Color Fuchsia;
		static Color Purple;

		Color(unsigned short red, unsigned short green, unsigned short blue);
		Color(unsigned short red, unsigned short green, unsigned short blue, unsigned short alpha);
		Color(const Color& other);
		Color();

		unsigned short getRed();
		void setRed(unsigned short red);
		unsigned short getGreen();
		void setGreen(unsigned short green);
		unsigned short getBlue();
		void setBlue(unsigned short blue);
		unsigned short getAlpha();
		void setAlpha(unsigned short alpha);

		void select();

	protected:

		unsigned short red_;
		float glRed_;
		unsigned short green_;
		float glGreen_;
		unsigned short blue_;
		float glBlue_;
		unsigned short alpha_;
		float glAlpha_;

	};
}
#endif
