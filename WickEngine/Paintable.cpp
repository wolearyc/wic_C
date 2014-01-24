// ------------------------------------------------------------------------------------------------
// File:            Paintable.cpp
// ------------------------------------------------------------------------------------------------

#include "Paintable.h"
namespace wick
{
    Paintable::Paintable(Pair location)
    {
        location_ = location;
    }
    Paintable::Paintable(const Paintable& other)
    {
        location_ = other.location_;
    }
    Paintable::Paintable()
    {
        location_ = Pair();
    }

    Pair Paintable::getLocation()
    {
        return(location_);
    }
    void Paintable::setLocation(Pair location)
    {
        location_ = location;
    }
    void Paintable::translate(Pair translation)
    {
        setLocation(location_ + translation);
    }

    GLdouble Paintable::convertCoordinate(int coordinate, int dimension)
    {
        return(2.0 * coordinate / dimension - 1);
    }
}
