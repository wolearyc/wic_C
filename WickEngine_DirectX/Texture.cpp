// ------------------------------------------------------------------------------------------------
// File:			Texture.cpp
//-------------------------------------------------------------------------------------------------

#include "Texture.h"
namespace wick
{
	// Constructors.
	Texture::Texture(string absoluteFilePath, Graphics* graphics)
	{
		HRESULT result = D3DXCreateTextureFromFile(graphics->device_,absoluteFilePath.c_str(),
												   &data_);
		if(result == D3DERR_NOTAVAILABLE || result == D3DXERR_INVALIDDATA)
		{
			wickThrowError(absoluteFilePath+" is invalid.");
		}
		if(result == D3DERR_OUTOFVIDEOMEMORY || result == E_OUTOFMEMORY)
		{
			wickThrowError("Out of memory.");
		}
	}
	Texture::Texture(const Texture& other)
	{
		data_ = other.data_;
	}
	Texture::Texture()
	{
		data_ = NULL;
	}

	// Returns DirectX data.
	LPDIRECT3DTEXTURE9 Texture::getData()
	{
		return(data_);
	}

	// Modifies texture.
	void Texture::setTexture(string absoluteFilePath, Graphics* graphics)
	{
		HRESULT result = D3DXCreateTextureFromFile(graphics->device_,absoluteFilePath.c_str(),
												   &data_);
		if(result == D3DERR_NOTAVAILABLE || result == D3DXERR_INVALIDDATA)
		{
			wickThrowError(absoluteFilePath+" is invalid.");
		}
		if(result == D3DERR_OUTOFVIDEOMEMORY || result == E_OUTOFMEMORY)
		{
			wickThrowError("Out of memory.");
		}
	}

	// Deallocates texture.
	void Texture::release()
	{
		data_->Release();
	}
}
