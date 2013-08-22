// ------------------------------------------------------------------------------------------------
// File:                WickError.cpp
// ------------------------------------------------------------------------------------------------

#include "WickError.h"
namespace wick
{
        string wickVersion_ = "alpha 0.0.1";

        void wickPrint(string message)
        {
                std::cout << message + "\n";
        }
        void wickThrowWarning(string message)
        {
                std::cout << "Wick::Warning " + message + ".\n";
        }

        void wickThrowError(string message)
        {
                std::cout << "Wick::Error   " + message + " (fatal).\n";
                wickPrintSeparator();
                wickPrint("Window terminated (1).");
                wickPrint("Press return to continue...");
                std::cin.get();
                std::exit(1);
        }

        void wickPrintSeparator()
        {
            wickPrint("====================");
        }
}
