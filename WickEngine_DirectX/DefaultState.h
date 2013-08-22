// ------------------------------------------------------------------------------------------------
// File:			DefaultState.h
// Author:			Will O'Leary
// Documentation:	https://github.com/wolearyc/wick/wiki/class-DefaultState
//-------------------------------------------------------------------------------------------------

#ifndef DEFAULTSTATE_H
#define DEFAULTSTATE_H
#include "State.h"
namespace wick
{
	class DefaultState : public State
	{
	public:

		// Loads resources.
		void initialize(Graphics* graphics);

		// Updates game logic.
		void update(Input* input, int fps, Graphics* graphics);

		// Paints logic to screen.
		void paint(Graphics* graphics);

		// Deallocates resources.
		void release();

	};
}
#endif

