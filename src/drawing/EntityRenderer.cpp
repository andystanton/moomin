#include "drawing/EntityRenderer.hpp"

EntityRenderer::EntityRenderer(const set<Entity *>& entities)
    : entities(entities)
{
    glGenBuffers(1, &vertexBufferAABB);
    glGenBuffers(1, &vertexBufferCircle);

    glGenVertexArrays(1, &vertexArrayIdAABB);
    glBindVertexArray(vertexArrayIdAABB);

    glGenVertexArrays(1, &vertexArrayIdCircle);
    glBindVertexArray(vertexArrayIdCircle);

    programId = LoadShaders("EntityVertexShader.vertexshader", "EntityFragmentShader.fragmentshader");

    matrixId = glGetUniformLocation(programId, "MVP");

    colourIdCircle = glGetUniformLocation(programId, "uniformColour");
    colourIdAABB = glGetUniformLocation(programId, "uniformColour");
}

EntityRenderer::~EntityRenderer()
{
    glDeleteBuffers(1, &vertexBufferAABB);
    glDeleteBuffers(1, &vertexBufferCircle);

    glDeleteVertexArrays(1, &vertexArrayIdAABB);
    glDeleteVertexArrays(1, &vertexArrayIdCircle);

    glDeleteProgram(programId);
}

void EntityRenderer::draw(glm::mat4 MVP)
{
    for (auto entity : entities)
    {
        draw(entity, MVP);
    }
}

void EntityRenderer::draw(Entity* entity, glm::mat4 MVP)
{

    if (entity->getCollisionType() == Entity::CollisionType::aabb)
    {
        glUseProgram(programId);

        glUniform3f(colourIdCircle, 0.8f, 0.7f, 0.3f);
        glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP[0][0]);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferAABB);

        AABB * aabb = static_cast<AABB *>(entity);
        Vec2 pos = aabb->getPos();
        Vec2 bounding = aabb->getBounding();

        GLfloat vertexBufferData[] = {
            pos.getX(), pos.getY(),
            pos.getX(), pos.getY() + bounding.getY(),
            pos.getX() + bounding.getX(), pos.getY() + bounding.getY(),
            pos.getX(), pos.getY(),
            pos.getX() + bounding.getX(), pos.getY() + bounding.getY(),
            pos.getX() + bounding.getX(), pos.getY(),
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            2,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
        glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

        glDisableVertexAttribArray(0);
    } else if(entity->getCollisionType() == Entity::CollisionType::circle)
    {
        glUseProgram(programId);

        glUniform3f(colourIdCircle, 0.4f, 0.8f, 0.4f);
        glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP[0][0]);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferCircle);

        Circle * circle = static_cast<Circle *>(entity);
        Vec2 pos = circle->getPos();
        float radius = circle->getRadius();

        int numSegments = 36;
        float segmentAngle = 360 / numSegments;

        GLfloat vertexBufferData[78];
        vertexBufferData[0] = pos.getX();
        vertexBufferData[1] = pos.getY();

        int j = 3;
        for (int i = -1; i < numSegments; i++, j++)
        {
            float angle = i * segmentAngle;

            vertexBufferData[i + j] = pos.getX() + sin(angle * M_PI / 180) * radius;
            vertexBufferData[i + j + 1] = pos.getY() + cos(angle * M_PI / 180) * radius;
        }

        vertexBufferData[76] = pos.getX();
        vertexBufferData[77] = pos.getY();

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            2,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
        glDrawArrays(GL_TRIANGLE_FAN, 0, 76); // 3 indices starting at 0 -> 1 triangle
    }
}

void EntityRenderer::handleResize(int width, int height)
{

}
