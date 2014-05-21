#ifndef _MOOMIN_GL_HANDLER
#define _MOOMIN_GL_HANDLER

#include <set>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <freetype-gl.h>
#include <GLFW/glfw3.h>

#include "model/PhysicsSystem.h"
#include "model/Circle.h"
#include "model/AABB.h"

#include "drawing/Renderer.h"
#include "drawing/FreeTypeRenderer.h"
#include "drawing/EntityRenderer.h"
#include "drawing/Text.h"
#include "drawing/FontProvider.h"

using std::set;
using std::stringstream;
using std::setprecision;
using std::fixed;
using std::cout;
using std::cerr;
using std::endl;

namespace GLHandler
{   
    GLFWwindow * window;
    set<Renderer *> renderers;

    FreeTypeRenderer * freeTypeRenderer = nullptr;
    EntityRenderer * entityRenderer = nullptr;

    PhysicsSystem * physicsSystem;
    
    string titleString;
    string fpsString;

    int width, height;

    int   frameCount    = 0;
    float lastFpsUpdate = 0;
    float fps           = 0;

    bool physics = true;

    void recalculateFps()
    {
        frameCount++;
        float currentTime = glfwGetTime();

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

    void registerRenderer(Renderer * renderer)
    {
        renderers.insert(renderer);
        renderer->handleResize(width, height);
    }

    void registerPhysicsSystem(PhysicsSystem * newPhysicsSystem)
    {
        physicsSystem = newPhysicsSystem;
    }

    void setFreeTypeRenderer(FreeTypeRenderer * newFreeTypeRenderer)
    {
        freeTypeRenderer = newFreeTypeRenderer;
        registerRenderer(freeTypeRenderer);

        Text * fpsText = new Text(fpsString, width/2 - 42, height/2 - 15, FontProvider::FontFamily::VeraMono, 32, Text::Colour::WHITE);
        Text * titleText = new Text(titleString, 4, height/2 - 15, FontProvider::FontFamily::VeraMono, 32, Text::Colour::WHITE);

        freeTypeRenderer->addText(titleText);
        freeTypeRenderer->addText(fpsText);
    }

    void setEntityRenderer(EntityRenderer * newEntityRenderer)
    {
        entityRenderer = newEntityRenderer;
        registerRenderer(entityRenderer);
    }

    void handleKey(GLFWwindow * window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        {
            physics = !physics;
        }
    }

    double clickStartX, clickStartY;
    double clickEndX, clickEndY;

    void handleClick(GLFWwindow *, int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            glfwGetCursorPos(window, &clickStartX, &clickStartY);
        } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        {
            //Circle * c = new Circle(clickStartX * 10, 6400 - (clickStartY * 10), (rand() % 20) + 20 );
            AABB * c = new AABB(clickStartX * 10, 6400 - (clickStartY * 10), (rand() % 20) + 50, (rand() % 20) + 50);
            glfwGetCursorPos(window, &clickEndX, &clickEndY);

            c->getVelocity().setX(clickEndX - clickStartX);
            c->getVelocity().setY(-(clickEndY - clickStartY));

            physicsSystem->addEntity(c);
        }
    }

    void handleResize(GLFWwindow * window, int windowWidth, int windowHeight)
    {
        glfwGetFramebufferSize(window, &width, &height);

        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION );
        glLoadIdentity();

        glOrtho(0, 6400, 0, 6400, 0, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        for (auto renderer : renderers)
        {
            renderer->handleResize(width, height);
        }
    }

    void init(const string& newTitle, int width, int height) 
    {   
        titleString = string(newTitle);

        if (!glfwInit()) {
            cerr << "Error: Unable to initialise GLFW" << endl;
            exit( EXIT_FAILURE );
        }
        glfwInit();

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        window = glfwCreateWindow(width, height, titleString.c_str(), NULL, NULL);
        if (!window) {
            glfwTerminate();
            cerr << "Error: Unable to create GLFW Window" << endl;
            exit( EXIT_FAILURE );
        }
        
        glfwMakeContextCurrent(window);
        glfwSetWindowSizeCallback(window, GLHandler::handleResize);
        glfwSetKeyCallback(window, GLHandler::handleKey);
        glfwSetMouseButtonCallback(window, GLHandler::handleClick);

        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            cerr << "Error: Unable to initialise GLEW" << endl;
            exit( EXIT_FAILURE );
        }
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glClearColor(0.1, 0.1, 0.1, 1.0);

        handleResize(window, width, height);
    }

    bool isPhysics()
    {
        return physics;
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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        recalculateFps();

        entityRenderer->draw();
        freeTypeRenderer->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

};

#endif