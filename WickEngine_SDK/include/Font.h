// ------------------------------------------------------------------------------------------------
// File:            Font.h
// Author:          Will O'Leary
// Documentation:
// ------------------------------------------------------------------------------------------------

#ifndef FONT_H
#define FONT_H
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
using std::string;
namespace wick
{
    class Font
    {
    public:
        Font(string filePath, unsigned short point);
        Font(const Font& other);
        Font();
        ~Font();

    protected:
        FT_Face face_;
    };
}
#endif
