// ------------------------------------------------------------------------------------------------
// File:			Rotateable.h
// Author:			Will O'Leary
// Documentation:
//-------------------------------------------------------------------------------------------------

#ifndef ROTATEABLE_H
#define ROTATEABLE_H
#include "GL/gl.h"
#include "Pair.h"
namespace wick
{
    class Rotateable
    {
    public:
        Rotateable(float rotation);
        Rotateable(Pair center, float rotation);
        Rotateable(const Rotateable& other);
        Rotateable();

        Pair getCenter();
        void setCenter(Pair center);
        float getRotation();
        void setRotation(float rotation);

    protected:
        Pair center_;
        float rotation_;

    };
}
#endif
