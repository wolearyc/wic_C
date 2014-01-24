// ------------------------------------------------------------------------------------------------
// File:			Image.h
// Author:			Will O'Leary
// Documentation:
//-------------------------------------------------------------------------------------------------

#ifndef IMAGE_H
#define IMAGE_H
#include "Quad.h"
#include "Texture.h"
#include "Bounds.h"
namespace wick
{
    class Image : public Quad
    {
    public:
        Image(Texture* texture, Pair location);
        Image(const Image& other);
        Image();

        void paint(Window* window);

        Texture* getTexture();
        void setTexture(Texture* texture);

        Bounds getBounds();
        void setBounds(Bounds bounds);

    protected:
        Texture* texture_;
        Bounds bounds_;
    };
}
#endif

