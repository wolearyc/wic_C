// ------------------------------------------------------------------------------------------------
// File:		main.cpp
// Author:		Will O'Leary
// ------------------------------------------------------------------------------------------------


#include "Wick.h"
#include "TestState.h"

using namespace wick;

int main()
{
	TestState* state = new TestState();
	state -> initialize();
	Window* window = new Window("Test", Pair(1280, 720), state);
	window->start();
	return(0);
}
