// ------------------------------------------------------------------------------------------------
// File:			Image.h
// Author:			Will O'Leary
// Documentation:   https://github.com/wolearyc/wick/wiki/class-Image
//-------------------------------------------------------------------------------------------------

#ifndef IMAGE_H
#define IMAGE_H
#include <vector>
#include "Box.h"
#include "Direct3D.h"
#include "Graphics.h"
#include "Texture.h"
#include "Paintable.h"
#include "Pair.h"
#include "Releaseable.h"
#include "Rotateable.h"
#include "Scaleable.h"
#include "WickError.h"
using std::vector;
namespace wick
{
	class Image : public Paintable, public Rotateable, public Scaleable
	{
	public:

		static const int ID = 0;

		// Constructors.
		Image(Texture* texture, Pair location, Box bounds);
		Image(Texture* texture, Pair location, Box bounds, Pair scale);
		Image(Texture* texture, Pair location, Box bounds, double rotation);
		Image(Texture* texture, Pair location, Box bounds, Pair scale, double rotation);
		Image(Texture* texture, Pair location, Box bounds, double rotation, Pair center);
		Image(Texture* texture, Pair location, Box bounds, Pair scale, double rotation, Pair center);
		Image(const Image& other);
		Image();

		// Paints image to screen.
		void paint(Graphics* graphics);

		// Modifies location.
		void setLocation(Pair location);

		// Texture methods.
		Texture* getTexture();
		void setTexture(Texture* texture);

		// Bounds methods.
		Box getBounds();
		void setBounds(Box bounds);

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
		const D3DXVECTOR3* getDirectXLocation();
		const RECT* getDirectXBounds();

	protected:

		// Initializes image.
		void initialize(Texture* texture, Pair location, Box bounds, Pair scale, double rotation,
						Pair center);
		Texture* texture_;
		Box bounds_;
		RECT dbounds_;
		D3DXVECTOR3 dlocation_;
		D3DXMATRIX matrix_;
		D3DXVECTOR2 dscale_;
		D3DXVECTOR2 dcenter_;

	};
}
#endif
