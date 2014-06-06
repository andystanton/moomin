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
    offsetId = glGetUniformLocation(programId, "offset");
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

    const Mesh & mesh = entity->getMesh();
    Vec2 pos = entity->getPos();

    if (mesh.getType() == Mesh::MeshType::triangles)
    {
        glUniform3f(colourId, 0.8f, 0.7f, 0.3f);
        glUniform2f(offsetId, pos.getX(), pos.getY());

        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferAABB);

        AABB * aabb = static_cast<AABB *>(entity);
        Vec2 bounding = aabb->getBounding();

        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, aabb->getMesh().getPoints(), GL_DYNAMIC_DRAW);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            2,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
        glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle
    } else if(mesh.getType() == Mesh::MeshType::fan)
    {
        glUniform3f(colourId, 0.4f, 0.8f, 0.4f);
        glUniform2f(offsetId, pos.getX(), pos.getY());

        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferCircle);

        Circle * circle = static_cast<Circle *>(entity);

        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * circle->getMesh().getSize(), circle->getMesh().getPoints(), GL_DYNAMIC_DRAW);

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
