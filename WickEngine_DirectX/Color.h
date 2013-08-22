// ------------------------------------------------------------------------------------------------
// File:			Color.h
// Author:			Will O'Leary
// Documentation:	https://github.com/wolearyc/wick/wiki/class-Color
//-------------------------------------------------------------------------------------------------

#ifndef COLOR_H
#define COLOR_H
#include "Direct3D.h"
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

		// Constructors.
		Color(int red, int green, int blue);
		Color(int alpha, int red, int green, int blue);
		Color(const Color& other);
		Color();

		// Alpha methods.
		int getAlpha();
		void setAlpha(int alpha);

		// Red methods.
		int getRed();
		void setRed(int red);

		// Green methods.
		int getGreen();
		void setGreen(int green);

		// Blue methods.
		int getBlue();
		void setBlue(int blue);

		// Fetches DirectX data.
		D3DCOLOR getData();

	protected:

		int alpha_;
		int red_;
		int green_;
		int blue_;
		D3DCOLOR data_;

	};
}
#endif
