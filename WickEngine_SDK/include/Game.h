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
// File:    Game.h
// ----------------------------------------------------------------------------
#ifndef GAME_H
#define GAME_H
#include "Pair.h"
#include "State.h"
#include "WickException.h"
#include "WickUtility.h"
#include "Dependencies/GLFW/glfw3.h"
#include <iostream>
#include <string>
using std::string;
#include <time.h>
#include <vector>
using std::vector;
namespace wick
{
	/// Designates keyboard keys and mouse buttons.
	enum WickKey
    {
        W_SPACE = 32,          ///< Space key.
        W_APOSTROPHE = 39,     ///< Apostrophe/double quotes key.
        WK_COMMA = 44,         ///< Comma key.
        W_MINUS = 45,          ///< Minus/underscore key.
        W_PERIOD = 46,         ///< Period key.
        W_SLASH = 47,          ///< Slash/question mark key.
        W_0 = 48,              ///< 0 key.
        W_1 = 49,              ///< 1 key.
        W_2 = 50,              ///< 2 key.
        W_3 = 51,              ///< 3 key.
        W_4 = 52,              ///< 4 key.
        W_5 = 53,              ///< 5 key.
        W_6 = 54,              ///< 6 key.
        W_7 = 55,              ///< 7 key.
        W_8 = 56,              ///< 8 key.
        W_9 = 57,              ///< 9 key.
        W_SEMICOLON = 59,      ///< Semicolon/colon key.
        W_EQUAL = 61,          ///< Equals/plus key.
        W_A = 65,              ///< A key.
        W_B = 66,              ///< B key.
        W_C = 67,              ///< C key.
        W_D = 68,              ///< D key.
        W_E = 69,              ///< E key.
        W_F = 70,              ///< F key.
        W_G = 71,              ///< G key.
        W_H = 72,              ///< H key.
        W_I = 73,              ///< I key.
        W_J = 74,              ///< J key.
        W_K = 75,              ///< K key.
        W_L = 76,              ///< L key.
        W_M = 77,              ///< M key.
        W_N = 78,              ///< N key.
        W_O = 79,              ///< O key.
        W_P = 80,              ///< P key.
        W_Q = 81,              ///< Q key.
        W_R = 82,              ///< R key.
        W_S = 83,              ///< S key.
        W_T = 84,              ///< T key.
        W_U = 85,              ///< U key.
        W_V = 86,              ///< V key.
        W_W = 87,              ///< W key.
        W_X = 88,              ///< X key.
        W_Y = 89,              ///< Y key.
        W_Z = 90,              ///< Z key.
        W_LEFT_BRACKET = 91,   ///< Left bracket/left curly brace key.
        W_BACKSLASH = 92,      ///< Backslash/vertical bar key.
        W_RIGHT_BRACKET = 93,  ///< Right bracket/right curly brace key.
        W_GRAVE_ACCENT = 96,   ///< Grave accent/tilde key.
        W_ESCAPE = 256,        ///< Escape key.
        W_ENTER = 257,         ///< Enter key.
        W_TAB = 258,           ///< Tab key.
        W_BACKSPACE = 259,     ///< Backspace key.
        W_INSERT = 260,        ///< Insert key.
        W_DELETE = 261,        ///< Delete key.
        W_RIGHT = 262,         ///< Right arrow key.
        W_LEFT = 263,          ///< Left arrow key.
        W_DOWN = 264,          ///< Down arrow key.
        W_UP = 265,            ///< Up arrow key.
        W_PAGE_UP = 266,       ///< Page up key.
        W_PAGE_DOWN = 267,     ///< Page down key.
        W_HOME = 268,          ///< Home key.
        W_END = 269,           ///< End key.
        W_CAPS_LOCK = 280,     ///< Caps lock key.
        W_SCROLL_LOCK = 281,   ///< Scroll lock key.
        W_NUM_LOCK = 282,      ///< Num lock key.
        W_PRINT_SCREEN = 283,  ///< Print screen key.
        W_PAUSE = 284,         ///< Pause key.
        W_F1 = 290,            ///< F1 key.
        W_F2 = 291,            ///< F2 key.
        W_F3 = 292,            ///< F3 key.
        W_F4 = 293,            ///< F4 key.
        W_F5 = 294,            ///< F5 key.
        W_F6 = 295,            ///< F6 key.
        W_F7 = 296,            ///< F7 key.
        W_F8 = 297,            ///< F8 key.
        W_F9 = 298,            ///< F9 key.
        W_F10 = 299,           ///< F10 key.
        W_F11 = 300,           ///< F11 key.
        W_F12 = 301,           ///< F12 key.
        W_F13 = 302,           ///< F13 key.
        W_F14 = 303,           ///< F14 key.
        W_F15 = 304,           ///< F15 key.
        W_F16 = 305,           ///< F16 key.
        W_F17 = 306,           ///< F17 key.
        W_F18 = 307,           ///< F18 key.
        W_F19 = 308,           ///< F19 key.
        W_F20 = 309,           ///< F20 key.
        W_F21 = 310,           ///< F21 key.
        W_F22 = 311,           ///< F22 key.
        W_F23 = 312,           ///< F23 key.
        W_F24 = 313,           ///< F24 key.
        W_F25 = 314,           ///< F25 key.
        W_KP_0 = 320,          ///< Keypad 0 key.
        W_KP_1 = 321,          ///< Keypad 1 key.
        W_KP_2 = 322,          ///< Keypad 2 key.
        W_KP_3 = 323,          ///< Keypad 3 key.
        W_KP_4 = 324,          ///< Keypad 4 key.
        W_KP_5 = 325,          ///< Keypad 5 key.
        W_KP_6 = 326,          ///< Keypad 6 key.
        W_KP_7 = 327,          ///< Keypad 7 key.
        W_KP_8 = 328,          ///< Keypad 8 key.
        W_KP_9 = 329,          ///< Keypad 9 key.
        W_KP_DECIMAL = 330,    ///< Keypad decimal key.
        W_KP_DIVIDE = 331,     ///< Keypad divide key.
        W_KP_MULTIPLY = 332,   ///< Keypad multiply key.
        W_KP_SUBTRACT = 333,   ///< Keypad subtract key.
        W_KP_ADD = 334,        ///< Keypad add key.
        W_KP_ENTER = 335,      ///< Keypad enter key.
        W_KP_EQUAL = 336,      ///< Keypad equals key.
        W_LEFT_SHIFT = 340,    ///< Left shift key.
        W_LEFT_CONTROL = 341,  ///< Left control key.
        W_LEFT_ALT = 342,      ///< Left alt key.
        W_LEFT_SUPER = 343,    ///< Left super key.
        W_RIGHT_SHIFT = 344,   ///< Right shift key.
        W_RIGHT_CONTROL = 345, ///< Right control key.
        W_RIGHT_ALT = 346,     ///< Right alt key.
        W_RIGHT_SUPER = 347,   ///< Right super key.
        W_MENU = 348,          ///< Menu key.
        W_LMB = 350,           ///< Left mouse button.
        W_RMB = 351,           ///< Right mouse button.
        W_MMB = 352,           ///< Middle mouse button.
        W_MB_4 = 353,          ///< Mouse button 4.
        W_MB_5 = 354,          ///< Mouse button 5.
        W_MB_6 = 355,          ///< Mouse button 6.
        W_MB_7 = 356,          ///< Mouse button 7.
        W_MB_8 = 357           ///< Mouse button 8.
    };
    /// \brief Holds and orchestrates the entire Wick game.
    ///
    /// Game creates the OS window, manages States, and handles keyboard and
    /// mouse input. A Game object should be instantiated (using 'new') in the
    /// program's main method, then a State should be added and initialized
    /// within the Game object, then the Game object should be executed.
    /// There should only be one Game object instantiated at any time. Game
    /// should always be instantiated using 'new', and therefore must be
    /// deallocated when the program terminates.
	class Game
	{
	public:
	    /// \brief Constructs a Game.
	    ///
	    /// \param title the OS window title.
	    /// \param dimensions the window dimensions in pixels.
	    /// \param fps the target frames per second.
	    /// \param resizeable designates whether the user can resize the OS
        ///        window. Ignored if the game is fullscreen.
        /// \param fullscreen designates whether or not the game is run
        ///        fullscreen
        /// \param samples the number the samples used in anti-aliasing. Larger
        ///        numbers of samples reduce aliasing, but too many samples can
        ///        interfere with rendering of small Text and Images. A value
        ///        of zero disables anti-aliasing.
        /// \exception WickException non-fatal exception when title is an empty
        ///            string.
        /// \exception WickException non-fatal exception when either of the
        ///            values in dimensions is less than or equal to 0.
        Game(string title, Pair dimensions, unsigned short fps,
             bool resizeable, bool fullscreen, unsigned short samples);
        /// \brief Constructs a Game with a non-resizeable standard OS window
        ///        rendered with 3 samples at 60 frames per second.
	    ///
	    /// \param title the OS window title.
	    /// \param dimensions the window dimensions in pixels.
        /// \exception WickException non-fatal exception when title is an empty
        ///            string.
        /// \exception WickException non-fatal exception when either of the
        ///            values in dimensions is less than or equal to 0.
        Game(string title, Pair dimensions);
        /// \brief Destructs a Game.
        ///
        /// The destructor deallocates all of the States stored in Game as
        /// well.
        ~Game();
        /// \brief Starts the game.
        ///
        /// The program exits this function once the user closes the OS window
        /// or stop() is called.
		void execute();
		/// \brief Stops the game and closes the OS window.
		void stop();
		/// \brief Gets the window dimensions of the OS window.
		///
		/// \return the dimensions of the OS window in pixels.
		Pair getDimensions();
		/// \brief Gets the display resolution.
		///
		/// \return the display resolution in dots per inch (usually
        ///         around Pair(72,72) or Pair(92,92))
		Pair getDeviceResolution();
		/// \brief Adds a state.
		///
		/// \param state pointer to the State object to add
		/// \param id desired ID to be assigned to the State
		/// \exception WickException non-fatal exception when the ID is already
		///            in use.
		void addState(State* state, unsigned short id);
		/// \brief Initializes a state that has already been added.
		///
		/// \param id the ID assigned to the State that is to be initialized.
		/// \exception WickException non-fatal exception when the ID is not
		///            assigned to any state.
		void initializeState(unsigned short id);
		/// \brief Adds and initializes a State.
		///
		/// Using this method is highly recommended unless memory is very
		/// limited (and the State is better left uninitialized).
		/// \param state pointer to the State object to add
		/// \param id desired ID to be assigned to the State
		/// \exception WickException non-fatal exception when ID is already in
		///            use.
		/// \exception WickException non-fatal exception when the ID is not
		///            assigned to any State, as a result of the failed
		///            addState operation.
		void addAndInitializeState(State* state, unsigned short id);
		/// \brief Deallocates a State.
		///
		/// \param id the ID assigned to the State that is to be deallocated.
		/// \exception WickException non-fatal exception when the ID is not
		///            assigned to any State.
		/// \exception WickException non-fatal exception when the State to be
		///            deallocated is currently being painted.
		void deallocateState(unsigned short id);
		/// \brief Removes a State.
		///
		/// Removing a State before having deallocating it results in a memory
		/// leak, unless the pointer is accessible elsewhere and can be
		/// deallocated.
		/// \param id the ID assigned to the State that is to be removed.
		/// \exception WickException non-fatal exception when the ID is not
		///            assigned to any State.
		/// \exception WickException non-fatal exception when the State to be
		///            removed is currently being painted.
		void removeState(unsigned short id);
		/// \brief Removes and deallocates a State.
		///
		/// Using this method is highly recommended in order to avoid
		/// accidental memory leaks.
		/// \param id the ID assigned to the State that is to be deallocated
		///        and removed.
		/// \exception WickException non-fatal exception when the ID is not
		///            assigned to any State.
		/// \exception WickException non-fatal exception when the State to be
		///            deallocated and removed is currently being painted.
		void deallocateAndRemoveState(unsigned short id);
		/// \brief Changes the State that is being painted.
		///
		/// \param id the ID assigned to the State that is to be painted.
		/// \exception WickException non-fatal exception when the ID is not
		///            assigned to any State.
		void selectState(unsigned short id);
		/// \brief Retrieves a State.
		///
		/// \param id the ID assigned to the State to retrieve.
		/// \return a pointer to the retrieved State or 0 if an exception is
		///         thrown.
		/// \exception WickException non-fatal exception when ID is not
		///            assigned to any State.
		State* findState(unsigned short id);
		/// \brief Checks whether a keyboard key or mouse button is depressed.
		///
		/// \param key key value
		/// \return true if the key is depressed, false otherwise.
		bool isKeyDown(enum WickKey key);
		/// \brief Checks whether a keyboard key or mouse button is down
		///        (depressed for the first time).
		/// \param key key value.
		/// \return true if the key is pressed, false otherwise.
		bool isKeyPressed(enum WickKey key);
		/// \brief Gets the keyboard input entered since the last refresh.
		///
		/// \return string of input.
		string getInput();
		/// \brief Gets the current location of the cursor.
		///
		/// \return the x-y coordinates of the cursor, measured from the bottom
		///         left of the screen.
		Pair getCursorLocation();
		/// \brief Gets the movement of the scroll wheel/ball.
		///
		/// \return a 2D displacement vector.
		Pair getScrollOffset();
		/// \brief Returns the time since execute() was called.
		///
		/// \return the time in seconds.
		double getTime();
    private:
		string title_;
		Pair dimensions_;
		GLFWwindow* window_;
        Pair deviceResolution_;
		vector<State*> states_;
		vector<unsigned short> ids_;
		State* currentState_;
		double spf_;
		bool resizeable_;
		bool fullscreen_;
		unsigned short samples_;
		static string wickVersion_;
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


