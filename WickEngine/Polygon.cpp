// ------------------------------------------------------------------------------------------------
// File:			Polygon.cpp
// ------------------------------------------------------------------------------------------------

#include "Polygon.h"
namespace wick
{
    Polygon::Polygon(Pair location, Color color, std::initializer_list<Pair> baseVertices)
            :Paintable(location), Rotateable()
    {
        color_ = color;
        baseVertices_ = baseVertices;
        vertices_ = vector<Pair>(baseVertices_.size(),Pair());
    }
    Polygon::Polygon(const Polygon& other)
            :Paintable(other), Rotateable(other)
    {
        color_    = other.color_;
        baseVertices_ = other.baseVertices_;
        vertices_ = other.vertices_;
    }
    Polygon::Polygon()
            :Paintable(), Rotateable()
    {
        color_ = Color();
    }

    void Polygon::paint(Window* window)
    {
        updateVertices();
        Pair dimensions = window->getDimensions();
        color_.select();
        glBegin(GL_POLYGON);
            for(unsigned int i = 0; i < baseVertices_.size(); i++)
            {
                Pair vertex = vertices_[i];
                glVertex2d(convertCoordinate(vertex.x_ + location_.x_, dimensions.x_),
                           convertCoordinate(vertex.y_ + location_.y_, dimensions.y_));
            }
        glEnd();
    }

    Color Polygon::getColor()
    {
        return(color_);
    }
    void Polygon::setColor(Color color)
    {
        color_ = color;
    }

    vector<Pair> Polygon::getBaseVertices()
    {
        return(baseVertices_);
    }
    void Polygon::setBaseVertices(std::initializer_list<Pair> baseVertices)
    {
        baseVertices_ = baseVertices;
        vertices_.clear();
        vertices_ = vector<Pair>(baseVertices_.size(),Pair());
    }

    void Polygon::updateVertices()
    {
        for(unsigned int i = 0; i < baseVertices_.size(); i++)
        {
            Pair vertex = baseVertices_[i];
            // Scaling.
            vertex = center_ + (Pair) ((vertex - center_) * scale_);
            // Rotation.
            vertex = Pair((vertex.x_ - center_.x_) * cos(rotation_) -
                          (vertex.y_ - center_.y_) * sin(rotation_),
                          (vertex.x_ - center_.x_) * sin(rotation_) +
                          (vertex.y_ - center_.y_) * cos(rotation_));
            vertices_[i] = vertex;
        }
    }
}
