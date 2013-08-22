// ------------------------------------------------------------------------------------------------
// File:            Window.cpp
// ------------------------------------------------------------------------------------------------

#include "Window.h"
namespace wick
{
    Window::Window(string title, int width, int height)
    {
        title_ = title;
        width_ = width;
        height_ = height;
    }

    Window::~Window()
    {
    }
}
