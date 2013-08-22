// ------------------------------------------------------------------------------------------------
// File:			Box.h
// Author:			Will O'Leary
// Documentation:	https://github.com/wolearyc/wick/wiki/class-Box
//-------------------------------------------------------------------------------------------------

#ifndef BOX_H
#define BOX_H
#include "Pair.h"
#include "WickError.h"
namespace wick
{
	class Box
	{
	public:

		Box(Pair upperLeft, Pair lowerRight);
		Box(int width, int height);
		Box(Pair upperLeft, int width, int height);
		Box(int upperLeftX, int upperLeftY, int lowerRightX, int lowerRightY);
		Box(const Box& other);
		Box();

		// Upper-left coordinate methods.
		Pair getUpperLeft();
		void setUpperLeft(Pair upperLeft);

		// Lower-right coordinate methods.
		Pair getLowerRight();
		void setLowerRight(Pair lowerRight);

		// Combined upper-left and lower-right method.
		void setUpperLeftAndLowerRight(Pair upperLeft, Pair lowerRight);

	protected:

		Pair upperLeft_;
		Pair lowerRight_;

	};
}
#endif
