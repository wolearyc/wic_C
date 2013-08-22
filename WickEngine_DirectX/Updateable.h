// ------------------------------------------------------------------------------------------------
// File:			Updateable.h
// Author:			Will O'Leary
// Documentation:   https://github.com/wolearyc/wick/wiki/class-Updateable
//-------------------------------------------------------------------------------------------------

#ifndef UPDATEABLE_H
#define UPDATEABLE_H
#include "Input.h"
#include "Graphics.h"
namespace wick
{
	class Updateable
	{
	public:

		// Destructor.
		~Updateable();

		// Updates logic.
		virtual void update(Input* input, int fps, Graphics* graphics) = 0;

	};
}
#endif
