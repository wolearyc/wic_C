#include "TestState.h"
namespace wick
{
    TestState::TestState()
    {
    }
    TestState::~TestState()
    {
    }
    void TestState::initialize()
    {
        quad_ = Quad(Pair(50,50), Color::Blue, Pair(100,100));
    }
    void TestState::update(Window* window)
    {
        if(window->keyDown("w"))
        {
            quad_.setLocation(quad_.getLocation() + Pair(0,1));
        }
        if(window->keyDown("e"))
        {
            quad_.setRotation(quad_.getRotation() + 0.01);
        }
        if(window->keyDown("q"))
        {
            quad_.setScale(quad_.getScale() + Pair(-0.01, -0.01));
        }
    }
    void TestState::paint(Window* window)
    {
        quad_.paint(window);
    }
}

