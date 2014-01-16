// ------------------------------------------------------------------------------------------------
// File:			Polygon.h
// Author:			Will O'Leary
// Documentation:
//-------------------------------------------------------------------------------------------------

#ifndef POLYGON_H
#define POLYGON_H
#include "GL/gl.h"
#include "Paintable.h"
#include "Rotateable.h"
#include "Scaleable.h"
#include "Color.h"
#include <vector>
using std::vector;
namespace wick
{
    class Polygon : public Paintable, public Rotateable, public Scaleable
    {
    public:
        Polygon(Pair location, Color color,  vector<Pair> baseVertices);
        Polygon(const Polygon& other);
        Polygon();

        void paint(Window* window);

        Color getColor();
        void setColor(Color color);

        vector<Pair> getBaseVertices();
        void setVertices(vector<Pair> vertices);

    protected:

        Color color_;
        vector<Pair> baseVertices_;
        vector<Pair> vertices_;

        void updateVertices();
    };
}
#endif
