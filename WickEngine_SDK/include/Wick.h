//-------------------------------------------------------------------------------------------------
// File:		    Wick.h
// Author:		    Will O'Leary
// Documentation:
//-------------------------------------------------------------------------------------------------

#ifndef WICK_H
#define WICK_H

#ifdef _WIN64
    #include "WWindow.h"
#elif _WIN32
    #include "WWindow.h"
#elif __APPLE__
    #include "OWindow.h"
#elif __linux
    #include "LWindow.h"
#endif

#include "WickError.h"
#include "Pair.h"
#include "Texture.h"
#include "Rotateable.h"
#include "Polygon.h"
#include "State.h"
#include "Color.h"
#include "Paintable.h"
#include "Scaleable.h"
#include "Quad.h"
#include <string>
using std::string;
#endif

