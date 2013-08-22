// ------------------------------------------------------------------------------------------------
// File:			Button.h
// Author:			Will O'Leary
// Documentation:   https://github.com/wolearyc/wick/wiki/class-Button
//-------------------------------------------------------------------------------------------------

#ifndef BUTTON_H
#define BUTTON_H
#include "Input.h"
#include "Image.h"
#include "Updateable.h"
#include "HitBox.h"
namespace wick
{
	class Button : public Paintable, Updateable, Rotateable, Scaleable
	{
	public:

		// Constructors.
		Button(Image off, Image on, Pair location, Box target);
		Button(const Button& other);
		Button();

		// Updates logic.
		void update(Input* input, int fps, Graphics* graphics);

		// Paints Button to screen.
		void paint(Graphics* graphics);

		// Sets location.
		void setLocation(Pair location);

		// Rotation methods.
		void setRotation(double rotation);
		void setRotationInDegrees(double rotation);

		// Sets center.
		void setCenter(Pair center);

		// Sets scale.
		void setScale(Pair scale);

		// Returns whether or not the curser is over the button.
		bool mouseOver();

		// Button press methods.
		bool pressed();
		void setPressed(bool pressed);

	protected:

		Image off_;
		Image on_;
		HitBox target_;
		bool over_;
		bool pressed_;

	};
}
#endif

