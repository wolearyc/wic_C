// ------------------------------------------------------------------------------------------------
// File:			HitBox.h
// Author:			Will O'Leary
// Documentation:   https://github.com/wolearyc/wick/wiki/class-HitBox
//-------------------------------------------------------------------------------------------------

#ifndef HITBOX_H
#define HITBOX_H
#include "Box.h"
namespace wick
{
	class HitBox: public Box
	{
	public:

		// Constructors.
		HitBox(Pair location, Pair upperLeft, Pair lowerRight);
		HitBox(Pair location, int width, int height);
		HitBox(Pair location, Pair upperLeft, int width, int height);
		HitBox(Pair location, int upperLeftX, int upperLeftY, int lowerRightX, int lowerRightY);
		HitBox(Pair location, Box box);
		HitBox(const HitBox& other);
		HitBox();

		// Location methods.
		Pair getLocation();
		void setLocation(Pair location);

		// Intersection methods.
		bool intersects(const HitBox& other);
		bool intersects(const Pair& pair);

	protected:

		Pair location_;

	};
}
#endif
