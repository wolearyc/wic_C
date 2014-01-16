// ------------------------------------------------------------------------------------------------
// File:			Rotateable.cpp
// ------------------------------------------------------------------------------------------------

#include "Rotateable.h"
namespace wick
{
    Rotateable::Rotateable(float rotation)
    {
        center_ = Pair();
        rotation_ = rotation;
    }
    Rotateable::Rotateable(Pair center, float rotation)
    {
        center_ = center;
        rotation_ = rotation;
    }
    Rotateable::Rotateable(const Rotateable& other)
    {
        center_ = other.center_;
        rotation_ = other.rotation_;
    }
    Rotateable::Rotateable()
    {
        center_ = Pair();
        rotation_ = 0.0;
    }

    Pair Rotateable::getCenter()
    {
        return(center_);
    }
    void Rotateable::setCenter(Pair center)
    {
        center_ = center;
    }
    float Rotateable::getRotation()
    {
        return(rotation_);
    }
    void Rotateable::setRotation(float rotation)
    {
        rotation_ = rotation;
    }

}
