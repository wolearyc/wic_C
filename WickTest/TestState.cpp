#include "TestState.h"
namespace wick
{
    TestState::TestState()
    {
    }
    TestState::~TestState()
    {
        delete(manTex_);
        manTex_ = NULL;
    }
    void TestState::initialize()
    {
        string root = "C:/Documents and Settings/User/My Documents/Programming/C-C++/Concepts/Pixel Space/";
        manTex_ = new Texture(root+"man.png");
        man_ = Image(manTex_, Pair(200,200)); man_.setScale(Pair(6,6));
        quad_ = Quad(Pair(0,0), Color::White, Pair(1000,1000));
        poly_ = Polygon(Pair(100,100), Color::Red, {Pair(),Pair(0,30),Pair(30,30),Pair(30,0)});
    }
    void TestState::update(Window* window)
    {
        if(window->keyDown("w"))
            man_.translate(Pair(0,1));
        if(window->keyDown("s"))
            man_.translate(Pair(0,-1));
        if(window->keyDown("a"))
            man_.translate(Pair(-1,0));
        if(window->keyDown("d"))
            man_.translate(Pair(1,0));
        if(window->keyDown(" "))
            man_.setColor(Color(255,255,255,128));
    }
    void TestState::paint(Window* window)
    {
        //quad_.paint(window);
        poly_.paint(window);
        man_.paint(window);
    }
}

