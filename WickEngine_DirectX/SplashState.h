// ------------------------------------------------------------------------------------------------
// File:			SplashState.h
// Author:			Will O'Leary
// Documentation:   https://github.com/wolearyc/wick/wiki/class-SplashState
//-------------------------------------------------------------------------------------------------

#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H
#include "Wick.h"
namespace wick
{
	class SplashState : public State
	{
	public:

		// Constructor.
		SplashState(string filePath, Pair dimensions, State* nextState);

		// Loads resources.
		void initialize(Graphics* graphics);

		// Updates logic.
		void update(Input* input, int fps, Graphics* graphics);

		// Paints SplashState to screen.
		void paint(Graphics* graphics);

		// Deallocates resources.
		void release();

	protected:

		string filePath_;
		Pair dimensions_;
		State* nextState_;

		Font* factions150_;
		FadeText wick_;
		Font* factions20_;
		FadeText engine_;
		FadeText version_;

		Font* console15_;
		vector<FadeText*> queue_;
		vector<FadeText*> messages_;

		int stage_;
		long double time_;

	};
}
#endif

