// ------------------------------------------------------------------------------------------------
// File:			WWindow.h
// Author:			Will O'Leary
// Documentation:
//-------------------------------------------------------------------------------------------------

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


