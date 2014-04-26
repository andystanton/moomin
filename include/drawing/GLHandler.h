#ifndef _MOOMIN_GL_HANDLER
#define _MOOMIN_GL_HANDLER

#include <set>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <freetype-gl.h>
#include <GLFW/glfw3.h>

#include "drawing/Renderer.h"
#include "drawing/FreeTypeRenderer.h"
#include "drawing/Text.h"
#include "drawing/FontProvider.h"

using std::cerr;
using std::endl;
using std::set;

namespace GLHandler
{   
    GLFWwindow * window;
    set<Renderer *> renderers;
    FreeTypeRenderer * freeTypeRenderer = nullptr;
    Text * fpsText;

    int width, height;

    float lastUpdate = 0;
    int frameCount = 0;

    void registerRenderer(Renderer * renderer)
    {
        renderers.insert(renderer);
        renderer->handleResize(width, height);
    }

    void setFreeTypeRenderer(FreeTypeRenderer * newFreeTypeRenderer)
    {
        freeTypeRenderer = newFreeTypeRenderer;
        registerRenderer(freeTypeRenderer);

        fpsText = new Text("0", width/2 - 42, height/2 - 15, FontProvider::FontFamily::VeraMono, 32, Text::Colour::WHITE);
        freeTypeRenderer->addText(fpsText);
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

    void draw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1, 0.1, 0.1, 1.0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        frameCount++;
        float currentTime = glfwGetTime();
        float fps;

        if (currentTime - lastUpdate >= 0.5)
        {
            fps = frameCount / (currentTime - lastUpdate);
            lastUpdate = currentTime;
            frameCount = 0;
        }

        std::stringstream fpsStream;
        fpsStream << std::setprecision(1) << std::fixed << fps;


        fpsText->setText(fpsStream.str());

        for (auto renderer : renderers)
        {
            renderer->draw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

};

#endif