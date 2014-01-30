// ------------------------------------------------------------------------------------------------
// File:            Font.cpp
// ------------------------------------------------------------------------------------------------

#include "Font.h"
namespace wick
{
    Font::Font(string filePath, unsigned short point)
    {
        FT_Library library;
        FT_Init_FreeType(&library);
        FT_New_Face(library, filePath.c_str(), 0, &face_);
    }
    Font::Font(const Font& other)
    {
    }
    Font::Font()
    {
    }
    Font::~Font()
    {
    }
}
