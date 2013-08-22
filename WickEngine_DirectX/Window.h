// ----------------------------------------------------------------------------
// File:			Window.h
// Author:			Will O'Leary
// Documentation:	https://github.com/wolearyc/wick/wiki/class-Window
//-----------------------------------------------------------------------------

#ifndef WINDOW_H
#define WINDOW_H
#include "Direct3D.h"

#include "DefaultState.h"
#include "Graphics.h"
#include "Image.h"
#include "Input.h"
#include "State.h"
#include "Text.h"
#include "WickError.h"

using std::string;

namespace wick
{

	class Window
	{

	public:

		// Constructor
		Window(string title, int width, int height);

		// Starts and runs the window. Automatically shuts down on exit.
		int start();

		void addState(State* state, int id);

		// Message handler for the window.
		LRESULT CALLBACK MessageHandler(HWND hWnd, UINT message, WPARAM wParam,
										LPARAM lParam);

	private:
		// Win32 variables.
		HWND hWnd_;
		HINSTANCE hInstance_;
		LPDIRECT3D9 d3d_;
		LPDIRECT3DDEVICE9 device_;

		// Wick variables.
		string title_;
		int width_;
		int height_;

		bool initialized_;
		Graphics* graphics_;
		Input* input_;
		int frames_;
		int fps_;

		LPD3DXSPRITE imageSprite_;
		LPD3DXSPRITE textSprite_;

		// Initilizes Direct3D.
		void initializeD3D(HWND hWnd);

		// Initilizes Wick Engine.
		void initializeWick();

		// Draws a single frame to the screen.
		void renderFrame();

		// Deallocates Wick Engine resources.
		void releaseWick();

		// Deallocates Direct3D resources.
		void releaseD3D();

		string vkToName(int code);

	};

	// Window procedure called by Windows.
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	// Handle to the Window.
	static Window* ApplicationHandle = 0;
}
#endif

