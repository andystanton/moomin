#ifndef _MOOMIN_GL_HANDLER
#define _MOOMIN_GL_HANDLER

#include <set>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <freetype-gl.h>
#include <GLFW/glfw3.h>

#include "model/PhysicsHelper.h"

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

    PhysicsHelper * physicsHelper;

    string titleString;
    string fpsString;

    int width, height;

    int   frameCount    = 0;
    float lastFpsUpdate = 0;
    float fps           = 0;

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
        if (action == GLFW_PRESS)
        {
            switch (key) {
                case GLFW_KEY_SPACE:
                    physicsHelper->togglePause();
                    break;
                case GLFW_KEY_1:
                    physicsHelper->addCirclesRandom();
                    break;
                case GLFW_KEY_2:
                    physicsHelper->addAABBsRandom();
                    break;
                case GLFW_KEY_3:
                    physicsHelper->addCirclesLatticeCentre();
                    break;
                case GLFW_KEY_4:
                    physicsHelper->addAABBsLatticeCentre();
                    break;
                case GLFW_KEY_5:
                    physicsHelper->addChaosLattice(false);
                    break;
                case GLFW_KEY_6:
                    physicsHelper->addChaosLattice(true);
                    break;
                case GLFW_KEY_0:
                    physicsHelper->disableAccelerationRules();
                    break;
                case GLFW_KEY_LEFT_BRACKET:
                    physicsHelper->enablePositionAccelerationRule(false);
                    break;
                case GLFW_KEY_RIGHT_BRACKET:
                    physicsHelper->enablePositionAccelerationRule(true);
                    break;
                case GLFW_KEY_O:
                    physicsHelper->enableEntityAccelerationRule(false);
                    break;
                case GLFW_KEY_P:
                    physicsHelper->enableEntityAccelerationRule(true);
                    break;
                case GLFW_KEY_UP:
                    physicsHelper->enableDirectionAccelerationRule('N');
                    break;
                case GLFW_KEY_DOWN:
                    physicsHelper->enableDirectionAccelerationRule('S');
                    break;
                case GLFW_KEY_LEFT:
                    physicsHelper->enableDirectionAccelerationRule('W');
                    break;
                case GLFW_KEY_RIGHT:
                    physicsHelper->enableDirectionAccelerationRule('E');
                    break;
            }
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
            glfwGetCursorPos(window, &clickEndX, &clickEndY);

            Vec2 pos(clickStartX * 10, physicsHelper->getHeight() - (clickStartY * 10));
            Vec2 bounding(Vec2((rand() % 20) + 50, (rand() % 20) + 50));
            Vec2 velocity(clickEndX - clickStartX, -(clickEndY - clickStartY));

            physicsHelper->addAABB(pos, bounding, velocity);

            // Vec2 pos(clickStartX * 10, physicsHelper->getHeight() - (clickStartY * 10));
            // float radius = (rand() % 20) + 20;
            // Vec2 velocity(clickEndX - clickStartX, -(clickEndY - clickStartY));
            //
            // physicsHelper->addCircle(pos, radius, velocity);
        }
    }

    void handleResize(GLFWwindow * window, int windowWidth, int windowHeight)
    {
        glfwGetFramebufferSize(window, &width, &height);

        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION );
        glLoadIdentity();

        glOrtho(0, physicsHelper->getWidth(), 0, physicsHelper->getHeight(), 0, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        for (auto renderer : renderers)
        {
            renderer->handleResize(width, height);
        }
    }

    void init(const string& newTitle,
              int width,
              int height,
              PhysicsHelper * newPhysicsHelper)
    {
        physicsHelper = newPhysicsHelper;
        physicsHelper->addCirclesLatticeCentre();

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

        glClearColor(0.2, 0.2, 0.5, 1.0);

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        recalculateFps();

        entityRenderer->draw();
        freeTypeRenderer->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

};

#endif
