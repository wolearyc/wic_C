// ----------------------------------------------------------------------------
// The Wick Engine - A simple, 2D, cross platform game library written in C++.
// Copyright (C) 2013-2014  Will O'Leary
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------
// File:    Window.cpp
// ----------------------------------------------------------------------------
#include "Window.h"
namespace wick
{
	Window::Window(string title, Pair dimensions, unsigned short fps,
                   bool resizeable, bool fullscreen, unsigned short samples)
           :title_(title), dimensions_(dimensions), spf_(1.0 / fps),
            resizeable_(resizeable), fullscreen_(fullscreen),
            samples_(samples), currentState_(0)
	{
	    print("Wick Engine version " + wickVersion_ + " Copyright (C)" +
              " 2013-2014 Will O'Leary\n");
        if(!glfwInit())
            throwError(W_WINDOW, "GLFW failed to initialize");
        glfwWindowHint(GLFW_REFRESH_RATE, 1.0 / spf_);
        glfwWindowHint(GLFW_SAMPLES, samples_);
        glfwWindowHint(GLFW_RESIZABLE, resizeable_);
        GLFWmonitor* monitor = 0;
        if(fullscreen_)
            monitor = glfwGetPrimaryMonitor();
        window_ = glfwCreateWindow(dimensions_.x_, dimensions_.y_,
                                              title_.c_str(), monitor, 0);
        if(window_ == 0)
            throwError(W_WINDOW, "Window creation failed");
        glfwSetErrorCallback(ErrorCallback);
        glfwSetWindowFocusCallback(window_, FocusCallback);
        glfwSetKeyCallback(window_, KeyCallback);
        glfwSetCharCallback(window_, CharCallback);
        glfwSetCursorPosCallback(window_, CursorLocationCallback);
        glfwSetScrollCallback(window_, ScrollCallback);
        glfwMakeContextCurrent(window_);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
    Window::Window(string title, Pair dimensions)
           :Window(title, dimensions, 60, false, false, 0)
    {
    }
	Window::~Window()
	{
	    glfwTerminate();
        unsigned int length = states_.size();
        for(unsigned int i = 0; i < length; i++)
        {
            delete(states_[i]);
        }
	}
	void Window::execute()
	{
        glfwSetTime(0.0);
        double firstTime;
        while (!glfwWindowShouldClose(window_))
        {
            firstTime = glfwGetTime();
            currentState_->update(this);
            resetInput();
            do
            {
                // Do nothing.
            }
            while(glfwGetTime() - firstTime < spf_);
            glFlush();
            glClearColor(0.0,0.0,0.0,1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            glLoadIdentity();
            currentState_->paint(this);
            glfwSwapBuffers(window_);
            glfwPollEvents();
        }
        print("\nTerminated.\n");
        glfwDestroyWindow(window_);
	}
	Pair Window::getDimensions()
	{
	    return(dimensions_);
	}
	void Window::addState(State* state, unsigned short id)
	{
	    unsigned int length = states_.size();
	    for(unsigned int i = 0; i < length; i++)
        {
            if(ids_[i] == id)
                throwError(W_WINDOW, "ID already in use.");
        }
        states_.push_back(state);
        ids_.push_back(id);
	}
    void Window::initializeState(unsigned short id)
    {
        findState(id)->initialize();
    }
    void Window::addAndInitializeState(State* state, unsigned short id)
    {
        addState(state, id);
        initializeState(id);
    }
    void Window::releaseState(unsigned short id)
    {
        State* state = findState(id);
        if(state == currentState_)
            throwError(W_WINDOW, "Cannot release current state");
        delete(state);
        state = 0;
    }
	void Window::removeState(unsigned short id)
	{
        unsigned int length = states_.size();
        for(unsigned int i = 0; i < length; i++)
        {
            if(ids_[i] = id)
            {
                if(findState(id) == currentState_)
                    throwError(W_WINDOW, "Cannot remove current state");
                states_.erase(states_.begin() + i);
                ids_.erase(ids_.begin() + i);
                break;
            }
        }
	}
	void Window::releaseAndRemoveState(unsigned short id)
	{
	    releaseState(id);
	    removeState(id);
	}
	void Window::selectState(unsigned short id)
	{
	    currentState_ = findState(id);
	}
	State* Window::findState(unsigned short id)
	{
	    unsigned int length = states_.size();
	    for(unsigned int i = 0; i < length; i++)
        {
            if(ids_[i] == id)
                return(states_[i]);
        }
        throwError(W_WINDOW, "State could not be found");
	}
	bool Window::isKeyDown(enum WickKey key)
	{
	    return(Window::downKeys_[key]);
	}
	bool Window::isKeyPressed(enum WickKey key)
	{
	    unsigned int length = pressedKeys_.size();
	    for(unsigned int i = 0; i < length; i++)
        {
            if(pressedKeys_[i] == key)
                return(true);
        }
        return(false);
	}
	string Window::getInput()
	{
	    return(input_);
	}
	Pair Window::getCursorLocation()
	{
	    Pair cursorLocation = cursorLocation_;
	    cursorLocation.y_ = dimensions_.y_ - cursorLocation.y_;
	    return(cursorLocation);
	}
	Pair Window::getScrollOffset()
	{
	    return(scrollOffset_);
	}
	double Window::getTime()
	{
	    return(glfwGetTime());
	}
	bool Window::focus_ = true;
	bool Window::downKeys_[360];
	vector<short> Window::pressedKeys_;
	string Window::input_;
	Pair Window::cursorLocation_;
	Pair Window::scrollOffset_;
	void Window::resetInput()
	{
	    pressedKeys_.clear();
	    input_ = "";
	    scrollOffset_ = Pair();
	}
	void Window::ErrorCallback(int error, const char* description)
	{
	    throwError(W_WINDOW, "GLFW error");
	}
	void Window::FocusCallback(GLFWwindow* window, int n)
    {
        focus_ = (bool) n;
    }
	void Window::KeyCallback(GLFWwindow* window, int key, int scancode,
                              int action, int mods)
    {
        if(focus_ && key < 360)
        {
            if(action == GLFW_RELEASE)
                downKeys_[key] = false;
            else if(action == GLFW_PRESS)
            {
                downKeys_[key] = true;
                pressedKeys_.push_back(key);
            }
        }
    }
    void Window::CharCallback(GLFWwindow* window, unsigned int key)
    {
        if(focus_)
        {
            string character = string(1, (unsigned char) key);
            input_ += character;
        }
    }
    void Window::CursorLocationCallback(GLFWwindow* window, double x, double y)
    {
        if(focus_)
        {
            cursorLocation_.x_ = x;
            cursorLocation_.y_ = y;
        }
    }
    void Window::MouseButtonCallback(GLFWwindow* window, int button,
                                     int action, int mods)
    {
        if(focus_)
        {
            if(action == GLFW_PRESS)
                downKeys_[button + 350] = true;
            else
                downKeys_[button + 350] = false;
        }
    }
    void Window::ScrollCallback(GLFWwindow* window, double x, double y)
    {
        if(focus_)
        {
            scrollOffset_.x_ = x;
            scrollOffset_.y_ = y;
        }
    }
}
