// ------------------------------------------------------------------------------------------------
// File:			Quad.cpp
// ------------------------------------------------------------------------------------------------

#include "Quad.h"
namespace wick
{
    Quad::Quad(Pair location, Color color, Pair dimensions)
         :Polygon(location, color, {Pair(), Pair(dimensions.x_,0.0),dimensions, Pair(0.0, dimensions.y_)})
    {
        dimensions_ = dimensions;
    }
    Quad::Quad(const Quad& other)
         :Polygon(other)
    {
        dimensions_ = other.dimensions_;
    }
    Quad::Quad()
         :Polygon()
    {
        dimensions_ = Pair();
    }

    Pair Quad::getDimensions()
    {
        return(dimensions_);
    }
    void Quad::setDimensions(Pair dimensions)
    {
        dimensions_ = dimensions;
        setBaseVertices({Pair(), Pair(dimensions.x_,0.0),dimensions, Pair(0.0, dimensions.y_)});
    }
}
