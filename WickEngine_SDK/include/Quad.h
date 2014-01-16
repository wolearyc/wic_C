// ------------------------------------------------------------------------------------------------
// File:			Quad.h
// Author:			Will O'Leary
// Documentation:
//-------------------------------------------------------------------------------------------------

#ifndef QUAD_H
#define QUAD_H
#include "Polygon.h"
namespace wick
{
    class Quad : public Polygon
    {
    public:
        Quad(Pair location, Color color, Pair dimensions);
        Quad(const Quad& other);
        Quad();

        Pair getDimensions();
        void setDimensions(Pair dimensions);

    protected:
        Pair dimensions_;
    };
}
#endif
