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

		Color(unsigned char red, unsigned char green, unsigned char blue);
		Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
		Color(const Color& other);
		Color();

		unsigned char getRed();
		void setRed(unsigned char red);
		unsigned char getGreen();
		void setGreen(unsigned char green);
		unsigned char getBlue();
		void setBlue(unsigned char blue);
		unsigned char getAlpha();
		void setAlpha(unsigned char alpha);

		void select();

	protected:

		unsigned char red_;
		float glRed_;
		unsigned char green_;
		float glGreen_;
		unsigned char blue_;
		float glBlue_;
		unsigned char alpha_;
		float glAlpha_;

	};
}
#endif
