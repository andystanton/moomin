#include "drawing/Text.h"

Text::Text(string& text, 
           float x, 
           float y, 
           FontProvider::FontFamily font, 
           int size,
           Colour colour)
    : text(text)
    , x(x)
    , y(y)
    , size(size)
    , font(font)
    , colour(colour)
{
}

Text::~Text()
{

}

string& Text::getText()
{
    return text;
}

float Text::getX()
{
    return x;
}

float Text::getY()
{
    return y;
}

int Text::getSize()
{
    return size;
}

FontProvider::FontFamily Text::getFontFamily()
{
    return font;
}

Text::Colour Text::getColour()
{
    return colour;
}

void Text::setText(string& text)
{
  this->text = text;
}