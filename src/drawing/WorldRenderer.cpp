#include "drawing/WorldRenderer.hpp"

WorldRenderer::WorldRenderer(const set<Entity *>& entities, int width, int height)
    : entities(entities)
    , width(width)
    , height(height)
{
    lookAt(Vec2::ORIGIN, Vec2(width, height));

    glGenBuffers(1, &vertexBufferGrid);
    glGenBuffers(1, &vertexBufferAABB);
    glGenBuffers(1, &vertexBufferCircle);

    glGenVertexArrays(1, &vertexArrayIdGrid);
    glBindVertexArray(vertexArrayIdGrid);

    glGenVertexArrays(1, &vertexArrayIdAABB);
    glBindVertexArray(vertexArrayIdAABB);

    glGenVertexArrays(1, &vertexArrayIdCircle);
    glBindVertexArray(vertexArrayIdCircle);

    programId = LoadShaders("EntityVertexShader.vertexshader", "EntityFragmentShader.fragmentshader");

    matrixId = glGetUniformLocation(programId, "MVP");
    colourId = glGetUniformLocation(programId, "uniformColour");
    offsetId = glGetUniformLocation(programId, "offset");
}

void WorldRenderer::lookAt(Vec2 bottomLeft, Vec2 topRight)
{
    Projection = glm::ortho(bottomLeft.getX(), topRight.getX(), bottomLeft.getY(), topRight.getY(), 0.0f, 1.f); // In world coordinates

    View = glm::lookAt(
        glm::vec3(0,0,1), // Camera is at (0,0,1), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix : an identity matrix (model will be at the origin)
    Model = glm::mat4(1.0f);

    // Our ModelViewProjection : multiplication of our 3 matrices
    MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around
}

WorldRenderer::~WorldRenderer()
{
    glDeleteBuffers(1, &vertexBufferGrid);
    glDeleteBuffers(1, &vertexBufferAABB);
    glDeleteBuffers(1, &vertexBufferCircle);

    glDeleteVertexArrays(1, &vertexArrayIdGrid);
    glDeleteVertexArrays(1, &vertexArrayIdAABB);
    glDeleteVertexArrays(1, &vertexArrayIdCircle);

    glDeleteProgram(programId);
}

void WorldRenderer::setZoom(Vec2 * lowerLeft, Vec2 * upperRight)
{
    this->zoomLowerLeft = lowerLeft;
    this->zoomUpperRight = upperRight;
}

void WorldRenderer::drawView()
{
    glUniform2f(offsetId, 0.f, 0.f);
    glUniform3f(colourId, 1.f, 1.f, 1.f);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferAABB);

    float points[8] = {
        zoomLowerLeft->getX(), zoomLowerLeft->getY(),
        zoomLowerLeft->getX(), zoomUpperRight->getY(),
        zoomUpperRight->getX(), zoomUpperRight->getY(),
        zoomUpperRight->getX(), zoomLowerLeft->getY()
    };

    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), points, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        2,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void WorldRenderer::drawGrid(int spacing)
{
    glUniform2f(offsetId, 0.f, 0.f);
    glUniform3f(colourId, 0.4f, 0.4f, 0.4f);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferGrid);

    int numLinesHorizontal = (width / spacing);
    int numLinesVertical = (height / spacing);

    int numVertices = numLinesVertical * 2 + numLinesHorizontal * 2;

    float points[numVertices * 2];
    for (int i = 0; i < numLinesHorizontal; i++)
    {
        points[i*4] = (i+1) * spacing;
        points[i*4+1] = 0.f;
        points[i*4+2] = (i+1) * spacing;
        points[i*4+3] = height;
    }
    int offset = (numLinesHorizontal-1) * 4;
    for (int j = 0; j < numLinesVertical; j++)
    {
        points[offset + j*4] = 0.f;
        points[offset + j*4+1] = (j + 1) * spacing;
        points[offset + j*4+2] = width;
        points[offset + j*4+3] = (j + 1) * spacing;
    }

    glBufferData(GL_ARRAY_BUFFER, numVertices * 2 * sizeof(float), points, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        2,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    glDrawArrays(GL_LINES, 0, numVertices);
}

void WorldRenderer::draw()
{
    glUseProgram(programId);
    glEnableVertexAttribArray(0);
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP[0][0]);

    drawGrid(200);

    for (auto entity : entities)
    {
        draw(entity);
    }

    glDisableVertexAttribArray(0);
}

void WorldRenderer::draw(Entity* entity)
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
