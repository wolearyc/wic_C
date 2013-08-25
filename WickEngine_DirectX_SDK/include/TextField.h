// ------------------------------------------------------------------------------------------------
// File:			TextField.h
// Author:			Will O'Leary
// Documentation:   https://github.com/wolearyc/wick/wiki/class-TextField
//-------------------------------------------------------------------------------------------------

#ifndef TEXTFIELD_H
#define TEXTFIELD_H
#include <string>
#include <sstream>
#include "Input.h"
#include "Text.h"
#include "Image.h"
#include "Updateable.h"
#include "HitBox.h"
using std::string;
namespace wick
{
	class TextField : public Paintable, public Updateable
	{
	public:

		// Constructors.
		TextField(Text text, Image background, Pair location, Pair textOffset, int characters,
				  Box target);
		TextField(const TextField& other);
		TextField();

		// Updates logic.
		void update(Input* input, int fps, Graphics* graphics);

		// Paints TextField to screen.
		void paint(Graphics* graphics);

		// Returns location.
		void setLocation(Pair location);

		// Activation methods.
		void activate();
		void deactivate();
		bool active();

		// Message methods.
		void setMessage(string message);
		string getMessage();

	protected:

		Text text_;
		string message_;
		Image background_;
		Pair offset_;
		unsigned int characters_;
		HitBox target_;
		bool active_;
	};
}
#endif

