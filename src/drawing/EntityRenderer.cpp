#include "drawing/EntityRenderer.h"

EntityRenderer::EntityRenderer(const set<Entity *>& entities)
    : entities(entities)
{
}

EntityRenderer::~EntityRenderer()
{

}

void EntityRenderer::draw()
{
    for (auto entity : entities)
    {
        draw(entity);
    }
}

void EntityRenderer::draw(Entity* entity) 
{
    const Mesh& mesh = entity->getMesh();
    unique_ptr<float> meshPoints(mesh.getPoints());

    int mode = GL_TRIANGLE_STRIP;
    if (mesh.getType() == Mesh::MeshType::quads) {
        mode = GL_QUAD_STRIP;
    }
    glPushMatrix();
        glTranslatef(entity->getPos().getX(), entity->getPos().getY(), 0);
        glBegin(mode);
            glColor3f(0.f, 1.f, 0.f);
            for(int i = 0; i < mesh.getSize(); i+=2) 
            {
                glVertex2f(meshPoints.get()[i], meshPoints.get()[i+1]);
            }
        glEnd();
    glPopMatrix();
}

void EntityRenderer::handleResize(int width, int height)
{
    
}