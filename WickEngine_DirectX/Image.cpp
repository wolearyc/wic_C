// ------------------------------------------------------------------------------------------------
// File:			Image.cpp
//-------------------------------------------------------------------------------------------------

#include "Image.h"
namespace wick
{
	// Constructors.
	Image::Image(Texture* texture, Pair location, Box bounds)
	{
		initialize(texture, location, bounds, bounds.getLowerRight()-bounds.getUpperLeft(), 0, Pair());
	}
	Image::Image(Texture* texture, Pair location, Box bounds, Pair scale)
	{
		initialize(texture, location, bounds, scale, 0, Pair());
	}
	Image::Image(Texture* texture, Pair location, Box bounds, double rotation)
	{
		initialize(texture, location, bounds, bounds.getLowerRight()-bounds.getUpperLeft(), rotation, Pair());
	}
	Image::Image(Texture* texture, Pair location, Box bounds, Pair scale, double rotation)
	{
		initialize(texture, location, bounds, scale, rotation, Pair());
	}
	Image::Image(Texture* texture, Pair location, Box bounds, double rotation, Pair center)
	{
		initialize(texture, location, bounds, bounds.getLowerRight()-bounds.getUpperLeft(), rotation, center);
	}
	Image::Image(Texture* texture, Pair location, Box bounds, Pair scale, double rotation,
				 Pair center)
	{
		initialize(texture, location, bounds, scale, rotation, center);
	}
	Image::Image(const Image& other) : Paintable(other), Rotateable(other), Scaleable(other)
	{
		texture_ = other.texture_;
		bounds_ = other.bounds_;
		dbounds_ = other.dbounds_;
		dlocation_ = other.dlocation_;
		dscale_ = other.dscale_;
		matrix_ = other.matrix_;
		dcenter_ = other.dcenter_;
	}
	Image::Image() : Paintable(), Rotateable(), Scaleable()
	{
		texture_ = new Texture();
		bounds_ = Box();
		dlocation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// Paints image to screen.
	void Image::paint(Graphics* graphics)
	{
		graphics->images_.push_back(this);
		graphics->ids_.push_back(ID);
	}

	// Modifies location.
	void Image::setLocation(Pair location)
	{
		location_ = location;
		dlocation_.x = (float) (location_.x_);
		dlocation_.y = (float) (location_.y_);
		if(paintCentered_)
		{
			dlocation_.x -= (float) (center_.x_);
			dlocation_.y -= (float) (center_.y_);
		}
		setCenter(center_);
	}

	// Texture methods.
	Texture* Image::getTexture()
	{
		return(texture_);
	}
	void Image::setTexture(Texture* texture)
	{
		texture_ = texture;
	}

	// Bounds methods.
	Box Image::getBounds()
	{
		return(bounds_);
	}
	void Image::setBounds(Box bounds)
	{
		bounds_ = bounds;
		dbounds_.left = (long) (bounds_.getUpperLeft().x_);
		dbounds_.top = (long) (bounds_.getUpperLeft().y_);
		dbounds_.right = (long) (bounds_.getLowerRight().x_);
		dbounds_.bottom = (long) (bounds_.getLowerRight().y_);
	}

	// Modifies scale.
	void Image::setScale(Pair scale)
	{
		Scaleable::setScale(scale);
		dscale_.x = (float) ((dbounds_.right-dbounds_.left)/scale_.x_);
		dscale_.y = (float) ((dbounds_.bottom-dbounds_.top)/scale_.y_);
		D3DXMatrixTransformation2D(&matrix_, &dcenter_, 0.0f, &dscale_, &dcenter_, (float) rotation_,
								   NULL);
	}

	// Rotation methods.
	void Image::setRotation(double rotation)
	{
		Rotateable::setRotation(rotation);
		D3DXMatrixTransformation2D(&matrix_, &dcenter_, 0.0f, &dscale_, &dcenter_, (float) rotation_,
								   NULL);
	}
	void Image::setRotationInDegrees(double rotation)
	{
		Rotateable::setRotationInDegrees(rotation);
		D3DXMatrixTransformation2D(&matrix_, &dcenter_, 0.0f, &dscale_, &dcenter_, (float) rotation_,
								   NULL);
	}

	// Center methods.
	void Image::setCenter(Pair center)
	{
		Rotateable::setCenter(center);
		dcenter_.x = dlocation_.x + center_.x_;
		dcenter_.y = dlocation_.y + center_.y_;
		D3DXMatrixTransformation2D(&matrix_, &dcenter_, 0.0f, &dscale_, &dcenter_, (float) rotation_,
								   NULL);
	}
	void Image::paintCentered(bool paintCentered)
	{
		Rotateable::paintCentered(paintCentered);
		setLocation(location_);
	}

	// DirectX methods.
	const D3DXMATRIX* Image::getMatrix()
	{
		return(&matrix_);
	}
	const D3DXVECTOR3* Image::getDirectXLocation()
	{
		return(&dlocation_);
	}
	const RECT* Image::getDirectXBounds()
	{
		return(&dbounds_);
	}

	// Initializes image.
	void Image::initialize(Texture* texture, Pair location, Box bounds, Pair scale, double rotation,
						   Pair center)
	{
		paintCentered_ = false;
		setTexture(texture);
		center_ = center;
		setLocation(location);
		dlocation_.z = 0.0f;
		setBounds(bounds);

		Scaleable::setScale(scale);
		bounds_ = bounds;
		dscale_.x = (float) scale_.x_/(dbounds_.right-dbounds_.left);
		dscale_.y = (float) scale.y_/(dbounds_.bottom-dbounds_.top);

		Rotateable::setRotation(rotation);

		D3DXMatrixTransformation2D(&matrix_, &dcenter_, 0.0f, &dscale_,  &dcenter_, (float) rotation_,
								   NULL);
	}
}

