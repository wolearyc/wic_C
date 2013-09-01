// ------------------------------------------------------------------------------------------------
// File:			Polygon.h
// Author:			Will O'Leary
// Documentation:
//-------------------------------------------------------------------------------------------------

#ifndef POLYGON_H
#define POLYGON_H
#include "GL/gl.h"
#include "Pair.h"
#include "Color.h"
#include <vector>
using std::vector;
namespace wick
{
    class Polygon
    {
    public:
        Polygon(Pair location, Color color,  Pair vertex, ...);
        Polygon(const Polygon& other);
        Polygon();
        ~Polygon();

        void paint();

        Pair getLocation();
        void setLocation(Pair location);

        Color getColor();
        void setColor();

        vector<Pair> getVertices();
        void setVertices(vector<Pair> vertices);

    protected:

        Pair location_;
        Color color_;
        vector<Pair> vertices_;
    };
}

#endif
