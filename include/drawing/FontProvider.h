#ifndef _MOOMIN_FONT_PROVIDER
#define _MOOMIN_FONT_PROVIDER

#include <map>
#include <string>
#include <freetype-gl.h>

using std::map;
using std::pair;
using std::make_pair;
using std::string;

class FontProvider
{
public:
    enum class FontFamily 
    {
        ObelixPro,
        Vera,
        VeraMono,
        VeraMonoBold,
        VeraMonoItalic,
        VeraMonoBoldItalic
    };

    static FontProvider * getInstance();
    static void destroyInstance();

    texture_font_t * getFont(FontProvider::FontFamily, int size);

private:
    FontProvider();
    ~FontProvider();
    
    void initFontLocations();
    texture_font_t * addFont(FontProvider::FontFamily, int size);

    map<FontProvider::FontFamily, string> fontLocations;
    map<FontProvider::FontFamily, map<int, texture_font_t *>> fontMap;
    texture_atlas_t * atlas;

    static FontProvider * singleton;
};

#endif
