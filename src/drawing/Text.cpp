#include "drawing/Text.h"

Text::Text(const string& text, 
           int x, 
           int y, 
           Font font, 
           Colour colour)
    : text(text)
    , x(x)
    , y(y)
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

int Text::getX()
{
    return x;
}

int Text::getY()
{
    return y;
}

Text::Font Text::getFont()
{
    return font;
}

Text::Colour Text::getColour()
{
    return colour;
}