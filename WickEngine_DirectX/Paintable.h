// ------------------------------------------------------------------------------------------------
// File:			Paintable.h
// Author:			Will O'Leary
// Documentation:   https://github.com/wolearyc/wick/wiki/class-Paintable
//-------------------------------------------------------------------------------------------------

#ifndef PAINTABLE_H
#define PAINTABLE_H
#include "Pair.h"
#include "Graphics.h"
namespace wick
{
	class Paintable
	{
	public:

		// Constructors.
		Paintable();
		Paintable(const Paintable &other);

		// Destructor.
		~Paintable();

		// Paints object to screen.
		virtual void paint(Graphics* graphics) = 0;

		// Location methods.
		Pair getLocation();
		void setLocation(Pair location);

	protected:

		Pair location_;

	};
}
#endif
