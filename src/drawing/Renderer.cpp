#include "drawing/Renderer.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::draw(const Entity& entity) {
    entity.getMesh();
}
