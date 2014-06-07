#include "drawing/EntityRenderer.hpp"

EntityRenderer::EntityRenderer(const set<Entity *>& entities, int width, int height)
    : entities(entities)
{
    Projection = glm::ortho(0.0f,(float)width * 10, 0.0f,(float)height * 10, 0.0f, 1.f); // In world coordinates

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
    glUseProgram(programId);
    glEnableVertexAttribArray(0);
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP[0][0]);
    for (auto entity : entities)
    {
        draw(entity);
    }
    glDisableVertexAttribArray(0);
}

void EntityRenderer::draw(Entity* entity)
{
    Vec2 pos = entity->getPos();
    const Mesh & mesh = entity->getMesh();



    glUniform2f(offsetId, pos.getX(), pos.getY());
    glUniform3fv(colourId, 1, entity->getColour());


    GLenum drawMode = GL_INVALID_ENUM;
    if (mesh.getType() == Mesh::MeshType::triangles)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferAABB);
        drawMode = GL_TRIANGLES;
    } else if(mesh.getType() == Mesh::MeshType::fan)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferCircle);
        drawMode = GL_TRIANGLE_FAN;
    }

    glBufferData(GL_ARRAY_BUFFER, mesh.getMemSize(), mesh.getPoints(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        2,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    glDrawArrays(drawMode, 0, mesh.getSize());

}
