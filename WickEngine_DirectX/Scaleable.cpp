// ------------------------------------------------------------------------------------------------
// File:			Scaleable.cpp
//-------------------------------------------------------------------------------------------------

#include "Scaleable.h"
namespace wick
{
	// Constructors.
	Scaleable::Scaleable()
	{
		scale_ = Pair(1,1);
	}
	Scaleable::Scaleable(const Scaleable &other)
	{
		scale_ = other.scale_;
	}

	// Destructor.
	Scaleable::~Scaleable()
	{
	}

	// Scale methods.
	Pair Scaleable::getScale()
	{
		return(scale_);
	}
	void Scaleable::setScale(Pair scale)
	{
		if(scale_.x_<0 || scale.y_<0)
		{
			wickThrowError("Invalid scale.");
		}
		scale_ = scale;
	}
}
