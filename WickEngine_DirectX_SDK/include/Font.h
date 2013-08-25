// ------------------------------------------------------------------------------------------------
// File:			Font.h
// Author:			Will O'Leary
// Documentation:   https://github.com/wolearyc/wick/wiki/class-Font
//-------------------------------------------------------------------------------------------------

#ifndef FONT_H
#define FONT_H
#include <string>
#include <vector>
#include "Direct3D.h"
#include "Graphics.h"
#include "Releaseable.h"
#include "WickError.h"
using std::string;
using std::vector;
namespace wick
{
	class Font : public Releaseable
	{
	public:

		static vector<string> installedFonts;

		// Constructors.
		Font(string absoluteFilePath, string name, int point, Graphics* graphics);
		Font(string absoluteFilePath, string name, int point, bool bold, bool italic,
			 Graphics* graphics);
		Font(const Font& other);
		Font();

		// Deallocates font.
		void release();

		// Returns DirectX data.
		LPD3DXFONT getData();

		// Returns height.
		int getHeight();

		// Returns average character width.
		int getWidth();

	protected:

		LPD3DXFONT data_;
		int height_;
		int averageWidth_;
	};
}
#endif
