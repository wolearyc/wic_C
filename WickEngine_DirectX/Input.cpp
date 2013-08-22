// ------------------------------------------------------------------------------------------------
// File:			Input.cpp
//-------------------------------------------------------------------------------------------------

#include "Input.h"
namespace wick
{
	// Constructor.
	Input::Input()
	{
	}

	// Destructor.
	Input::~Input()
	{
	}

	// Key down methods.
	bool Input::isKeyDown(string key)
	{
		for(unsigned int i = 0; i < down_.size(); i++)
		{
			if(down_[i] == key)
			{
				return(true);
			}
		}
		return(false);
	}
	void Input::keyDown(string key)
	{
		down_.push_back(key);
	}
	void Input::keyUp(string key)
	{
		int size = down_.size();
		for(int i = 0; i<size; i++)
		{
			if(down_[i] == key)
			{
				down_.erase(down_.begin() + i);
				size--;
				i--;
			}
		}
	}
	vector<string> Input::getDown()
	{
		return(down_);
	}

	// Key pressed methods.
	bool Input::isKeyPressed(string key)
	{
		if(activated_)
		{
			for(unsigned int i = 0; i<pressed_.size(); i++)
			{
				if(pressed_[i] == key)
				{
					return(true);
				}
			}
		}
		return(false);
	}
	void Input::keyPressed(string key)
	{
		pressed_.push_back(key);
	}
	vector<string> Input::getPressed()
	{
		return(pressed_);
	}
	void Input::reset()
	{
		pressed_.clear();
	}

	// Mouse location methods.
	void Input::setMouseLocation(Pair location)
	{
		if(activated_)
		{
			location_ = location;
		}
	}
	Pair Input::getMouseLocation()
	{
		return(location_);
	}

	// Input activation methods.
	void Input::activate()
	{
		activated_ = true;
	}
	void Input::deactivate()
	{
		activated_ = false;
	}

	// Returns the time since program start in seconds.
	long double Input::getTimeSec()
	{
		return((float) clock()/CLOCKS_PER_SEC);
	}
}


