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
#include "WWindow.h"
#include <vector>
using std::vector;
namespace wick
{
    class Polygon
    {
    public:
        Polygon(Pair location, Color color,  vector<Pair> vertices);
        Polygon(const Polygon& other);
        Polygon();

        void paint(Window* window);

        Pair getLocation();
        void setLocation(Pair location);

        Color getColor();
        void setColor(Color color);

        vector<Pair> getVertices();
        void setVertices(vector<Pair> vertices);

    protected:

        Pair location_;
        Color color_;
        vector<Pair> vertices_;
    };
}
#endif
