// ------------------------------------------------------------------------------------------------
// File:			FadeText.h
// Author:			Will O'Leary
// Documentation:   https://github.com/wolearyc/wick/wiki/class-FadeText
//-------------------------------------------------------------------------------------------------

#ifndef FADETEXT_H
#define FADETEXT_H
#include "Input.h"
#include "Text.h"
#include "Updateable.h"
namespace wick
{
	class FadeText : public Text, Updateable
	{
	public:

		// Constructors.
		FadeText(string message,Pair location,Font* font, Color color, double fadeIn, double fadeOut);
		FadeText(string message,Pair location,Font* font, Color color, double fadeIn, double delay,
				 double fadeOut);
		FadeText(const FadeText& other);
		FadeText();

		// Paints FadeText to screen.
		void paint(Graphics* graphics);

		// Updates transition.
		void update(Input* input, int fps, Graphics* graphics);

		// Transition methods.
		void fadeIn();
		void fadeOut();
		void reset();

		// Fade-in methods.
		double getFadeIn();
		void setFadeIn(double fadeIn);

		// Delay methods.
		double getDelay();
		void setDelay(double delay);

		// Fade-out methods.
		double getFadeOut();
		void setFadeOut(double fadeOut);

	protected:

		bool started_;
		int stage_;
		long double lastTime_;

		double fadeIn_;
		double delay_;
		double fadeOut_;

	};
}
#endif

