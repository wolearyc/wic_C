// ------------------------------------------------------------------------------------------------
// File:            Bounds.cpp
// ------------------------------------------------------------------------------------------------

#include "Bounds.h"
namespace wick
{
    Bounds::Bounds(Pair lowerLeft, Pair upperRight)
    {
        lowerLeft_ = lowerLeft;
        upperRight_ = upperRight;
    }
    Bounds::Bounds(int lowerLeftX, int lowerLeftY, int upperRightX, int upperRightY)
           :Bounds(Pair(lowerLeftX, lowerLeftY), Pair(upperRightX, upperRightY))
    {
    }
    Bounds::Bounds(Pair location, int xDimension, int yDimension)
           :Bounds(location, location + Pair(xDimension,yDimension))
    {
    }
    Bounds::Bounds(const Bounds& other)
    {
        lowerLeft_ = other.lowerLeft_;
        upperRight_ = other.upperRight_;
    }
    Bounds::Bounds()
    {
        lowerLeft_ = Pair();
        upperRight_ = Pair(64,64);
    }

    Pair Bounds::getLowerLeft()
    {
        return(lowerLeft_);
    }
    void Bounds::setLowerLeft(Pair lowerLeft)
    {
        lowerLeft_ = lowerLeft;
    }
    Pair Bounds::getUpperRight()
    {
        return(upperRight_);
    }
    void Bounds::setUpperRight(Pair upperRight)
    {
        upperRight_ = upperRight;
    }
}
