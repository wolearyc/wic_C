// ------------------------------------------------------------------------------------------------
// File:                WickError.cpp
// ------------------------------------------------------------------------------------------------

#include "WickError.h"
namespace wick
{
        string wickVersion_ = "0.0.2";

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
                printSeparator();
                print("Window terminated (1).");
                std::exit(1);
        }

        void printSeparator()
        {
            print("====================");
        }
}
