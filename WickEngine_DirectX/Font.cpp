// ------------------------------------------------------------------------------------------------
// File:			Font.cpp
//-------------------------------------------------------------------------------------------------

#include "Font.h"
namespace wick
{
	vector<string> Font::installedFonts;

	// Constructors.
	Font::Font(string absoluteFilePath, string name, int point, Graphics* graphics)
	{
		if(absoluteFilePath.length() != 0)
		{
			int result = AddFontResource(absoluteFilePath.c_str());
			if(result == 0)
			{
				wickThrowError(absoluteFilePath+" is invalid.");
			}
			installedFonts.push_back(absoluteFilePath);
		}
		D3DXCreateFont(graphics->device_, point, 0, false, false, FALSE, DEFAULT_CHARSET,
					   OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH
					   | FF_DONTCARE, name.c_str(), &data_);
		height_ = point;
		TEXTMETRICW metrics;
		data_->GetTextMetricsW(&metrics);
		averageWidth_ = metrics.tmAveCharWidth;
	}
	Font::Font(string absoluteFilePath, string name, int point, bool bold, bool italic,
			   Graphics* graphics)
	{
		if(absoluteFilePath.length() != 0)
		{
			int result = AddFontResource(absoluteFilePath.c_str());
			if(result == 0)
			{
				wickThrowError(absoluteFilePath+" is invalid.");
			}
			installedFonts.push_back(absoluteFilePath);
		}
		D3DXCreateFont(graphics->device_, point, 0, bold, italic, FALSE, DEFAULT_CHARSET,
					   OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH
					   | FF_DONTCARE, name.c_str(), &data_);
		height_ = point;
		TEXTMETRICW metrics;
		data_->GetTextMetricsW(&metrics);
		averageWidth_ = metrics.tmAveCharWidth;
	}
	Font::Font(const Font& other)
	{
		data_ = other.data_;
	}
	Font::Font()
	{
		data_ = NULL;
	}

	// Deallocates font.
	void Font::release()
	{
		data_->Release();
	}

	// Returns DirectX data.
	LPD3DXFONT Font::getData()
	{
		return(data_);
	}

	// Returns height.
	int Font::getHeight()
	{
		return(height_);
	}

	// Returns average character width.
	int Font::getWidth()
	{
		return(averageWidth_);
	}
}
