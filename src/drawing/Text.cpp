#include "drawing/Text.h"

Text::Text(const string& text, 
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

const string& Text::getText()
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

void Text::setText(const string& text)
{
  this->text = string(text);
}