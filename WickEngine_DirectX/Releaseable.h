// ------------------------------------------------------------------------------------------------
// File:			Releaseable.h
// Author:			Will O'Leary
// Documentation:   https://github.com/wolearyc/wick/wiki/class-Releaseable
//-------------------------------------------------------------------------------------------------

#ifndef RELEASEABLE_H
#define RELEASEABLE_H
namespace wick
{
	class Releaseable
	{
	public:

		// Destructor.
		~Releaseable();

		// Deallocates object.
		virtual void release() = 0;

	};
}
#endif
