#ifndef TESTSTATE_H
#define TESTSTATE_H
#include "Wick.h"
namespace wick
{
    class TestState : public State
    {
        public:
            TestState();
            ~TestState();
            void initialize();
            void update(Window* window);
            void paint(Window* window);
        private:
            Quad quad_;
    };
}
#endif
