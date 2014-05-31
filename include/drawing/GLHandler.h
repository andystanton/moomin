#ifndef _MOOMIN_GL_HANDLER
#define _MOOMIN_GL_HANDLER

#include <set>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <freetype-gl.h>
#include <GLFW/glfw3.h>

#include "model/PhysicsHelper.h"
#include "model/StandardPhysicsSystem.h"
#include "model/Circle.h"
#include "model/AABB.h"

#include "drawing/Renderer.h"
#include "drawing/FreeTypeRenderer.h"
#include "drawing/EntityRenderer.h"
#include "drawing/Text.h"
#include "drawing/FontProvider.h"

#include "model/rules/EntityAccelerationRule.h"
#include "model/rules/DirectionAccelerationRule.h"
#include "model/rules/PositionAccelerationRule.h"

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

    StandardPhysicsSystem * physicsSystem;

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

    Circle * createRandomCircle()
    {
        int worldWidth = 6400, worldHeight = 6400;
        Circle * c = new Circle(rand() % worldWidth, worldHeight/8 + (rand() % (int)(worldHeight * 0.75)), (rand() % 20) + 20);
        c->getVelocity().setX((rand() % 30) - 15);
        c->getVelocity().setY(rand() % 30);
        return c;
    }

    AABB * createRandomAABB()
    {
        int worldWidth = 6400, worldHeight = 6400;
        AABB * aabb = new AABB(rand() % worldWidth, worldHeight/8 + (rand() % (int)(worldHeight * 0.75)), (rand() % 160) + 80, (rand() % 160) + 80);
        aabb->getVelocity().setX((rand() % 30) - 15);
        aabb->getVelocity().setY(rand() % 30);
        return aabb;
    }

    void createCirclesRandom()
    {
        for (int i=0; i < 50; i++)
        {
            physicsSystem->addEntity(createRandomCircle());
        }
    }

    void createAABBsRandom()
    {
        for (int i=0; i < 50; i++)
        {
            physicsSystem->addEntity(createRandomAABB());
        }
    }

    void createCirclesLattice(float x = 2700, float y = 2700, Vec2 velocity = Vec2(0,0))
    {
        float radius = 50;
        float diameter = 2 * radius;
        for (int i=0; i < 10; i++)
        {
            for (int j=0; j < 10; j++)
            {
                Circle * temp = new Circle(x + i * diameter, y + j * diameter, radius);
                temp->getVelocity() = velocity;
                physicsSystem->addEntity(temp);
            }
        }
    }

    void createAABBLattice(float x = 2650, float y = 2650, Vec2 velocity = Vec2(0,0))
    {
        float width = 100;
        float height = width;
        for (int i=0; i < 10; i++)
        {
            for (int j=0; j < 10; j++)
            {
                AABB * temp = new AABB(x + i * width, y + j * height, width, height);
                temp->getVelocity() = velocity;
                physicsSystem->addEntity(temp);
            }
        }
    }

    void createChaosLattice(bool inverted)
    {
        physicsHelper->disableAccelerationRules();
        float speed = 30;
        if (!inverted)
        {
            createCirclesLattice(100, 100, Vec2(speed,speed));
            createAABBLattice(5300, 5300, Vec2(-speed,-speed));
        } else
        {
            createCirclesLattice(100, 5300, Vec2(speed,-speed));
            createAABBLattice(5300, 100, Vec2(-speed,speed));
        }
    }

    void registerPhysicsSystem(StandardPhysicsSystem * newPhysicsSystem, PhysicsHelper * newPhysicsHelper)
    {
        physicsSystem = newPhysicsSystem;
        physicsHelper = newPhysicsHelper;

        createCirclesLattice();
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
                    physicsSystem->clearEntities();
                    createCirclesRandom();
                    break;
                case GLFW_KEY_2:
                    physicsSystem->clearEntities();
                    createAABBsRandom();
                    break;
                case GLFW_KEY_3:
                    physicsSystem->clearEntities();
                    createCirclesLattice();
                    break;
                case GLFW_KEY_4:
                    physicsSystem->clearEntities();
                    createAABBLattice();
                    break;
                case GLFW_KEY_5:
                    physicsSystem->clearEntities();
                    createChaosLattice(false);
                    break;
                case GLFW_KEY_6:
                    physicsSystem->clearEntities();
                    createChaosLattice(true);
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
