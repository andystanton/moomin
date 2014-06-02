#include "drawing/GLHandler.h"

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

static const GLfloat g_vertex_buffer_data[] = {
     0.f, 10.f, 0.0f,
    10.f, 10.f, 0.0f,
     0.f,  0.f, 0.0f,
    10.f, 10.f, 0.0f,
    10.f,  0.f, 0.0f,
     0.f,  0.f, 0.0f
};

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

    programID = LoadShaders("AABBVertexShader.vertexshader", "AABBFragmentShader.fragmentshader");
    MatrixID = glGetUniformLocation(programID, "MVP");

    Projection = glm::ortho(0.0f,(float)width, 0.0f,(float)height, 0.0f,1.f); // In world coordinates

    View = glm::lookAt(
        glm::vec3(0,0,1), // Camera is at (4,3,3), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix : an identity matrix (model will be at the origin)
    Model = glm::mat4(1.0f);
    // Our ModelViewProjection : multiplication of our 3 matrices
    MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void GLHandler::draw()
{
    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT );

    //recalculateFps();

    // Use our shader
    glUseProgram(programID);

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(0);

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
    glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

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
