// ------------------------------------------------------------------------------------------------
// File:			SplashState.cpp
//-------------------------------------------------------------------------------------------------

#include "SplashState.h"
namespace wick
{
	// Constructor.
	SplashState::SplashState(string filePath, Pair dimensions, State* nextState)
	{
		filePath_ = filePath;
		dimensions_ = dimensions;
		nextState_ = nextState;
	}

	// Loads resources.
	void SplashState::initialize(Graphics* graphics)
	{ 
		factions150_ = new Font(filePath_, "Factions", 150, graphics);
		wick_ = FadeText("Wick", Pair(507,260), factions150_, Color::White, 1.0, 1.0, 1.0);
		factions20_ = new Font(filePath_, "Factions", 20, graphics);
		engine_ = FadeText("Engine", Pair(717,380), factions20_, Color::White, 1.0, 1.0, 1.0);
		version_ = FadeText("Development Version", Pair(5,690), factions20_, Color::White, 1.0, 1.0, 1.0);

		console15_ = new Font("", "Lucida Console", 15, graphics);
		string possibleStrings[] = {
		"FILLER STRING"
		};
		srand((int) time(NULL));
		for(int i = 0; i<15; i++)
		{
			//int randIndex = rand() % 40;
			int randX = rand() % dimensions_.x_;
			int randY = rand() % dimensions_.y_;
			queue_.push_back(new FadeText(possibleStrings[0], Pair(randX, randY), console15_, 
							 Color(0,255,255,255), 0.5, 1.5));
		}

		stage_ = 0;
		time_ = Input::getTimeSec();
	}

	// Updates game logic.
	void SplashState::update(Input* input, int fps, Graphics* graphics)
	{
		long double newTime = Input::getTimeSec();
		if(input->isKeyPressed("LMB"))
		{
			stage_ = 18;
		}
		if(stage_ <= 14)
		{
			if(newTime-time_ >= 0.1)
			{
				messages_.push_back(queue_[stage_]);
				stage_++;
				time_ = newTime;
			}
		}
		else if(stage_ == 15)
		{
			if(newTime-time_ >= 0.5)
			{
				stage_++;
				time_ = newTime;
				for(unsigned int i = 0; i<messages_.size(); i++)
				{
					messages_[i]->fadeOut();
				}
			}
		}
		else if(stage_ == 16)
		{
			if(newTime-time_ >= 2.0)
			{
				stage_++;
				time_ = newTime;
			}
		}
		else if(stage_ == 17)
		{
			if(newTime-time_ >= 4.0)
			{
				stage_++;
			}
		}
		else
		{
			graphics->addState(nextState_, 1);
			graphics->initializeState(1);
			graphics->switchState(1);
			graphics->releaseState(0);
			graphics->removeState(0);
		}
		wick_.update(input, fps, graphics);
		engine_.update(input, fps, graphics);
		version_.update(input, fps, graphics);
		for(unsigned int i = 0; i<messages_.size(); i++)
		{
			messages_[i]->update(input, fps, graphics);
		}
	}
	
	// Paints logic to screen.
	void SplashState::paint(Graphics* graphics)
	{
		if(stage_ == 17)
		{
			wick_.paint(graphics);
			engine_.paint(graphics);
			version_.paint(graphics);
		}
		for(unsigned int i = 0; i<messages_.size(); i++)
		{
			messages_[i]->paint(graphics);
		}
	}

	// Deallocates resources.
	void SplashState::release()
	{
		factions150_->release();
		factions20_->release();
		console15_->release();
	}
}
