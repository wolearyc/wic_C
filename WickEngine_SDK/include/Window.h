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
// File:    Window.h
// ----------------------------------------------------------------------------
#ifndef WWINDOW_H
#define WWINDOW_H
#include "Pair.h"
#include "State.h"
#include "WickError.h"
#include "GLFW/glfw3.h"
#include <string>
using std::string;
#include <time.h>
#include <vector>
using std::vector;
namespace wick
{
	enum WickKey
    {
    W_SPACE = 32, W_APOSTROPHE = 39, WK_COMMA = 44, W_MINUS = 45,
    W_PERIOD = 46, W_SLASH = 47, W_0 = 48, W_1 = 49, W_2 = 50, W_3 = 51,
    W_4 = 52, W_5 = 53, W_6 = 54, W_7 = 55, W_8 = 56, W_9 = 57,
    W_SEMICOLON = 59, W_EQUAL = 61, W_A = 65, W_B = 66, W_C = 67, W_D = 68,
    W_E = 69, W_F = 70, W_G = 71, W_H = 72, W_I = 73, W_J = 74, W_K = 75,
    W_L = 76, W_M = 77, W_N = 78, W_O = 79, W_P = 80, W_Q = 81, W_R = 82,
    W_S = 83, W_T = 84, W_U = 85, W_V = 86, W_W = 87, W_X = 88, W_Y = 89,
    W_Z = 90, W_LEFT_BRACKET = 91, W_BACKSLASH = 92, W_RIGHT_BRACKET = 93,
    W_GRAVE_ACCENT = 96, W_ESCAPE = 256, W_ENTER = 257, W_TAB = 258,
    W_BACKSPACE = 259, W_INSERT = 260, W_DELETE = 261, W_RIGHT = 262,
    W_LEFT = 263, W_DOWN = 264, W_UP = 265, W_PAGE_UP = 266, W_PAGE_DOWN = 267,
    W_HOME = 268, W_END = 269, W_CAPS_LOCK = 280, W_SCROLL_LOCK = 281,
    W_NUM_LOCK = 282, W_PRINT_SCREEN = 283, W_PAUSE = 284, W_F1 = 290,
    W_F2 = 291, W_F3 = 292, W_F4 = 293, W_F5 = 294, W_F6 = 295, W_F7 = 296,
    W_F8 = 297, W_F9 = 298, W_F10 = 299, W_F11 = 300, W_F12 = 301, W_F13 = 302,
    W_F14 = 303, W_F15 = 304, W_F16 = 305, W_F17 = 306, W_F18 = 307,
    W_F19 = 308, W_F20 = 309, W_F21 = 310, W_F22 = 311, W_F23 = 312,
    W_F24 = 313, W_F25 = 314, W_KP_0 = 320, W_KP_1 = 321, W_KP_2 = 322,
    W_KP_3 = 323, W_KP_4 = 324, W_KP_5 = 325, W_KP_6 = 326, W_KP_7 = 327,
    W_KP_8 = 328, W_KP_9 = 329, W_KP_DECIMAL = 330, W_KP_DIVIDE = 331,
    W_KP_MULTIPLY = 332, W_KP_SUBTRACT = 333, W_KP_ADD = 334, W_KP_ENTER = 335,
    W_KP_EQUAL = 336, W_LEFT_SHIFT = 340, W_LEFT_CONTROL = 341,
    W_LEFT_ALT = 342, W_LEFT_SUPER = 343, W_RIGHT_SHIFT = 344,
    W_RIGHT_CONTROL = 345, W_RIGHT_ALT = 346, W_RIGHT_SUPER = 347,
    W_MENU = 348, W_LMB = 350, W_RMB = 351, W_MMB = 352, W_MB_4 = 353,
    W_MB_5 = 354, W_MB_6 = 355, W_MB_7 = 356, W_MB_8 = 357
    };
	class Window
	{
	public:
        Window(string title, Pair dimensions, unsigned short fps,
               bool resizeable, bool fullscreen, unsigned short samples);
        Window(string title, Pair dimensions);
        ~Window();
		void execute();
		Pair getDimensions();
		void addState(State* state, unsigned short id);
		void initializeState(unsigned short id);
		void addAndInitializeState(State* state, unsigned short id);
		void releaseState(unsigned short id);
		void removeState(unsigned short id);
		void releaseAndRemoveState(unsigned short id);
		void selectState(unsigned short id);
		State* findState(unsigned short id);
		bool isKeyDown(enum WickKey key);
		bool isKeyPressed(enum WickKey key);
		string getInput();
		Pair getCursorLocation();
		Pair getScrollOffset();
		double getTime();
    private:
		string title_;
		Pair dimensions_;
		GLFWwindow* window_;
		vector<State*> states_;
		vector<unsigned short> ids_;
		State* currentState_;
		unsigned short spf_;
		bool resizeable_;
		bool fullscreen_;
		unsigned short samples_;
		static bool focus_;
        static bool downKeys_[360];
        static vector<short> pressedKeys_;
        static string input_;
        static Pair cursorLocation_;
        static Pair scrollOffset_;
        static void resetInput();
		static void ErrorCallback(int error, const char* description);
		static void FocusCallback(GLFWwindow* window, int n);
        static void KeyCallback(GLFWwindow* window, int key, int scancode,
                                int action, int mods);
        static void CharCallback(GLFWwindow* window, unsigned int key);
        static void CursorLocationCallback(GLFWwindow* window, double x,
                                           double y);
        static void MouseButtonCallback(GLFWwindow* window, int button,
                                        int action, int mods);
        static void ScrollCallback(GLFWwindow* window, double x, double y);
	};
}
#endif


