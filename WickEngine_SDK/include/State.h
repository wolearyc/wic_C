// ------------------------------------------------------------------------------------------------
// File:            State.h
// Author:			Will O'Leary
// Documentation:
//-------------------------------------------------------------------------------------------------

#ifndef STATE_H
#define STATE_H
namespace wick
{
    class Window;
    class State
    {
        public:
            State();
            ~State();

            virtual void initialize() = 0;

            virtual void update(Window* window) = 0;

            virtual void paint(Window* window) = 0;
    };
}
#endif
