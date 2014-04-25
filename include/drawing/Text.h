#ifndef _MOOMIN_TEXT
#define _MOOMIN_TEXT

#include <string>

#include "drawing/FontProvider.h"

using std::string;

class Text
{
public:
    enum class Colour 
    {
        WHITE,
        BLACK,
        RED,
        GREEN,
        BLUE
    };

    Text(const string& text, 
         float x, 
         float y, 
         FontProvider::FontFamily, 
         int size,
         Colour);
    ~Text();

    const string& getText();
    float getX();
    float getY();
    FontProvider::FontFamily getFontFamily();
    int getSize();
    Colour getColour();
private:
    const string& text;
    float x, y;
    int size;
    FontProvider::FontFamily font;
    Colour colour;
};

#endif