#include "drawing/EntityRenderer.hpp"

EntityRenderer::EntityRenderer(const set<Entity *>& entities, int width, int height)
    : entities(entities)
{
    Projection = glm::ortho(0.0f,(float)width * 10, 0.0f,(float)height * 10, 0.0f,1.f); // In world coordinates

    View = glm::lookAt(
        glm::vec3(0,0,1), // Camera is at (0,0,1), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix : an identity matrix (model will be at the origin)
    Model = glm::mat4(1.0f);

    // Our ModelViewProjection : multiplication of our 3 matrices
    MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

    glGenBuffers(1, &vertexBufferAABB);
    glGenBuffers(1, &vertexBufferCircle);

    glGenVertexArrays(1, &vertexArrayIdAABB);
    glBindVertexArray(vertexArrayIdAABB);

    glGenVertexArrays(1, &vertexArrayIdCircle);
    glBindVertexArray(vertexArrayIdCircle);

    programId = LoadShaders("EntityVertexShader.vertexshader", "EntityFragmentShader.fragmentshader");
    matrixId = glGetUniformLocation(programId, "MVP");

    colourId = glGetUniformLocation(programId, "uniformColour");
}

EntityRenderer::~EntityRenderer()
{
    glDeleteBuffers(1, &vertexBufferAABB);
    glDeleteBuffers(1, &vertexBufferCircle);

    glDeleteVertexArrays(1, &vertexArrayIdAABB);
    glDeleteVertexArrays(1, &vertexArrayIdCircle);

    glDeleteProgram(programId);
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
    glUseProgram(programId);
    glEnableVertexAttribArray(0);
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP[0][0]);

    if (entity->getCollisionType() == Entity::CollisionType::aabb)
    {
        glUniform3f(colourId, 0.8f, 0.7f, 0.3f);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferAABB);

        AABB * aabb = static_cast<AABB *>(entity);
        Vec2 pos = aabb->getPos();
        Vec2 bounding = aabb->getBounding();

        // todo: create vector and translate properly
        float * mesh = aabb->getMesh().getPoints();
        int meshSize = aabb->getMesh().getSize();

        float * posMesh = new float[meshSize];
        for (int i = 0; i < meshSize; i+=2)
        {
            posMesh[i] = mesh[i] + pos.getX();
            posMesh[i+1] = mesh[i+1] + pos.getY();
        }

        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, posMesh, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            2,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
        glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle
    } else if(entity->getCollisionType() == Entity::CollisionType::circle)
    {
        glUniform3f(colourId, 0.4f, 0.8f, 0.4f);

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

    glDisableVertexAttribArray(0);
}

void EntityRenderer::handleResize(int width, int height)
{

}
