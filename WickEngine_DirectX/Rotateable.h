// ------------------------------------------------------------------------------------------------
// File:			Rotateable.h
// Author:			Will O'Leary
// Documentation:   https://github.com/wolearyc/wick/wiki/class-Rotateable
//-------------------------------------------------------------------------------------------------

#ifndef ROTATEABLE_H
#define ROTATEABLE_H
#include "Pair.h"
namespace wick
{
	class Rotateable
	{
	public:

		// Constructors.
		Rotateable();
		Rotateable(const Rotateable& other);

		// Destructor.
		~Rotateable();

		// Rotation methods.
		double getRotation();
		double getRotationInDegrees();
		void setRotation(double rotation);
		void setRotationInDegrees(double rotation);

		// Center methods.
		Pair getCenter();
		void setCenter(Pair center);
		void paintCentered(bool paintCentered);

	protected:

		double rotation_;
		Pair center_;
		bool paintCentered_;

	};
}
#endif
