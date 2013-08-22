// ------------------------------------------------------------------------------------------------
// File:			Texture.h
// Author:			Will O'Leary
// Documentation:   https://github.com/wolearyc/wick/wiki/class-Texture
//-------------------------------------------------------------------------------------------------

#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include "Direct3D.h"
#include "Graphics.h"
#include "Releaseable.h"
#include "WickError.h"
using std::string;
namespace wick
{
	class Texture : public Releaseable
	{
	public:

		// Constructors.
		Texture(string absoluteFilePath, Graphics* graphics);
		Texture(const Texture& other);
		Texture();

		// Returns DirectX data.
		LPDIRECT3DTEXTURE9 getData();

		// Modifies texture.
		void setTexture(string absoluteFilePath, Graphics* graphics);

		// Deallocates texture.
		void release();

	protected:

		LPDIRECT3DTEXTURE9 data_;

	};
}
#endif
