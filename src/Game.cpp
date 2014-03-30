/* ----------------------------------------------------------------------------
 * wick - a simple, object-oriented 2D game engine for Mac OSX written in C++
 * Copyright (C) 2013-2014  Will O'Leary
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------------------------
 * File:    Game.cpp
 * ----------------------------------------------------------------------------
 */
#include "Game.h"
namespace wick
{
	Game::Game(string title, Pair dimensions, unsigned short fps,
               bool resizeable, bool fullscreen, unsigned short samples)
    :title_(title), logicalDimensions_(dimensions), resizeable_(resizeable),
    fullscreen_(fullscreen), samples_(samples), selectedState_(nullptr)
	{
        if(title_ == "")
        {
            title_ = "Wick Game";
            throw(ParameterException("title", "any non-empty string",
                                     "Wick Game"));
        }
        if(logicalDimensions_.x_ <= 0)
        {
            logicalDimensions_.x_ = 500;
            throw(ParameterException("dimensions (x value)", ">0", "500"));
        }
        if(logicalDimensions_.y_ <= 0)
        {
            logicalDimensions_.y_ = 500;
            throw(ParameterException("dimensions (y value)", ">0", "500"));
        }
        if(fps == 0)
        {
            fps = 60;
            throw(ParameterException("fps", ">0", "60"));
        }
        spf_ = 1.0 / fps;
        if(!glfwInit())
            throw(ArchitectureException("glfw could not initialize"));
        glfwWindowHint(GLFW_REFRESH_RATE, 1.0 / spf_);
        glfwWindowHint(GLFW_SAMPLES, samples_);
        glfwWindowHint(GLFW_RESIZABLE, resizeable_);
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        if(fullscreen_)
            window_ = glfwCreateWindow(logicalDimensions_.x_,
                                       logicalDimensions_.y_, title_.c_str(),
                                       monitor, 0);
        else
            window_ = glfwCreateWindow(logicalDimensions_.x_,
                                       logicalDimensions_.y_, title_.c_str(), 0,
                                       0);
        if(window_ == 0)
            throw(ArchitectureException("window creation failed"));
        int actualWidth, actualHeight;
        glfwGetFramebufferSize(window_, &actualWidth, &actualHeight);
        actualDimensions_ = Pair(actualWidth, actualHeight);
        int physicalWidth; int physicalHeight;
        glfwGetMonitorPhysicalSize(monitor, &physicalWidth, &physicalHeight);
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        deviceResolution_ = Pair(mode->width / (physicalWidth * 0.0393701),
                                 mode->height / (physicalHeight * 0.0393701));
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
            selectedState_->update(this);
            resetInput();
            while(glfwGetTime() - lastUpdateTime < spf_)
            {
            }
            glFlush();
            glClearColor(0.0,0.0,0.0,1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            glLoadIdentity();
            selectedState_->paint(this);
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
	Pair Game::getLogicalDimensions()
	{
	    return(logicalDimensions_);
	}
    Pair Game::getActualDimensions()
	{
	    return(actualDimensions_);
	}

	Pair Game::getDeviceResolution()
	{
	    return(deviceResolution_);
	}
	void Game::addState(State* state, unsigned short id)
	{
	    unsigned int length = states_.size();
	    State* otherState = findState(id);
        if(otherState != nullptr)
            throw(WickException("state id already in use", false));
        else
        {
            states_.push_back(state);
            ids_.push_back(id);
        }
	}
    void Game::initializeState(unsigned short id)
    {
        State* state = findState(id);
        if(state == nullptr)
            throw(WickException("no state with that id exists", false));
        else
            state->initialize(this);
    }
    void Game::addAndInitializeState(State* state, unsigned short id)
    {
        addState(state, id);
        initializeState(id);
    }
    void Game::deallocateState(unsigned short id)
    {
        State* state = findState(id);
        if(state == nullptr)
            throw(WickException("no state with that id exists", false));
        else if(state == selectedState_)
            throw(WickException("cannot deallocate selected state", false));
        else
        {
            delete(state);
            state = nullptr;
        }
    }
	void Game::removeState(unsigned short id)
	{
        unsigned int length = states_.size();
        for(unsigned int i = 0; i < length; i++)
        {
            if(ids_[i] == id)
            {
                State* state = states_[i];
                if(state == selectedState_)
                    throw(WickException("cannot remove selected state", false));
                else
                {
                    states_.erase(states_.begin() + i);
                    ids_.erase(ids_.begin() + i);
                }
                break;
            }
        }
        throw(WickException("no state with that id exists", false));
	}
	void Game::deallocateAndRemoveState(unsigned short id)
	{
	    deallocateState(id);
	    removeState(id);
	}
	void Game::selectState(unsigned short id)
	{
	    State* state = findState(id);
        if(state == nullptr)
            throw(WickException("no state with that id exists", false));
        else
            selectedState_ = state;
	}
	State* Game::findState(unsigned short id)
	{
	    unsigned int length = states_.size();
	    for(unsigned int i = 0; i < length; i++)
        {
            if(ids_[i] == id)
                return(states_[i]);
        }
        return(nullptr);
	}
	bool Game::isKeyDown(enum WickKey key)
	{
	    return(Game::downKeys_[(int) key]);
	}
	bool Game::isKeyPressed(enum WickKey key)
	{
	    unsigned int length = pressedKeys_.size();
	    for(unsigned int i = 0; i < length; i++)
        {
            if(pressedKeys_[i] == (int) key)
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
	    cursorLocation.y_ = logicalDimensions_.y_ - cursorLocation.y_;
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
	    throw(ArchitectureException(string(description)));
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
