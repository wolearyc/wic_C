// ------------------------------------------------------------------------------------------------
// File:		Main.cpp
// Description:		The main method of any wick game. Must be included in any wick project.
//                      Contains variables for setting up the window.
// Version:
// Author:		Will O'Leary
// ------------------------------------------------------------------------------------------------


#include "Wick.h"

using namespace wick;

int main()
{
	Window* window = new Window("Test", 1280, 720);
	window->start();
	return(0);
}
