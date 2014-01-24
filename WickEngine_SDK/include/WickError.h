// ------------------------------------------------------------------------------------------------
// File:            WickError.h
// Author:          Will O'Leary
// Documentation:
// ------------------------------------------------------------------------------------------------

#ifndef WICKERROR_H
#define WICKERROR_H
#include <iostream>
#include <string>
#include <cstdlib>
using std::string;
namespace wick
{
        extern string wickVersion_;

        void print(string message);

        void throwWarning(string message);

        void throwError(string message);

        void printSeparator();

}
#endif
