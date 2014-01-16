// ------------------------------------------------------------------------------------------------
// File:			Paintable.h
// Author:			Will O'Leary
// Documentation:
//-------------------------------------------------------------------------------------------------

#ifndef PAINTABLE_H
#define PAINTABLE_H
#include "GL/gl.h"
#include "Pair.h"
#include "WWindow.h"
namespace wick
{
    class Paintable
    {
    public:
        Paintable(Pair location);
        Paintable(const Paintable& other);
        Paintable();

        virtual void paint(Window* window) = 0;

        Pair getLocation();
        void setLocation(Pair location);

    protected:
        Pair location_;

        GLdouble convertCoordinate(int coordinate, int dimension);
    };
}
#endif
