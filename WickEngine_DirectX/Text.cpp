// ------------------------------------------------------------------------------------------------
// File:			Text.cpp
//-------------------------------------------------------------------------------------------------

#include "Text.h"
namespace wick
{
	// Constructors.
	Text::Text(string message, Pair location, Font* font, Color color)
	{
		setLocation(location);
		message_ =  message;
		font_ = font;
		color_ = color;
		setScale(getDimensions());
	}
	Text::Text(const Text& other) : Paintable(other), Rotateable(other), Scaleable(other)
	{
		message_ = other.message_;
		font_ = other.font_;
		color_ = other.color_;
		dimensions_ = other.dimensions_;
		dlocation_ = other.dlocation_;
		matrix_ = other.matrix_;
		dscale_ = other.dscale_;
		dcenter_ = other.dcenter_;
	}
	Text::Text() : Paintable(), Rotateable(), Scaleable()
	{
		message_ = "";
		font_ = new Font();
		color_ = Color();
	}

	// Paints text to screen.
	void Text::paint(Graphics* graphics)
	{
		graphics->texts_.push_back(this);
		graphics->ids_.push_back(ID);
	}

	// Message methods.
	string Text::getMessage()
	{
		return(message_);
	}
	void Text::setMessage(string message)
	{
		message_ = message;
	}

	// Font methods.
	Font* Text::getFont()
	{
		return(font_);
	}
	void Text::setFont(Font* font)
	{
		font_ = font;
	}

	// Returns dimensions.
	Pair Text::getDimensions()
	{
		return(Pair(message_.size()*font_->getWidth(),font_->getHeight()));
	}

	// Color methods.
	Color Text::getColor()
	{
		return(color_);
	}
	void Text::setColor(Color color)
	{
		color_ = color;
	}

	// Modifies location.
	void Text::setLocation(Pair location)
	{
		location_ = location;
		dlocation_.left = location_.x_;
		dlocation_.top = location_.y_;
		dlocation_.right = dlocation_.left + 1;
		dlocation_.bottom = dlocation_.top + 1;
		if(paintCentered_)
		{
			dlocation_.left -= center_.x_;
			dlocation_.top -= center_.y_;
		}
		setCenter(center_);
	}

	// Modifies scale.
	void Text::setScale(Pair scale)
	{
		Scaleable::setScale(scale);
		Pair dimensions = getDimensions();
		dscale_.x = (float) (scale.x_/dimensions.x_);
		dscale_.y = (float) (scale.y_/dimensions.y_);
		D3DXMatrixTransformation2D(&matrix_, &dcenter_, 0.0f, &dscale_, &dcenter_, (float) rotation_,
								   NULL);
	}

	// Rotation methods.
	void Text::setRotation(double rotation)
	{
		Rotateable::setRotation(rotation);
		D3DXMatrixTransformation2D(&matrix_, &dcenter_, 0.0f, &dscale_, &dcenter_, (float) rotation_,
								   NULL);
	}
	void Text::setRotationInDegrees(double rotation)
	{
		Rotateable::setRotationInDegrees(rotation);
		D3DXMatrixTransformation2D(&matrix_, &dcenter_, 0.0f, &dscale_, &dcenter_, (float) rotation_,
								   NULL);
	}

	// Center methods.
	void Text::setCenter(Pair center)
	{
		Rotateable::setCenter(center);
		dcenter_.x = (float) dlocation_.left + center_.x_;
		dcenter_.y = (float) dlocation_.top + center_.y_;
		D3DXMatrixTransformation2D(&matrix_, &dcenter_, 0.0f, &dscale_, &dcenter_, (float) rotation_,
								   NULL);
	}
	void Text::paintCentered(bool paintCentered)
	{
		Rotateable::paintCentered(paintCentered);
		setLocation(location_);
	}

	// DirectX methods.
	const D3DXMATRIX* Text::getMatrix()
	{
		return(&matrix_);
	}
	RECT* Text::getDirectXLocation()
	{
		return(&dlocation_);
	}
}
