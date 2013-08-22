// ------------------------------------------------------------------------------------------------
// File:			Text.h
// Author:			Will O'Leary
// Documentation:   https://github.com/wolearyc/wick/wiki/class-Text
//-------------------------------------------------------------------------------------------------

#ifndef TEXT_H
#define TEXT_H
#include <string>
#include "Color.h"
#include "Direct3D.h"
#include "Font.h"
#include "Paintable.h"
#include "Rotateable.h"
#include "Scaleable.h"
namespace wick
{
	class Text : public Paintable, public Rotateable, public Scaleable
	{
	public:

		static const int ID = 2;

		// Constructors.
		Text(string message, Pair location, Font* font, Color color);
		Text(const Text& other);
		Text();

		// Paints Text to screen.
		void paint(Graphics* graphics);

		// Message methods.
		string getMessage();
		void setMessage(string text);

		// Font methods.
		Font* getFont();
		void setFont(Font* font);

		// Returns dimensions.
		Pair getDimensions();

		// Color methods.
		Color getColor();
		void setColor(Color color);

		// Modifies location.
		void setLocation(Pair location);

		// Modifies scale.
		void setScale(Pair scale);

		// Rotation methods.
		void setRotation(double rotation);
		void setRotationInDegrees(double rotation);

		// Center methods.
		void setCenter(Pair center);
		void paintCentered(bool paintCentered);

		// DirectX methods.
		const D3DXMATRIX* getMatrix();
		RECT* getDirectXLocation();

	protected:

		string message_;
		Font* font_;
		Color color_;
		Pair dimensions_;

		// DirectX.
		RECT dlocation_;
		D3DXMATRIX matrix_;
		D3DXVECTOR2 dscale_;
		D3DXVECTOR2 dcenter_;

	};
}
#endif
