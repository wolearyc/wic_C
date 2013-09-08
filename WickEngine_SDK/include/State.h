// ------------------------------------------------------------------------------------------------
// File:            State.h
// Author:			Will O'Leary
// Documentation:
//-------------------------------------------------------------------------------------------------

#ifndef STATE_H
#define STATE_H
#include "WWindow.h"
namespace wick
{
    class State
    {
        public:
            State();
            virtual ~State() = 0;

            virtual void initialize() = 0;

            virtual void paint(Window* window) = 0;
    };
}
#endi
