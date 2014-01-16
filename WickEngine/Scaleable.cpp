// ------------------------------------------------------------------------------------------------
// File:			Scaleable.cpp
// ------------------------------------------------------------------------------------------------

#include "Scaleable.h"
namespace wick
{
    Scaleable::Scaleable(Pair scale)
    {
        scale_ = scale;
    }
    Scaleable::Scaleable(const Scaleable& other)
    {
        scale_ = other.scale_;
    }
    Scaleable::Scaleable()
    {
        scale_ = Pair(1,1);
    }

    Pair Scaleable::getScale()
    {
        return(scale_);
    }
    void Scaleable::setScale(Pair scale)
    {
        scale_ = scale;
    }
}
