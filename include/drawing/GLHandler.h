#ifndef _MOOMIN_GL_HANDLER
#define _MOOMIN_GL_HANDLER

#include <vector>
#include <iostream>

#include <freetype-gl.h>
#include <GLFW/glfw3.h>

#include "drawing/Renderer.h"

using std::vector;
using std::cerr;
using std::endl;

namespace GLHandler
{   
    GLFWwindow * window;
    vector<Renderer *> renderers;
    int width, height;

    float lastUpdate = 0;
    int frameCount = 0;

    float fps;

    void registerRenderer(Renderer * renderer)
    {
        renderers.push_back(renderer);
        renderer->handleResize(width, height);
    }

    void handleResize(GLFWwindow * window, int windowWidth, int windowHeight)
    {
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION );
        glLoadIdentity();
        glScalef(1.0, -1.0, 1.0);
        glOrtho(0, windowWidth, windowHeight, 0, 0, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        for (auto renderer : renderers)
        {
            renderer->handleResize(width, height);
        }
    }

    void init() 
    {   
        const int width=640, height=480;

        if (!glfwInit()) {
            cerr << "Error: Unable to initialise GLFW" << endl;
            exit( EXIT_FAILURE );
        }
        glfwInit();

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        window = glfwCreateWindow(width, height, "Moomin", NULL, NULL);
        if (!window) {
            glfwTerminate();
            cerr << "Error: Unable to create GLFW Window" << endl;
            exit( EXIT_FAILURE );
        }
        
        glfwMakeContextCurrent(window);
        glfwSetWindowSizeCallback(window, GLHandler::handleResize);

        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            cerr << "Error: Unable to initialise GLEW" << endl;
            exit( EXIT_FAILURE );
        }

        handleResize(window, width, height);
    }

    bool isActive()
    {
        return !glfwWindowShouldClose(window);
    }

    void quit()
    {
        glfwTerminate();
    }

    float getFps()
    {
        return fps;
    }

    void draw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.109803922, 0.109803922, 0.109803922, 1.0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        frameCount++;
        float currentTime = glfwGetTime();

        if (currentTime - lastUpdate >= 0.5)
        {
            fps = frameCount / (currentTime - lastUpdate);
            std::cout << frameCount / (currentTime - lastUpdate)  << "fps" << endl;
            lastUpdate = currentTime;
            frameCount = 0;
        }

        for (auto renderer : renderers)
        {
            renderer->draw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

};

#endif