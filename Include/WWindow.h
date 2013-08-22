// ------------------------------------------------------------------------------------------------
// File:			WWindow.h
// Description:		        Creates and manages the window for Microsoft Windows.
// Version:
// Author:			Will O'Leary
// Documentation:
//-------------------------------------------------------------------------------------------------

#ifndef WWINDOW_H
#define WWINDOW_H
#include <windows.h>
#include <GL/gl.h>
#include <string>
namespace wick
{
	class WWindow
	{
	public:

		// Constructor.
		WWindow(string title, int width, int height);

		// Starts and runs the window.
		int start();

		// Message handler.
		LRESULT CALLBACK MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:

        // Windows variables.
		HWND hWnd_;
		HDC hdc_;
		HINSTANCE hInstance_;

		// OpenGL variables.
		HGLRC hglrc_;

		// Wick variables.
		string title_;
		int width_;
		int height_;
		bool initialized_;

	};

	// Window procedure.
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	// Handle.
	static Window* ApplicationHandle = 0;

}
#endif /* WWINDOW_H */


