// ------------------------------------------------------------------------------------------------
// File:			Graphics.h
// Author:			Will O'Leary
// Documentation:   https://github.com/wolearyc/wick/wiki/class-Graphics
//-------------------------------------------------------------------------------------------------

#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <vector>
#include "WickError.h"
#include "Direct3D.h"
using std::vector;
namespace wick
{
	class Image;
	class Text;
	class State;
	class Graphics
	{
	public:

	    // Paint queue.
		vector<int> ids_;
		vector<Image*> images_;
		vector<Text*> texts_;

		// State management
		vector<State*> states_;
		State* currentState_;
		vector<State*> releasedStates_;
		bool stateReleased_;
		vector<State*> initializedStates_;
		bool stateInitialized_;
		vector<int> removedStates_;
		bool stateRemoved_;
		vector<int> stateIds_;

		LPDIRECT3DDEVICE9 device_;

		// Constructor.
		Graphics();

		// Destructor.
		~Graphics();

		// Clears paint queue.
		void clear();

		// State methods.
		void addState(State* state, int id);
		void switchState(int id);
		void releaseState(int id);
		void removeState(int id);
		void initializeState(int id);

		// Finds a state with a specified ID.
		State* findState(int id);

	protected:

		bool stateAdded_;

	};
}
#endif
