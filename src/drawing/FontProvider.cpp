#include "drawing/FontProvider.h"

FontProvider::FontProvider()
    : fontMap()
    , fontLocations()
{
    atlas = texture_atlas_new(1024, 1024, 1);
    initFontLocations();
}

FontProvider::~FontProvider()
{
    // TODO: delete fonts
}

FontProvider * FontProvider::singleton = nullptr;

FontProvider * FontProvider::getInstance()
{
    if (singleton == nullptr)
    {
        singleton = new FontProvider();
    }
    return singleton;
}

void FontProvider::destroyInstance()
{
    if (singleton != nullptr)
    {
        delete singleton;
        singleton = nullptr;
    }
}

texture_font_t * FontProvider::getFont(FontProvider::FontFamily family, int size)
{
    texture_font_t * font;

    map<FontProvider::FontFamily, map<int, texture_font_t *>>::iterator familyIt = fontMap.find(family);
    if (familyIt == fontMap.end())
    {
        font = addFont(family, size);
    } else
    {
        map<int, texture_font_t *> sizeMap = familyIt->second;
        map<int, texture_font_t *>::iterator sizeIt = sizeMap.find(size);
        if (sizeIt == sizeMap.end())
        {
            font = addFont(family, size);
        }
        else
        {
            font = sizeIt->second;
        }
    }
    return font;
}

texture_font_t * FontProvider::addFont(FontProvider::FontFamily family, int size)
{
    texture_font_t * font = texture_font_new_from_file(atlas, size, fontLocations.at(family).c_str());

    map<FontProvider::FontFamily, map<int, texture_font_t *>>::iterator familyIt = fontMap.find(family);
    map<int, texture_font_t *> sizeMap;
    if (familyIt == fontMap.end())
    {
        sizeMap = map<int, texture_font_t *>();
    } else
    {
        sizeMap = familyIt->second;
    }

    sizeMap[size] = font;
    fontMap[family] = sizeMap;

    return font;
}

void FontProvider::initFontLocations()
{
    fontLocations.insert(make_pair(FontProvider::FontFamily::ObelixPro, "lib/freetype-gl/fonts/ObelixPro.ttf"));
    fontLocations.insert(make_pair(FontProvider::FontFamily::Vera, "lib/freetype-gl/fonts/Vera.ttf"));
    fontLocations.insert(make_pair(FontProvider::FontFamily::VeraMono, "lib/freetype-gl/fonts/VeraMono.ttf"));
    fontLocations.insert(make_pair(FontProvider::FontFamily::VeraMonoBold, "lib/freetype-gl/fonts/VeraMoBd.ttf"));
    fontLocations.insert(make_pair(FontProvider::FontFamily::VeraMonoItalic, "lib/freetype-gl/fonts/VeraMoIt.ttf"));
    fontLocations.insert(make_pair(FontProvider::FontFamily::VeraMonoBoldItalic, "lib/freetype-gl/fonts/VeraMoBI.ttf"));
}