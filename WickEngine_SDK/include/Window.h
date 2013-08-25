// ------------------------------------------------------------------------------------------------
// File:                        Window.h
// Description:                 Cross-platform generic class for a window.
// Version:
// Author:                      Will O'Leary
// Documentation:
// ------------------------------------------------------------------------------------------------

#ifndef WINDOW_H
#define WINDOW_H
#include <iostream>
#include <string>
#include "WickError.h"
using std::string;

namespace wick
{
    class Window
    {
    public:
        // Constructor.
        Window(string title, int width, int height);

        // Destructor.
        ~Window();

        // Starts and runs the window.
        int start();

    private:

        // Wick variables.
		string title_;
		int width_;
		int height_;
    };
}
#endif /* WINDOW_H */
