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
// File:    State.h
// ----------------------------------------------------------------------------
#ifndef STATE_H
#define STATE_H
namespace wick
{
    class Game;
    /// \brief A game state that can be initialized, updated, and painted.
    ///
    /// State objects are the building blocks of wick. A State represents and
    /// executes a single "game state". A State could represent the main menu
    /// or a single level of a game. The programmer should write their own
    /// classes that inherit from State. These programmer-defined States 
    /// must define a destructor, initialize method, update method, and 
    /// paint method.
    class State
    {
    public:
        /// \brief The default constructor
        State();
        /// \brief The destructor
        ///
        /// The destructor should contain code to deallocate all pointers.
        virtual ~State();
        /// \brief Initializes the State
        ///
        /// This method is called once before the State is run. Typically,
        /// game objects are constructed here.
        virtual void initialize(Game* game) = 0;
        /// \brief Updates the game
        ///
        /// Every time before paint is called, this method is called once.
        /// Typically, user input is polled here and object locations,
        /// rotations, scales, etc. are changed accordingly.
        virtual void update(Game* game) = 0;
        /// \brief Paints the State to the screen
        ///
        /// This method is called once for every frame, so usually about
        /// 60 times per second. Typically, Paintable objects are painted here.
        virtual void paint(Game* game) = 0;
    };
}
#endif
