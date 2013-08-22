// ------------------------------------------------------------------------------------------------
// File:			Graphics.cpp
//-------------------------------------------------------------------------------------------------

#include "Graphics.h"
namespace wick
{
	// Constructor.
	Graphics::Graphics()
	{
		stateAdded_ = false;
	}

	// Destructor.
	Graphics::~Graphics()
	{
	}

	// Clears paint queue.
	void Graphics::clear()
	{
		ids_.clear();
		images_.clear();
		texts_.clear();
	}

	// State methods.
	void Graphics::addState(State* state, int id)
	{
		if(stateAdded_ == false)
		{
			stateAdded_ = true;
			states_.clear();
			stateIds_.clear();
			states_.push_back(state);
			stateIds_.push_back(id);
			currentState_ = state;
		}
		else
		{
			states_.push_back(state);
			stateIds_.push_back(id);
		}
		wickPrint("Added state " + std::to_string(id) + ".");
	}
	void Graphics::switchState(int id)
	{
		currentState_ = findState(id);
		wickPrint("Switched to state " + std::to_string(id) + ".");
	}
	void Graphics::releaseState(int id)
	{
		releasedStates_.push_back(findState(id));
		stateReleased_ = true;
		wickPrint("Released state " + std::to_string(id) + ".");
	}
	void Graphics::removeState(int id)
	{
		findState(id);
		removedStates_.push_back(id);
		stateRemoved_ = true;
		wickPrint("Removed state " + std::to_string(id) + ".");
	}
	void Graphics::initializeState(int id)
	{
		initializedStates_.push_back(findState(id));
		stateInitialized_ = true;
		wickPrint("Initialized state " + std::to_string(id) + ".");
	}

	// Finds a state with a specified ID.
	State* Graphics::findState(int id)
	{
		int size = stateIds_.size();
		for(int i = 0; i<size; i++)
		{
			if(stateIds_[i] == id)
			{
				return(states_[i]);
			}
		}
		wickThrowError("Invalid State ID.");
		return(NULL);
	}
}







