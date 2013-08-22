// ------------------------------------------------------------------------------------------------
// File:			Toggle.h
// Author:			Will O'Leary
// Documentation:   https://github.com/wolearyc/wick/wiki/class-Toggle
//-------------------------------------------------------------------------------------------------

#ifndef TOGGLE_H
#define TOGGLE_H
#include "Button.h"
namespace wick
{
	class Toggle : public Button
	{
	public:

		// Constructors.
		Toggle(Image off, Image on, Pair location, Box target);
		Toggle(const Toggle& other);
		Toggle();

		// Updates logic.
		void update(Input* input, int fps, Graphics* graphics);

		// Paints Toggle to screen.
		void paint(Graphics* graphics);

	};
}
#endif

