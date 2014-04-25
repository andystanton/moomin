#include "drawing/GLHandler.h"
#include "drawing/EntityRenderer.h"
#include "drawing/FreeTypeRenderer.h"

#include "drawing/Text.h"
#include "drawing/FontProvider.h"

int main(void) 
{  
    GLHandler::init();

    vector<Entity *> * entities = new vector<Entity *>();

    EntityRenderer er = EntityRenderer(entities);
    FreeTypeRenderer fr = FreeTypeRenderer();

    GLHandler::registerRenderer(&er);
    GLHandler::registerRenderer(&fr);

    // create something to draw
    Mesh squareMesh 
    {
        -10.0, 10.0,
        -10.0,-10.0,
         10.0, 10.0,
         10.0,-10.0
    };
    Entity e = Entity(320, 240, squareMesh);    
    entities->push_back(&e);

    Text t1 = Text("some text", 350, 650, FontProvider::FontFamily::ObelixPro, 16, Text::Colour::GREEN);
    Text t2 = Text("more text",   0,   0, FontProvider::FontFamily::Vera,      64, Text::Colour::RED);
    Text t3 = Text("some text", 350, 600, FontProvider::FontFamily::ObelixPro, 32, Text::Colour::GREEN);
    Text t4 = Text("some text", 350, 500, FontProvider::FontFamily::ObelixPro, 64, Text::Colour::GREEN);
    fr.addText(&t1);
    fr.addText(&t2);
    fr.addText(&t3);
    fr.addText(&t4);

    while (GLHandler::isActive()) 
    {
        GLHandler::draw();
    }
    
    GLHandler::quit();
    return 0;
}
