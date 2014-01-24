// ------------------------------------------------------------------------------------------------
// File:            WickError.cpp
// ------------------------------------------------------------------------------------------------

#include "WickError.h"
namespace wick
{
        string wickVersion_ = "0.0.8";

        void print(string message)
        {
                std::cout << message + "\n";
        }
        void throwWarning(string message)
        {
                std::cout << "-WARNING- : " + message + "\n";
        }

        void throwError(string message)
        {
                std::cout << "~ERROR~   : " + message + "\n";
                print("\nTerminated (1).");
                std::exit(1);
        }

        void printSeparator()
        {
            print("====================");
        }
}
