// ------------------------------------------------------------------------------------------------
// File:			WWindow.cpp
// ------------------------------------------------------------------------------------------------

#include "WWindow.h"
namespace wick
{
	// Constructor.
	WWindow::WWindow(string title, int width, int height)
	{
        title_ = title;
		width_ = width;
		height_ = height;
	}

	// Starts and runs the window.
	int WWindow::start()
	{
	        print("==== Starting " + title_ + "... ====");
		ApplicationHandle = this;
		hInstance_ = GetModuleHandle(NULL);

		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(WNDCLASSEX));
		wc.lpfnWndProc = WndProc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_OWNDC;
		wc.hInstance = hInstance_;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.lpszClassName = "wickapp";

		RegisterClassEx(&wc);

		hWnd_ = CreateWindowEx(WS_EX_WINDOWEDGE, "wickapp", title_.c_str(), WS_OVERLAPPED | WS_CAPTION |
							   WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, 0, 0,  width_ + 7,
							   height_ + 32, NULL, NULL, hInstance_, NULL);

		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL
			| PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 8, 0,
			PFD_MAIN_PLANE, 0, 0, 0, 0
		};
		hdc_ = GetDC(hWnd_);
		int pixelFormat = ChoosePixelFormat(hdc_, &pfd);
		if(pixelFormat == 0)
                        throwError("Unable to find compatible pixel format");
		SetPixelFormat(hdc_, pixelFormat, &pfd);
		hglrc_ = wglCreateContext(hdc_);
		wglMakeCurrent(hdc_, hglrc_);

		ShowWindow(hWnd_, SW_SHOW);

		const int UPDATE_TIMER_ID = 0;
		SetTimer(hWnd_, UPDATE_TIMER_ID , 15, NULL);
		const int SECOND_TIMER_ID = 1;
		SetTimer(hWnd_, SECOND_TIMER_ID, 1000, NULL);

		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));

		while(GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return msg.wParam;
	}

	// Message handler.
	LRESULT WWindow::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch(message)
		{
		case WM_DESTROY:
			wglMakeCurrent(hdc_, NULL);
			wglDeleteContext(hglrc_);
			PostQuitMessage(0);
			print("==== " + title_ + " terminated (0). ====");
			print("Press return to continue...");
			std::cin.get();
			exit(0);
			return(0);
		case WM_SETFOCUS:
			return(0);
		case WM_KILLFOCUS:
			return(0);
		case WM_MOUSEMOVE:
			return(0);
		case WM_KEYDOWN:
			return(0);
		case WM_CHAR:
			return(0);
		case WM_KEYUP:
			return(0);
		case WM_LBUTTONDOWN:
			return(0);
		case WM_LBUTTONUP:
			return(0);
		case WM_RBUTTONDOWN:
			return(0);
		case WM_RBUTTONUP:
			return(0);
		case WM_MOUSEWHEEL:
			return(0);
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	// Window procedure called by Windows.
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		return(ApplicationHandle->MessageHandler(hWnd, message, wParam, lParam));
	}
}
