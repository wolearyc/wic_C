// ------------------------------------------------------------------------------------------------
// File:			Image.cpp
// ------------------------------------------------------------------------------------------------

#include "Image.h"
namespace wick
{
    Image::Image(Texture* texture, Pair location)
          :Quad(location, Color(255,255,255,255), texture->getDimensions())
    {
        texture_ = texture;
        bounds_ = Bounds(Pair(),texture->getDimensions());
    }
    Image::Image(const Image& other)
          :Quad(other)
    {
        texture_ = other.texture_;
        bounds_ = other.bounds_;
    }
    Image::Image()
          :Quad()
    {
        texture_ = new Texture();
        bounds_ = Bounds();
    }

    void Image::paint(Window* window)
    {
        updateVertices();
        Pair wDimensions = window->getDimensions();
        Pair tDimensions = texture_->getDimensions();
        texture_->select();
        color_.select();
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
            Pair vertex = vertices_[0];
            glTexCoord2f (bounds_.getLowerLeft().x_ / tDimensions.x_, -bounds_.getLowerLeft().y_ / tDimensions.y_);
            glVertex2d(convertCoordinate(vertex.x_ + location_.x_, wDimensions.x_),
                       convertCoordinate(vertex.y_ + location_.y_, wDimensions.y_));
            vertex = vertices_[1];
            glTexCoord2f (bounds_.getUpperRight().x_ / tDimensions.x_, -bounds_.getLowerLeft().y_ / tDimensions.y_);
            glVertex2d(convertCoordinate(vertex.x_ + location_.x_, wDimensions.x_),
                       convertCoordinate(vertex.y_ + location_.y_, wDimensions.y_));
            vertex = vertices_[2];
            glTexCoord2f (bounds_.getUpperRight().x_ / tDimensions.x_, -bounds_.getUpperRight().y_ / tDimensions.y_);
            glVertex2d(convertCoordinate(vertex.x_ + location_.x_, wDimensions.x_),
                       convertCoordinate(vertex.y_ + location_.y_, wDimensions.y_));
            vertex = vertices_[3];
            glTexCoord2f (bounds_.getLowerLeft().x_ / tDimensions.x_, -bounds_.getUpperRight().y_ / tDimensions.y_);
            glVertex2d(convertCoordinate(vertex.x_ + location_.x_, wDimensions.x_),
                       convertCoordinate(vertex.y_ + location_.y_, wDimensions.y_));
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }

    Texture* Image::getTexture()
    {
        return(texture_);
    }
    void Image::setTexture(Texture* texture)
    {
        texture_ = texture;
    }

    Bounds Image::getBounds()
    {
        return(bounds_);
    }
    void Image::setBounds(Bounds bounds)
    {
        bounds_ = bounds;
        setDimensions(bounds_.getUpperRight() - bounds_.getLowerLeft());
    }
}
