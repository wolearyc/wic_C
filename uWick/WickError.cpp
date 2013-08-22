// ------------------------------------------------------------------------------------------------
// File:                WickError.cpp
// ------------------------------------------------------------------------------------------------

#include "WickError.h"
namespace wick
{
        void print(string message)
        {
                std::cout << message + "\n";
        }
        void throwWarning(string message)
        {
                std::cout << "Wick::Warning " + message + ".\n";
        }

        void throwError(string message)
        {
                std::cout << "Wick::Error   " + message + " (fatal).\n";
                std::exit(1);
        }
}
