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
    Text * titleText;

    int width, height;
    string title;

    int   frameCount    = 0;
    float lastFpsUpdate = 0;
    float fps           = 0;

    
    string fpsToOneDP()
    {
        std::stringstream fpsStream;
        fpsStream << std::setprecision(1) << std::fixed << fps;
        return fpsStream.str();
    }

    void recalculateFps()
    {
        frameCount++;
        float currentTime = glfwGetTime();

        if (currentTime - lastFpsUpdate >= 0.5)
        {
            fps = frameCount / (currentTime - lastFpsUpdate);
            lastFpsUpdate = currentTime;
            fpsText->setText(fpsToOneDP());
            frameCount = 0;
        }
    }

    void registerRenderer(Renderer * renderer)
    {
        renderers.insert(renderer);
        renderer->handleResize(width, height);
    }

    void setFreeTypeRenderer(FreeTypeRenderer * newFreeTypeRenderer)
    {
        freeTypeRenderer = newFreeTypeRenderer;
        registerRenderer(freeTypeRenderer);

        fpsText = new Text(fpsToOneDP(), width/2 - 42, height/2 - 15, FontProvider::FontFamily::VeraMono, 32, Text::Colour::WHITE);
        titleText = new Text(title, 4, height/2 - 15, FontProvider::FontFamily::VeraMono, 32, Text::Colour::WHITE);

        freeTypeRenderer->addText(titleText);
        freeTypeRenderer->addText(fpsText);
    }

    void handleResize(GLFWwindow * window, int windowWidth, int windowHeight)
    {
        glfwGetFramebufferSize(window, &width, &height);

        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION );
        glLoadIdentity();

        glOrtho(0, windowWidth, 0, windowHeight, 0, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        for (auto renderer : renderers)
        {
            renderer->handleResize(width, height);
        }
    }

    void init(const string& newTitle, int width, int height) 
    {   
        title = string(newTitle);

        if (!glfwInit()) {
            cerr << "Error: Unable to initialise GLFW" << endl;
            exit( EXIT_FAILURE );
        }
        glfwInit();

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
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

        recalculateFps();

        for (auto renderer : renderers)
        {
            renderer->draw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

};

#endif