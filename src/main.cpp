#include "drawing/GLHandler.h"
#include "drawing/EntityRenderer.h"
#include "drawing/FreeTypeRenderer.h"

#include "drawing/Text.h"

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

    Text t1 = Text("some text", 350, 650, Text::Font::ObelixPro, Text::Colour::GREEN);
    Text t2 = Text("more text",   0,   0, Text::Font::Vera,      Text::Colour::RED);

    fr.addText(&t1);
    fr.addText(&t2);

    while (GLHandler::isActive()) 
    {
        // fr.drawText("some text", 350, 650, Text::Font::ObelixPro, Text::Colour::GREEN);
        // fr.drawText("more text",   0,   0, Text::Font::Vera,      Text::Colour::RED);
        GLHandler::draw();
    }
    
    GLHandler::quit();
    return 0;
}
