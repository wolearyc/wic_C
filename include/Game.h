// ----------------------------------------------------------------------------
// wick - a simple, object-oriented 2D game engine for Mac OSX written in C++
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
#include "GLFW/glfw3.h"
#include <iostream>
#include <string>
using std::string;
#include <time.h>
#include <vector>
using std::vector;
namespace wick
{
	/// Designates keyboard keys and mouse buttons
	enum class WickKey
    {
        W_SPACE = 32,          ///< the space key.
        W_APOSTROPHE = 39,     ///< the apostrophe/double quotes key.
        WK_COMMA = 44,         ///< the comma key.
        W_MINUS = 45,          ///< the minus/underscore key.
        W_PERIOD = 46,         ///< the period key.
        W_SLASH = 47,          ///< the slash/question mark key.
        W_0 = 48,              ///< the 0 key.
        W_1 = 49,              ///< the 1 key.
        W_2 = 50,              ///< the 2 key.
        W_3 = 51,              ///< the 3 key.
        W_4 = 52,              ///< the 4 key.
        W_5 = 53,              ///< the 5 key.
        W_6 = 54,              ///< the 6 key.
        W_7 = 55,              ///< the 7 key.
        W_8 = 56,              ///< the 8 key.
        W_9 = 57,              ///< the 9 key.
        W_SEMICOLON = 59,      ///< the semicolon/colon key.
        W_EQUAL = 61,          ///< the equals/plus key.
        W_A = 65,              ///< the A key.
        W_B = 66,              ///< the B key.
        W_C = 67,              ///< the C key.
        W_D = 68,              ///< the D key.
        W_E = 69,              ///< the E key.
        W_F = 70,              ///< the F key.
        W_G = 71,              ///< the G key.
        W_H = 72,              ///< the H key.
        W_I = 73,              ///< the I key.
        W_J = 74,              ///< the J key.
        W_K = 75,              ///< the K key.
        W_L = 76,              ///< the L key.
        W_M = 77,              ///< the M key.
        W_N = 78,              ///< the N key.
        W_O = 79,              ///< the O key.
        W_P = 80,              ///< the P key.
        W_Q = 81,              ///< the Q key.
        W_R = 82,              ///< the R key.
        W_S = 83,              ///< the S key.
        W_T = 84,              ///< the T key.
        W_U = 85,              ///< the U key.
        W_V = 86,              ///< the V key.
        W_W = 87,              ///< the W key.
        W_X = 88,              ///< the X key.
        W_Y = 89,              ///< the Y key.
        W_Z = 90,              ///< the Z key.
        W_LEFT_BRACKET = 91,   ///< the left bracket/left curly brace key.
        W_BACKSLASH = 92,      ///< the backslash/vertical bar key.
        W_RIGHT_BRACKET = 93,  ///< the right bracket/right curly brace key.
        W_GRAVE_ACCENT = 96,   ///< the grave accent/tilde key.
        W_ESCAPE = 256,        ///< the escape key.
        W_ENTER = 257,         ///< the enter key.
        W_TAB = 258,           ///< the tab key.
        W_BACKSPACE = 259,     ///< the backspace key.
        W_INSERT = 260,        ///< the insert key.
        W_DELETE = 261,        ///< the delete key.
        W_RIGHT = 262,         ///< the right arrow key.
        W_LEFT = 263,          ///< the left arrow key.
        W_DOWN = 264,          ///< the down arrow key.
        W_UP = 265,            ///< the up arrow key.
        W_PAGE_UP = 266,       ///< the page up key.
        W_PAGE_DOWN = 267,     ///< the page down key.
        W_HOME = 268,          ///< the home key.
        W_END = 269,           ///< the end key.
        W_CAPS_LOCK = 280,     ///< the caps lock key.
        W_SCROLL_LOCK = 281,   ///< the scroll lock key.
        W_NUM_LOCK = 282,      ///< the num lock key.
        W_PRINT_SCREEN = 283,  ///< the print screen key.
        W_PAUSE = 284,         ///< the pause key.
        W_F1 = 290,            ///< the F1 key.
        W_F2 = 291,            ///< the F2 key.
        W_F3 = 292,            ///< the F3 key.
        W_F4 = 293,            ///< the F4 key.
        W_F5 = 294,            ///< the F5 key.
        W_F6 = 295,            ///< the F6 key.
        W_F7 = 296,            ///< the F7 key.
        W_F8 = 297,            ///< the F8 key.
        W_F9 = 298,            ///< the F9 key.
        W_F10 = 299,           ///< the F10 key.
        W_F11 = 300,           ///< the F11 key.
        W_F12 = 301,           ///< the F12 key.
        W_F13 = 302,           ///< the F13 key.
        W_F14 = 303,           ///< the F14 key.
        W_F15 = 304,           ///< the F15 key.
        W_F16 = 305,           ///< the F16 key.
        W_F17 = 306,           ///< the F17 key.
        W_F18 = 307,           ///< the F18 key.
        W_F19 = 308,           ///< the F19 key.
        W_F20 = 309,           ///< the F20 key.
        W_F21 = 310,           ///< the F21 key.
        W_F22 = 311,           ///< the F22 key.
        W_F23 = 312,           ///< the F23 key.
        W_F24 = 313,           ///< the F24 key.
        W_F25 = 314,           ///< the F25 key.
        W_KP_0 = 320,          ///< the keypad 0 key.
        W_KP_1 = 321,          ///< the keypad 1 key.
        W_KP_2 = 322,          ///< the keypad 2 key.
        W_KP_3 = 323,          ///< the keypad 3 key.
        W_KP_4 = 324,          ///< the keypad 4 key.
        W_KP_5 = 325,          ///< the keypad 5 key.
        W_KP_6 = 326,          ///< the keypad 6 key.
        W_KP_7 = 327,          ///< the keypad 7 key.
        W_KP_8 = 328,          ///< the keypad 8 key.
        W_KP_9 = 329,          ///< the keypad 9 key.
        W_KP_DECIMAL = 330,    ///< the keypad decimal key.
        W_KP_DIVIDE = 331,     ///< the keypad divide key.
        W_KP_MULTIPLY = 332,   ///< the keypad multiply key.
        W_KP_SUBTRACT = 333,   ///< the keypad subtract key.
        W_KP_ADD = 334,        ///< the keypad add key.
        W_KP_ENTER = 335,      ///< the keypad enter key.
        W_KP_EQUAL = 336,      ///< the keypad equals key.
        W_LEFT_SHIFT = 340,    ///< the left shift key.
        W_LEFT_CONTROL = 341,  ///< the left control key.
        W_LEFT_ALT = 342,      ///< the left alt key.
        W_LEFT_SUPER = 343,    ///< the left super key.
        W_RIGHT_SHIFT = 344,   ///< the right shift key.
        W_RIGHT_CONTROL = 345, ///< the right control key.
        W_RIGHT_ALT = 346,     ///< the right alt key.
        W_RIGHT_SUPER = 347,   ///< the right super key.
        W_MENU = 348,          ///< the menu key.
        W_LMB = 350,           ///< the left mouse button.
        W_RMB = 351,           ///< the right mouse button.
        W_MMB = 352,           ///< the middle mouse button.
        W_MB_4 = 353,          ///< mouse button 4.
        W_MB_5 = 354,          ///< mouse button 5.
        W_MB_6 = 355,          ///< mouse button 6.
        W_MB_7 = 356,          ///< mouse button 7.
        W_MB_8 = 357           ///< mouse button 8.
    };
    /// \brief Holds and orchestrates the entire game
    ///
    /// Game creates the OS window, manages States, and handles keyboard and 
	/// mouse input. A Game object should be instantiated (using 'new') in the 
	/// program's main method. Then a State should be added and initialized 
	/// within the Game object. Then the Game object should be executed. There 
	/// should only be one Game object instantiated at any time. Game should 
	///	always be instantiated using 'new', and must be deallocated using the 
	///	destructor before the program terminates. 
	class Game
	{
	public:
	    /// \brief A constructor
	    /// \param title the OS window title
	    /// \param dimensions the frame dimensions in pixels
	    /// \param fps the target frames per second
	    /// \param resizeable designates whether the user can resize the OS  
		///		   window (ignored if the game is fullscreen) 
        /// \param fullscreen designates whether or not the game is run
        ///        fullscreen
        /// \param samples the number the samples used in anti-aliasing. Larger
        ///        numbers of samples reduce aliasing, but too many samples can
        ///        interfere with rendering of small Text and Images. A value
        ///        of zero disables anti-aliasing.
        /// \exception ParameterException non-fatal exception when title is an
        ///            empty string;  the title is set to "Wick Game"
        /// \exception ParameterException non-fatal exception when either of the
        ///            values in the frame dimensions is less than or equal to 
		///			   0; the invalid dimension is set to 500
        Game(string title, Pair dimensions, unsigned short fps,
             bool resizeable, bool fullscreen, unsigned short samples);
	    /// \brief A constructor for a Window using 3 samples for antialiasing
	    /// \param title the OS window title
	    /// \param dimensions the frame dimensions in pixels
	    /// \param fps the target frames per second
	    /// \param resizeable designates whether the user can resize the OS  
		///		   window (ignored if the game is fullscreen) 
        /// \param fullscreen designates whether or not the game is run
        ///        fullscreen
        /// \exception ParameterException non-fatal exception when title is an
        ///            empty string; the title is set to "Wick Game"
        /// \exception ParameterException non-fatal exception when either of the
        ///            values in the frame dimensions is less than or equal to 
		///			   0; the invalid dimension is set to 500
        Game(string title, Pair dimensions);
        /// \brief The destructor
        /// The destructor deallocates all of the States stored in Game as well.
        ~Game();
        /// \brief Starts the game
        /// The program exits this function once the user closes the OS window 
		/// or stop() is called.
		void execute();
		/// \brief Stops the game and closes the OS window
		void stop();
		/// \brief Retrieves the frame dimensions of the OS window in logical
        ///        pixels
        ///
        /// The logical and actual dimensions of the OS window should be the
        /// same with standard resolution screens, but the two may differ with
        /// high dpi (retina or 4K) displays.
		/// \return the frame dimensions of the OS window in logical pixels.
		Pair getLogicalDimensions();
        /// \brief Retrieves the frame dimensions of the OS window in actual
        ///        physical pixels
        ///
        /// The actual and logical dimensions of the OS window should be the
        /// same with standard resolution screens, but the two may differ with
        /// high dpi (retina or 4K) displays.
        /// \return the frame dimensions of the OS window in actual pixels.
		Pair getActualDimensions();
		/// \brief Retrieves the display resolution
		/// \return the display resolution in pixels per inch
		Pair getDeviceResolution();
		/// \brief Adds a State
		/// \param state the State to add
		/// \param id the desired ID to be assigned to the State
		/// \exception WickException non-fatal exception when the ID is already
		///			   in use; the State is not added.
		void addState(State* state, unsigned short id);
		/// \brief Initializes a state that has already been added
		/// \param id the ID assigned to the State that is to be initialized
		/// \exception WickException non-fatal exception when no state with that
        ///            ID exists; nothing is initialized
		void initializeState(unsigned short id);
		/// \brief Adds and initializes a State
		/// \param state the State object to add and initialize
		/// \param id desired ID to be assigned to the State
		/// \exception WickException non-fatal exception when ID is already in
		///            use.
		/// \exception WickException non-fatal exception when the ID is not
		///            assigned to any State, as a result of the failed
		///            addState operation; no state is added or initialized
		void addAndInitializeState(State* state, unsigned short id);
		/// \brief Deallocates a State
		/// \param id the ID assigned to the State that is to be deallocated.
		/// \exception WickException non-fatal exception when the ID is not
		///            assigned to any State
		/// \exception WickException non-fatal exception when the State to be
		///            deallocated is currently selected; no State is
        ///            deallocated
		void deallocateState(unsigned short id);
		/// \brief Removes a State.
		///
		/// Removing a State before having deallocating it results in a memory
		/// leak, unless the pointer is accessible elsewhere and can be
		/// deallocated.
		/// \param id the ID assigned to the State that is to be removed
		/// \exception WickException non-fatal exception when no state with the
        ///            ID exists; no state is removed
		/// \exception WickException non-fatal exception when the State to be
		///            removed is currently selected; no state is removed
		void removeState(unsigned short id);
		/// \brief Removes and deallocates a State
		///
		/// Using this method is highly recommended in order to avoid
		/// accidental memory leaks.
		/// \param id the ID assigned to the State that is to be deallocated
		///        and removed
		/// \exception WickException non-fatal exception when no state with the
        ///            ID exists; no state is deallocated or removed
		/// \exception WickException non-fatal exception when the State to be
		///            deallocated and removed is currently selected; no state
        ///            is deallocated or removed
		void deallocateAndRemoveState(unsigned short id);
		/// \brief Changes the State that is being painted
		///
		/// \param id the ID assigned to the State that is to be painted.
		/// \exception WickException non-fatal exception when the ID is not
		///            assigned to any State; the selected state does not change
		void selectState(unsigned short id);
		/// \brief Retrieves a State
		///
		/// \param id the ID assigned to the State to retrieve
		/// \return a pointer to the retrieved State or nullptr if no state with
        ///         the ID exists
		State* findState(unsigned short id);
		/// \brief Checks whether a keyboard key or mouse button is depressed
		/// \param key the key value
		/// \return true if the key is depressed, and false otherwise
		bool isKeyDown(enum WickKey key);
		/// \brief Checks whether a keyboard key or mouse button is down
		///        (depressed for the first time)
		/// \param key the key value
		/// \return true if the key is pressed, and false otherwise
		bool isKeyPressed(enum WickKey key);
		/// \brief Retrieves the keyboard input entered since the last refresh
		/// \return the input
		string getInput();
		/// \brief Retrieves the current location of the cursor
		/// \return the x-y coordinates of the cursor
		Pair getCursorLocation();
		/// \brief Retrieves the movement of the scroll wheel/ball since the 
		///		   last refresh
		/// \return the 2D displacement vector of the scrool wheel/ball
		Pair getScrollOffset();
		/// \brief Retrieves the time since execute() was called
		/// \return the time since exexcute() was called in seconds
		double getTime();
    private:
		string title_;
		Pair logicalDimensions_;
        Pair actualDimensions_;
		GLFWwindow* window_;
        Pair deviceResolution_;
		vector<State*> states_;
		vector<unsigned short> ids_;
		State* selectedState_;
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


