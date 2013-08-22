// ------------------------------------------------------------------------------------------------
// File:                WickError.h
// Description:         Provides wick errors (fatal) and warnings (non-fatal).
// Version:
// Author:              Will O'Leary
// Documentation:
// ------------------------------------------------------------------------------------------------

#ifndef WICKERROR_H
#define WICKERROR_H
#include <iostream>
#include <string>
using std::string;
namespace wick
{
        void print(string message);

        void throwWarning(string message);

        void throwError(string message);

}
#endif /* WICKERROR_H */
