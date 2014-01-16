// ------------------------------------------------------------------------------------------------
// File:			Scaleable.h
// Author:			Will O'Leary
// Documentation:
//-------------------------------------------------------------------------------------------------

#ifndef SCALEABLE_H
#define SCALEABLE_H
#include "GL/gl.h"
#include "Pair.h"
namespace wick
{
    class Scaleable
    {
    public:
        Scaleable(Pair scale);
        Scaleable(const Scaleable& other);
        Scaleable();

        Pair getScale();
        void setScale(Pair scale);

    protected:
        Pair scale_;

    };
}
#endif
