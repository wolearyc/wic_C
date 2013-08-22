// ------------------------------------------------------------------------------------------------
// File:			FadeText.cpp
//-------------------------------------------------------------------------------------------------

#include "FadeText.h"

namespace wick
{
	// Constructors.
	FadeText::FadeText(string message, Pair location, Font* font, Color color, double fadeIn,
					   double fadeOut) : Text(message, location, font, color)
	{
		color_.setAlpha(0);
		started_ = false;
		stage_ = 0;
		setFadeIn(fadeIn);
		setDelay(10000000);
		setFadeOut(fadeOut);
	}
	FadeText::FadeText(string message, Pair location, Font* font, Color color, double fadeIn,
					   double delay, double fadeOut) : Text(message, location, font, color)
	{
		color_.setAlpha(0);
		started_ = false;
		stage_ = 0;
		setFadeIn(fadeIn);
		setDelay(delay);
		setFadeOut(fadeOut);
	}
	FadeText::FadeText(const FadeText& other) : Text(other)
	{
		started_ = other.started_;
		stage_ = other.stage_;
		lastTime_ = other.lastTime_;
		fadeIn_ = other.fadeIn_;
		delay_ = other.delay_;
		fadeOut_ = other.fadeOut_;
	}
	FadeText::FadeText() : Text()
	{
		started_ = false;
		stage_ = 0;
		lastTime_ = 0.0;
		fadeIn_ = 0;
		delay_ = 0;
		fadeOut_ = 0;
	}

	// Paints FadeText to screen.
	void FadeText::paint(Graphics* graphics)
	{
		Text::paint(graphics);
		if(!started_)
		{
			started_ = true;
			lastTime_ = Input::getTimeSec();
		}
	}

	// Updates transition.
	void FadeText::update(Input* input, int fps, Graphics* graphics)
	{
		long double time_ = input->getTimeSec();
		if(started_ && stage_ == 0)
		{
			int newAlpha = (int) ((time_-lastTime_)/fadeIn_*255.0);
			if(newAlpha>=255)
			{
				newAlpha = 255;
				stage_ = 1;
				lastTime_ = time_;
			}
			color_.setAlpha(newAlpha);
		}
		else if(stage_ == 1)
		{
			if(time_-lastTime_>=delay_)
			{
				stage_ = 2;
				lastTime_ = time_;
			}
		}
		else if(stage_ == 2)
		{
			int newAlpha = 255 - (int) ((time_-lastTime_)/fadeOut_*255.0);
			if(newAlpha<=0)
			{
				newAlpha = 0;
				stage_ = 3;
				started_ = false;
			}
			color_.setAlpha(newAlpha);
		}
	}

	// Transition methods.
	void FadeText::fadeIn()
	{
		started_ = true;
		lastTime_ = Input::getTimeSec();
		getColor().setAlpha(0);
		stage_ = 0;
	}
	void FadeText::fadeOut()
	{
		getColor().setAlpha(255);
		lastTime_ = Input::getTimeSec();
		stage_ = 2;
	}
	void FadeText::reset()
	{
		started_ = false;
		getColor().setAlpha(0);
		stage_ = 0;
	}

	// Fade-in methods.
	double FadeText::getFadeIn()
	{
		return(fadeIn_);
	}
	void FadeText::setFadeIn(double fadeIn)
	{
		if(fadeIn<0)
		{
			wickThrowError("Invalid fade-in time.");
		}
		fadeIn_ = fadeIn;
	}

	// Delay methods.
	double FadeText::getDelay()
	{
		return(delay_);
	}
	void FadeText::setDelay(double delay)
	{
		if(delay<0)
		{
			wickThrowError("Invalid delay time.");
		}
		delay_ = delay;
	}

	// Fade-out methods.
	double FadeText::getFadeOut()
	{
		return(fadeOut_);
	}
	void FadeText::setFadeOut(double fadeOut)
	{
		if(fadeOut<0)
		{
			wickThrowError("Invalid fade-out time.");
		}
		fadeOut_ = fadeOut;
	}
}
