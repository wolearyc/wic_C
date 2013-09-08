// ------------------------------------------------------------------------------------------------
// File:			Polygon.cpp
// ------------------------------------------------------------------------------------------------

#include "Polygon.h"
namespace wick
{
    Polygon::Polygon(Pair location, Color color, vector<Pair> vertices)
    {
        location_ = location;
        color_    = color;
        vertices_ = vertices;
    }
    Polygon::Polygon(const Polygon& other)
    {
        location_ = other.location_;
        color_    = other.color_;
        vertices_ = other.vertices_;
    }
    Polygon::Polygon()
    {
        location_ = Pair();
        color_ = Color();
    }

    void Polygon::paint(Window* window)
    {
        Pair dimensions = window->getDimensions();
        color_.select();
        glBegin(GL_POLYGON);
            for(unsigned int i = 0; i < vertices_.size(); i++)
            {
                Pair vertex = vertices_[i];
                GLdouble x = vertex.x_ / dimensions.x_ - 1;
                GLdouble y = vertex.y_ / dimensions.y_ + 1;
                glVertex2d(x, y);
            }
        glEnd();
    }

    Pair Polygon:: getLocation()
    {
        return(location_);
    }
    void Polygon::setLocation(Pair location)
    {
        location_ = location;
    }

    Color Polygon::getColor()
    {
        return(color_);
    }
    void Polygon::setColor(Color color)
    {
        color_ = color;
    }

    vector<Pair> Polygon::getVertices()
    {
        return(vertices_);
    }
    void Polygon::setVertices(vector<Pair> vertices)
    {
        vertices_ = vertices;
    }
}
