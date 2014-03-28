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
// File:    Text.h
// ----------------------------------------------------------------------------
#ifndef TEXT_H
#define TEXT_H
#include "Color.h"
#include "Font.h"
#include <initializer_list>
using std::initializer_list;
#include <string>
using std::string;
#include <vector>
using std::vector;
namespace wick
{
    /// \brief Text stores a string that can be painted to the screen
    ///
    /// A Text object can be painted, rotated, scaled, colored, and centered.
    /// Text objects operate with a Font object, much like Images operate with
    /// Textures. Multiple Text objects can use the same Font.
    class Text : public Paintable, public Rotateable, public Scaleable
    {
    public:
        /// \brief A constructor for multicolored Text
        /// \param location the screen location
        /// \param message the string to be rendered
        /// \font the font to use
        /// \colors a set of colors; each color in the set is assigned to one
        ///         letter in order, if the set of colors is too small for the
        ///         whole message, the color pattern repeats
        Text(Pair location, string message, Font* font, vector<Color> colors);
        /// \brief A constructor for multicolored Text
        /// \param location the screen location
        /// \param message the string to be rendered
        /// \font the font to use
        /// \colors a set of colors; each color in the set is assigned to one
        ///         letter in order, if the set of colors is too small for the
        ///         whole message, the color pattern repeats; the use of an
        ///         initializer_list means that the set can be initialized
        ///         with curly braces ({Color 1, Color 2, etc. })
        Text(Pair location, string message, Font* font,
             initializer_list<Color> colors);
        /// \brief A constructor for colored Text
        /// \param location the screen location
        /// \param message the string to be rendered
        /// \font the font to use
        /// \color the Text color
        Text(Pair location, string message, Font* font, Color color);
        /// \brief The default constructor
        ///
        /// Text objects constructed with the default constructor cannot be
        /// painted.
        Text();
        /// \brief The copy constructor
        /// \param other another Text object
        Text(const Text& other);
        /// \brief Paints the text to the screen
        /// \param game the game
        void paint(Game* game);
        /// \brief Retrieves the string being rendered
        /// \return the string being rendered
        string getMessage();
        /// \brief Modifies the string being rendered
        /// \param message the desired string to be rendered
        void setMessage(string message);
        /// \brief Retrieves the color pattern
        /// \return the color pattern of the text (can be a set of one color if
        ///         the text is of a single color
        vector<Color> getColors();
        /// \brief Modifies the color pattern
        /// \param colors the desired set of colors; each color in the set is
        ///        assigned to one letter in order, if the set of colors is too
        ///        small for the whole message, the color pattern repeats
        void setColors(vector<Color> colors);
        /// \brief Modifies the color pattern
        /// \param colors the desired set of colors; each color in the set is
        ///        assigned to one letter in order, if the set of colors is too
        ///        small for the whole message, the color pattern repeats; the
        ///        use of an initializer_list means that the set can be
        ///        initialized with curly braces ({Color 1, Color 2, etc})
        void setColors(initializer_list<Color> colors);
        /// \brief Modifies the color of the text
        /// \color the desired color
        void setColor(Color color);
    protected:
        string message_;
        Font* font_;
        vector<Image> images_;
        vector<Pair> offsets_;
        vector<Color> colors_;
    };
}
#endif
