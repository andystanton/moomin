#include "drawing/GLHandler.hpp"

GLHandler::GLHandler(const string& title,
                     int width,
                     int height,
                     PhysicsHelper & physicsHelper)
    : title(title)
    , width(width)
    , height(height)
    , physicsHelper(physicsHelper)
    , renderers()
    , entityRenderer(nullptr)
    , frameCount(0)
    , lastFpsUpdate(0.f)
    , fps(0.f)
    , fpsString()
{
    glContextHandler = unique_ptr<GLContextHandler>(
        new GLFWContextHandler(title, width, height, physicsHelper)
    );
    init();
}

GLHandler::~GLHandler()
{

}
//
// static const GLfloat g_vertex_buffer_data[] = {
//      0.f, 50.f, 0.0f,
//     50.f, 50.f, 0.0f,
//      0.f,  0.f, 0.0f,
//     50.f, 50.f, 0.0f,
//     50.f,  0.f, 0.0f,
//      0.f,  0.f, 0.0f
// };
//
// static const GLfloat g_vertex_buffer_data2[] = {
//     800.f,         600.f,  0.0f,
//     800.f,         600.f - 50.f, 0.0f,
//     800.f - 50.f,  600.f,  0.0f,
//     800.f,         600.f - 50.f, 0.0f,
//     800.f - 50.f,  600.f - 50.f, 0.0f,
//     800.f - 50.f,  600.f, 0.0f
// };

void GLHandler::init()
{
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        exit(-1);
    }

    glClearColor(0.2, 0.2, 0.5, 1.0);

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glGenVertexArrays(1, &VertexArrayID2);
    glBindVertexArray(VertexArrayID2);

    programID = LoadShaders("AABBVertexShader.vertexshader", "AABBFragmentShader.fragmentshader");
    programID2 = LoadShaders("CircleVertexShader.vertexshader", "CircleFragmentShader.fragmentshader");
    MatrixID = glGetUniformLocation(programID, "MVP");
    MatrixID2 = glGetUniformLocation(programID2, "MVP2");

    Projection = glm::ortho(0.0f,(float)width * 10, 0.0f,(float)height * 10, 0.0f,1.f); // In world coordinates

    View = glm::lookAt(
        glm::vec3(0,0,1), // Camera is at (4,3,3), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix : an identity matrix (model will be at the origin)
    Model = glm::mat4(1.0f);
    // Our ModelViewProjection : multiplication of our 3 matrices
    MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

    glGenBuffers(1, &aabbVertexBuffer);
    glGenBuffers(1, &circleVertexBuffer);
}

void GLHandler::draw()
{
    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT );

    recalculateFps();

    for (auto entity : physicsHelper.getEntities())
    {
        if (entity->getCollisionType() == Entity::CollisionType::aabb)
        {
            glUseProgram(programID);
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, aabbVertexBuffer);

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
            glUseProgram(programID2);
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, circleVertexBuffer);

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

    //entityRenderer->draw();

    glContextHandler->postDraw();
}

void GLHandler::recalculateFps()
{
    frameCount++;
    float currentTime = glContextHandler->getTime();

    if (currentTime - lastFpsUpdate >= 0.5)
    {
        fps = frameCount / (currentTime - lastFpsUpdate);
        lastFpsUpdate = currentTime;

        stringstream fpsStream;
        fpsStream << setprecision(1) << fixed << fps;
        fpsString = fpsStream.str();

        frameCount = 0;
    }
}

void GLHandler::registerRenderer(Renderer * renderer)
{
    renderers.insert(renderer);
    renderer->handleResize(width, height);
}

void GLHandler::setEntityRenderer(EntityRenderer * entityRenderer)
{
    this->entityRenderer = entityRenderer;
    registerRenderer(this->entityRenderer);
}

bool GLHandler::isActive()
{
    return glContextHandler->isActive();
}

double GLHandler::getTime()
{
    return glContextHandler->getTime();
}

void GLHandler::quit()
{
    glDeleteBuffers(1, &aabbVertexBuffer);
    glDeleteBuffers(1, &circleVertexBuffer);

	glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteVertexArrays(1, &VertexArrayID2);

	glDeleteProgram(programID);
    glDeleteProgram(programID2);

    glContextHandler->quit();
}

void GLHandler::resize()
{
    // glViewport(0, 0, width, height);
    // glMatrixMode(GL_PROJECTION );
    // glLoadIdentity();
    //
    // glOrtho(0, physicsHelper.getWidth(), 0, physicsHelper.getHeight(), 0, 1);
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
    //
    // for (auto renderer : renderers)
    // {
    //     renderer->handleResize(width, height);
    // }
}
