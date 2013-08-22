// ------------------------------------------------------------------------------------------------
// File:			Scaleable.h
// Author:			Will O'Leary
// Documentation:   https://github.com/wolearyc/wick/wiki/class-Scaleable
//-------------------------------------------------------------------------------------------------

#ifndef SCALEABLE_H
#define SCALEABLE_H
#include "Pair.h"
#include "WickError.h"
namespace wick
{
	class Scaleable
	{
	public:

		// Constructors.
		Scaleable();
		Scaleable(const Scaleable &other);

		// Destructor.
		~Scaleable();

		// Scale methods.
		Pair getScale();
		void setScale(Pair scale);

	protected:

		Pair scale_;

	};
}
#endif
