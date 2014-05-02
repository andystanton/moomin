#ifndef _MOOMIN_FONT_PROVIDER
#define _MOOMIN_FONT_PROVIDER

#include <map>
#include <string>
#include <iostream>
#include <freetype-gl.h>

#include "util/PathHelper.h"

using std::map;
using std::pair;
using std::make_pair;
using std::string;
using std::cout;
using std::endl;

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

    texture_font_t * getFont(FontProvider::FontFamily, int size);

    static FontProvider & getInstance()
    {
        static FontProvider fontProvider;
        return fontProvider;
    }

protected:
    FontProvider();
    FontProvider(const FontProvider&);
    FontProvider& operator=(const FontProvider&); 
    ~FontProvider();

private:
    void initFontLocations();
    texture_font_t * addFont(FontProvider::FontFamily, int size);

    map<FontProvider::FontFamily, string> fontLocations;
    map<FontProvider::FontFamily, map<int, texture_font_t *>> fontMap;
    texture_atlas_t * atlas;

    PathHelper pathHelper;
};

#endif
