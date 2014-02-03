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
// File:    WWindow.h
// ----------------------------------------------------------------------------

#ifndef WWINDOW_H
#define WWINDOW_H
#include <windows.h>
#include <GL/gl.h>
#include <iostream>
#include <string>
#include "WickError.h"
#include "Pair.h"
#include <time.h>
#include "SOIL.h"
#include <vector>
#include "State.h"
using std::string;
using std::vector;
namespace wick
{
	class Window
	{
	public:
        Window(string title, Pair dimensions, State* state);

		int start();
        LRESULT CALLBACK MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		Pair getDimensions();
		Pair getCursorLocation();
		bool keyDown(string key);
		vector<string> getDownKeys();
		bool keyPressed(string key);
		vector<string> getPressedKeys();
		long double time();

	private:

		string title_;
		Pair dimensions_;

		HWND hWnd_;
		HDC hdc_;
		HINSTANCE hInstance_;
		HGLRC hglrc_;

        Pair cursorLocation_;
        string getWickName(WPARAM wParam, LPARAM lParam);
        void keyUp(string key);
        vector<string> downKeys_;
        vector<string> pressedKeys_;

        State* state_;

	};

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	static Window* ApplicationHandle = 0;

}
#endif /* WWINDOW_H */


