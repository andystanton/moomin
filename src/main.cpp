#include "drawing/GLFWGLHandler.h"
#include "drawing/EntityRenderer.h"

#include "model/StandardPhysicsSystem.h"
#include "model/PhysicsHelper.h"

using namespace std;



int main( void )
{
    int width = 800, height = 600;

    // Create Physics System
    StandardPhysicsSystem physicsSystem(width * 10, height * 10);
    PhysicsHelper physicsHelper(physicsSystem);

    // Initialise Graphics System
    GLFWGLHandler glHandler("Moomin Engine v1.0", width, height, physicsHelper);

    // Create Renderers
    EntityRenderer er(physicsSystem.getEntities());

    // Register Renderers with Graphics System
    glHandler.setEntityRenderer(&er);

    GLFWwindow* window = glHandler.getWindow();


	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("AABBVertexShader.vertexshader", "AABBFragmentShader.fragmentshader" );

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // Moomin!
    float lastUpdate = glHandler.getTime();
    while (glHandler.isActive())
    {
        //glHandler.draw();

        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT );

        // Use our shader
        glUseProgram(programID);

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
        glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

        glDisableVertexAttribArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        float time = glHandler.getTime();
        physicsSystem.step(1000 * (time - lastUpdate));
        lastUpdate = time;
    }

	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

    glHandler.quit();

    return 0;
}
