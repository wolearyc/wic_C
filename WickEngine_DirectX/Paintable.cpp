// ------------------------------------------------------------------------------------------------
// File:			Paintable.cpp 
//-------------------------------------------------------------------------------------------------

#include "Paintable.h"

namespace wick
{
	// Constructors.
	Paintable::Paintable()
	{
		location_ = Pair();
	}
	Paintable::Paintable(const Paintable &other)
	{
		location_ = other.location_;
	}

	// Destuctor.
	Paintable::~Paintable()
	{
	}
	
	// Location methods.
	Pair Paintable::getLocation()
	{
		return(location_);
	}
	void Paintable::setLocation(Pair location)
	{
		location_ = location;
	}
}