// ------------------------------------------------------------------------------------------------
// File:			State.h
// Author:			Will O'Leary
// Documentation:   https://github.com/wolearyc/wick/wiki/class-State
//-------------------------------------------------------------------------------------------------

#ifndef STATE_H
#define STATE_H
#include "Paintable.h"
#include "Releaseable.h"
#include "Updateable.h"
namespace wick
{
	class Window;
	class State : public Paintable, public Releaseable, public Updateable
	{
	public:

		// Constructor.
		State();

		// Destructor.
		~State();

		// Loads resources.
		virtual void initialize(Graphics* graphics) = 0;

	};
}
#endif
