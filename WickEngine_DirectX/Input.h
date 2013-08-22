// ------------------------------------------------------------------------------------------------
// File:			Input.h
// Author:			Will O'Leary
// Documentation:   https://github.com/wolearyc/wick/wiki/class-Input
//-------------------------------------------------------------------------------------------------

#ifndef INPUT_H
#define INPUT_H
#include "Direct3D.h"
#include <time.h>
#include <vector>
#include <string>
#include "Pair.h"
using std::vector;
using std::string;
namespace wick
{
	class Input
	{
	public:

		// Constructor.
		Input();

		// Destructor.
		~Input();

		// Key down methods.
		bool isKeyDown(string key);
		void keyDown(string key);
		void keyUp(string key);
		vector<string> getDown();

		// Key pressed methods.
		bool isKeyPressed(string key);
		void keyPressed(string key);
		vector<string> getPressed();
		void reset();

		// Mouse location methods.
		void setMouseLocation(Pair location);
		Pair getMouseLocation();

		// Input activation methods.
		void activate();
		void deactivate();

		// Returns the time since program start in seconds.
		static long double getTimeSec();

	protected:

		vector<string> down_;
		vector<string> pressed_;
		Pair location_;
		bool activated_;

	};
}
#endif
