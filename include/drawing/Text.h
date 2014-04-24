#ifndef _MOOMIN_TEXT
#define _MOOMIN_TEXT

#include <string>

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

    enum class Font 
    {
        ObelixPro,
        Vera,
        VeraMono,
        VeraMonoBold,
        VeraMonoItalic,
        VeraMonoBoldItalic
    };

    Text(const string& text, 
         int x, 
         int y, 
         Font, 
         Colour);
    ~Text();

    const string& getText();
    int getX();
    int getY();
    Font getFont();
    Colour getColour();
private:
    const string& text;
    int x, y;
    Font font;
    Colour colour;
};

#endif