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
// File:    Game.cpp
// ----------------------------------------------------------------------------
#include "Game.h"
namespace wick
{
	Game::Game(string title, Pair dimensions, unsigned short fps,
               bool resizeable, bool fullscreen, unsigned short samples)
         :title_(title), dimensions_(dimensions), spf_(1.0 / fps),
          resizeable_(resizeable), fullscreen_(fullscreen),
          samples_(samples), currentState_(0)
	{
	    std::cout << "Wick Engine version " + wickVersion_ + " Copyright (C)" +
                     " 2013-2014 Will O'Leary\n\n";
        if(title_ == "")
        {
            title_ = "Wick Game";
            throw(WickException(W_GAME, 0));
        }
        if(dimensions_.x_ <= 0)
        {
            dimensions_.x_ = 500;
            throw(WickException(W_GAME, 1));
        }
        if(dimensions_.y_ <= 0)
        {
            dimensions_.y_ = 500;
            throw(WickException(W_GAME, 2));
        }
        if(!glfwInit())
            throw(WickException(W_GAME, 3));
        glfwWindowHint(GLFW_REFRESH_RATE, 1.0 / spf_);
        glfwWindowHint(GLFW_SAMPLES, samples_);
        glfwWindowHint(GLFW_RESIZABLE, resizeable_);
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        if(fullscreen_)
            window_ = glfwCreateWindow(dimensions_.x_, dimensions_.y_,
                                       title_.c_str(), monitor, 0);
        else
            window_ = glfwCreateWindow(dimensions_.x_, dimensions_.y_,
                                       title_.c_str(), 0, 0);
        if(window_ == 0)
            throw(WickException(W_GAME, 4));
        int width; int height;
        glfwGetMonitorPhysicalSize(monitor, &width, &height);
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        deviceResolution_ = Pair(mode->width / (width * 0.0393701),
                                 mode->height / (height * 0.0393701));
        glfwSetErrorCallback(ErrorCallback);
        glfwSetWindowFocusCallback(window_, FocusCallback);
        glfwSetKeyCallback(window_, KeyCallback);
        glfwSetCharCallback(window_, CharCallback);
        glfwSetCursorPosCallback(window_, CursorLocationCallback);
        glfwSetScrollCallback(window_, ScrollCallback);
        glfwMakeContextCurrent(window_);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_DEPTH_TEST);
	}
    Game::Game(string title, Pair dimensions)
         :Game(title, dimensions, 60, false, false, 3)
    {
    }
	Game::~Game()
	{
	    glfwTerminate();
        unsigned int length = states_.size();
        for(unsigned int i = 0; i < length; i++)
        {
            delete(states_[i]);
        }
	}
	void Game::execute()
	{
        glfwSetTime(0.0);
        unsigned short updates = 0;
        double lastSecondTime = 0.0;
        while (!glfwWindowShouldClose(window_))
        {
            double lastUpdateTime = glfwGetTime();
            glfwPollEvents();
            currentState_->update(this);
            resetInput();
            while(glfwGetTime() - lastUpdateTime < spf_)
            {
            }
            glFlush();
            glClearColor(0.0,0.0,0.0,1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            glLoadIdentity();
            currentState_->paint(this);
            glfwSwapBuffers(window_);
            updates++;
            if(glfwGetTime() - lastSecondTime >= 1.0)
            {
                updates = 0;
                lastSecondTime = glfwGetTime();
            }
        }
        std::cout << "\nTerminated.\n";
        glfwDestroyWindow(window_);
	}
	void Game::stop()
	{
        glfwSetWindowShouldClose(window_, true);
	}
	Pair Game::getDimensions()
	{
	    return(dimensions_);
	}
	Pair Game::getDeviceResolution()
	{
	    return(deviceResolution_);
	}
	void Game::addState(State* state, unsigned short id)
	{
	    bool found = false;
	    unsigned int length = states_.size();
	    for(unsigned int i = 0; i < length; i++)
        {
            if(ids_[i] == id)
                found = true;
        }
        if(found)
            throw(WickException(W_GAME, 5, toString(id)));
        else
        {
            states_.push_back(state);
            ids_.push_back(id);
        }
	}
    void Game::initializeState(unsigned short id)
    {
        findState(id)->initialize(this);
    }
    void Game::addAndInitializeState(State* state, unsigned short id)
    {
        addState(state, id);
        initializeState(id);
    }
    void Game::deallocateState(unsigned short id)
    {
        State* state = findState(id);
        if(state == currentState_)
            throw(WickException(W_GAME, 7, toString(id)));
        else
        {
            delete(state);
            state = 0;
        }
    }
	void Game::removeState(unsigned short id)
	{
        unsigned int length = states_.size();
        for(unsigned int i = 0; i < length; i++)
        {
            if(ids_[i] == id)
            {
                if(findState(id) == currentState_)
                    throw(WickException(W_GAME, 7, toString(id)));
                else
                {
                    states_.erase(states_.begin() + i);
                    ids_.erase(ids_.begin() + i);
                }
                break;
            }
        }
	}
	void Game::deallocateAndRemoveState(unsigned short id)
	{
	    deallocateState(id);
	    removeState(id);
	}
	void Game::selectState(unsigned short id)
	{
	    currentState_ = findState(id);
	}
	State* Game::findState(unsigned short id)
	{
	    unsigned int length = states_.size();
	    for(unsigned int i = 0; i < length; i++)
        {
            if(ids_[i] == id)
                return(states_[i]);
        }
        throw(WickException(W_GAME, 8, toString(id)));
        return(0);
	}
	bool Game::isKeyDown(enum WickKey key)
	{
	    return(Game::downKeys_[key]);
	}
	bool Game::isKeyPressed(enum WickKey key)
	{
	    unsigned int length = pressedKeys_.size();
	    for(unsigned int i = 0; i < length; i++)
        {
            if(pressedKeys_[i] == key)
                return(true);
        }
        return(false);
	}
	string Game::getInput()
	{
	    return(input_);
	}
	Pair Game::getCursorLocation()
	{
	    Pair cursorLocation = cursorLocation_;
	    cursorLocation.y_ = dimensions_.y_ - cursorLocation.y_;
	    return(cursorLocation);
	}
	Pair Game::getScrollOffset()
	{
	    return(scrollOffset_);
	}
	double Game::getTime()
	{
	    return(glfwGetTime());
	}
	string Game::wickVersion_ = "0.1.3";
	bool Game::focus_ = true;
	bool Game::downKeys_[360];
	vector<short> Game::pressedKeys_;
	string Game::input_;
	Pair Game::cursorLocation_;
	Pair Game::scrollOffset_;
	void Game::resetInput()
	{
	    pressedKeys_.clear();
	    input_ = "";
	    scrollOffset_ = Pair();
	}
	void Game::ErrorCallback(int error, const char* description)
	{
	    throw(WickException(W_GAME, 9, string(description)));
	}
	void Game::FocusCallback(GLFWwindow* window, int n)
    {
        focus_ = (bool) n;
    }
	void Game::KeyCallback(GLFWwindow* window, int key, int scancode,
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
    void Game::CharCallback(GLFWwindow* window, unsigned int key)
    {
        if(focus_)
        {
            string character = string(1, (unsigned char) key);
            input_ += character;
        }
    }
    void Game::CursorLocationCallback(GLFWwindow* window, double x, double y)
    {
        if(focus_)
        {
            cursorLocation_.x_ = x;
            cursorLocation_.y_ = y;
        }
    }
    void Game::MouseButtonCallback(GLFWwindow* window, int button,
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
    void Game::ScrollCallback(GLFWwindow* window, double x, double y)
    {
        if(focus_)
        {
            scrollOffset_.x_ = x;
            scrollOffset_.y_ = y;
        }
    }
}
