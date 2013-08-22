// ------------------------------------------------------------------------------------------------
// File:			Rotateable.cpp - Source file for Rotateable.
//-------------------------------------------------------------------------------------------------

#include "Rotateable.h"
namespace wick
{
	// Constructors.
	Rotateable::Rotateable()
	{
		rotation_ = 0.0;
		center_ = Pair();
		paintCentered_ = false;
	}
	Rotateable::Rotateable(const Rotateable &other)
	{
		rotation_ = other.rotation_;
		center_ = other.center_;
		paintCentered_ = other.paintCentered_;
	}

	// Destructor.
	Rotateable::~Rotateable()
	{
	}

	// Rotation metods.
	double Rotateable::getRotation()
	{
		return(rotation_);
	}
	double Rotateable::getRotationInDegrees()
	{
		return(rotation_/0.01745);
	}
	void Rotateable::setRotation(double rotation)
	{
		rotation_ =rotation;
	}
	void Rotateable::setRotationInDegrees(double rotation)
	{
		rotation_ = rotation * 0.01745;
	}

	// Center methods.
	Pair Rotateable::getCenter()
	{
		return(center_);
	}
	void Rotateable::setCenter(Pair center)
	{
		center_ = center;
	}
	void Rotateable::paintCentered(bool paintCentered)
	{
		paintCentered_ = paintCentered;
	}
}
