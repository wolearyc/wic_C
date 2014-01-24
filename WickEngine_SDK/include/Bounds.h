// ------------------------------------------------------------------------------------------------
// File:            Bounds.h
// Author:          Will O'Leary
// Documentation:
// ------------------------------------------------------------------------------------------------

#ifndef BOUNDS_H
#define BOUNDS_H
#include "Pair.h"
namespace wick
{
    class Bounds
    {
    public:
        Bounds(Pair lowerLeft, Pair upperRight);
        Bounds(int lowerLeftX, int lowerLeftY, int upperRightX, int upperRightY);
        Bounds(Pair location, int xDimension, int yDimension);
        Bounds(const Bounds& other);
        Bounds();

        Pair getLowerLeft();
        void setLowerLeft(Pair lowerLeft);
        Pair getUpperRight();
        void setUpperRight(Pair upperRight);

    protected:
        Pair lowerLeft_;
        Pair upperRight_;
    };
}

#endif
