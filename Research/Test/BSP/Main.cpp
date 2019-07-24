/* A beginning OpenGL program that uses OpenGL 3.3
     to draw a triangle. The triangle is now specified with 3D
     coordinates.
   A virtual camera has been defined and limited key-based
     movement has been added.
*/

/*
  FileName    : Main.cpp
  Author      : Zachary Zuch
  Course      : CSCI 375
  Assignment  : Lab 4
  Description : This file is the main file to initialize GLEW and GLFW,
              and send draw calls.
*/

/******************************************************************/
// System includes
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <iomanip>

// Use GLEW so we can access the latest OpenGL functionality
// Always include GLEW before GLFW!
#include <GL/glew.h>
// Use GLFW so we can create windows and handle events in a
//   platform-independent way
#include <GLFW/glfw3.h>
#include <GL/glut.h>

/******************************************************************/
// Local includes
#include "ShaderProgram.h"
#include "KeyBuffer.h"
#include "Scene.h"

/******************************************************************/
// Type declarations/globals variables/prototypes

// Need a shader program to transform and light the primitives
ShaderProgram* g_shaderProgram;
Scene* g_scene;
KeyBuffer g_keyBuffer;

unsigned frameCounter = 0;
double frameTime = 0.0;
int fps = 0;

const std::vector<std::string> g_meshFiles = {"model.dae", "Deathwing.obj", "Sphere.obj"};
float g_animationMultiplier = 1.0f;

/******************************************************************/

void
init (GLFWwindow*& window);

void
initGlfw ();

void
initGlew ();

void
initWindow (GLFWwindow*& window);

void
resetViewport (GLFWwindow* window, int width, int height);

void
initScene ();

void
initShaders ();

void
updateScene (double time);

void
drawScene (GLFWwindow* window, double deltaTime);

void
processMouseButton(GLFWwindow* window, int button, int action, int mods);

void 
processMousePosition(GLFWwindow* window, double x, double y);

void
processScroll (GLFWwindow* window, double xOffset, double yOffset);

void
recordKeys (GLFWwindow* window, int key, int scanCode, int action,
 int modifiers);

void
processKeys ();

void
releaseGlResources ();

void
outputGlfwError (int error, const char* description);

/******************************************************************/

int
main (int argc, char* argv[])
{
    GLFWwindow* window;
    init (window);

    // std::cout << "Vertex Uniform Max = " << GL_MAX_VERTEX_UNIFORM_COMPONENTS_ARB << std::endl;

    double previousTime = glfwGetTime ();
    // Game/render loop
    while (!glfwWindowShouldClose (window))
    {
        double currentTime = glfwGetTime ();
        // Compute frame times, which we can use later for frame rate 
        //      computation, animation, and physics.
        double deltaTime = currentTime - previousTime;

        frameTime += deltaTime;
        ++frameCounter;

        previousTime = currentTime;
        updateScene (deltaTime);
        drawScene (window, deltaTime);
        // Process events in the event queue, which results in callbacks
        //   being invoked.
        glfwPollEvents ();
        processKeys ();

        if (frameTime > 1.0)
        {
            frameCounter = 0;
            frameTime = 0.0;
        }
    }

    // Destroying the window destroys the OpenGL context
    glfwDestroyWindow (window);
    glfwTerminate ();
    std::cout << std::endl;

    return EXIT_SUCCESS;
}

/******************************************************************/

void
init (GLFWwindow*& window)
{
    // Always initialize GLFW before GLEW
    initGlfw ();
    initWindow (window);
    initGlew ();
    initScene ();
    int width, height;
    glfwGetFramebufferSize (window, &width, &height);
    g_scene->setAspectRatio(width, height);
}

/******************************************************************/

void
initGlfw ()
{
    glfwSetErrorCallback (outputGlfwError);
    if (!glfwInit ())
    {
        fprintf (stderr, "Failed to init GLFW -- exiting\n");
        exit (EXIT_FAILURE);
    }
}

/******************************************************************/

void
initWindow (GLFWwindow*& window)
{
    // Necessary on MacOS! Was needed in one case on Linux too.
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow (1200, 900, "OpenGL Engine", nullptr, nullptr);
    if (window == nullptr)
    {
        fprintf (stderr, "Failed to init the window -- exiting\n");
        glfwTerminate ();
        exit (EXIT_FAILURE);
    }
    glfwSetWindowPos (window, 200, 100);

    glfwMakeContextCurrent (window);
      // Swap buffers after 1 frame
    glfwSwapInterval (1);
    // Input Callbacks
    glfwSetKeyCallback (window, recordKeys);
    glfwSetScrollCallback(window, processScroll);
    glfwSetMouseButtonCallback(window, processMouseButton);
    glfwSetCursorPosCallback(window, processMousePosition);
    // Frame/Window Resize Callback
    glfwSetFramebufferSizeCallback (window, resetViewport);

      // Specify background color
    glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
    
      // Enable depth testing so occluded surfaces aren't drawn
    glEnable (GL_DEPTH_TEST);
      // Enable the culling of back-facing triangles
      // A triangle must be wound CCW in window coordinates to be front facing
      // If it is wound CW it is back facing and will NOT be displayed!
    glEnable (GL_CULL_FACE);
      // The next two setting are default, but we'll be explicit.
    glFrontFace (GL_CCW);
    glCullFace (GL_BACK);
    // Set initial viewport size
    int width, height;
    glfwGetFramebufferSize (window, &width, &height);
    glViewport (0, 0, width, height);
}

/******************************************************************/

void
initGlew ()
{
    GLenum status = glewInit ();
    if (status != GLEW_OK)
    {
        fprintf (stderr, "Failed to initialize GLEW -- exiting"
            " (%s).\n", glewGetErrorString (status));
        exit (EXIT_FAILURE);
    }
    const GLubyte* version = glewGetString (GLEW_VERSION);
    fprintf (stderr, "Using GLEW version %s.\n", version);
    version = glGetString (GL_VERSION);
    fprintf (stderr, "Using OpenGL version %s\n", version);
}

/******************************************************************/

void
resetViewport (GLFWwindow* window, int width, int height)
{
    // Render into entire window
    // Origin for window coordinates is lower-left of window
    glViewport (0, 0, width, height);
    g_scene->setAspectRatio(width, height);
    g_keyBuffer.reset();
}

/******************************************************************/

void
initScene ()
{
    // Compile and link all shader programs
    initShaders ();
    g_scene = new Scene();

    g_scene->lights[0].setIsActive(true);
    g_scene->lights[0].setIsDirect(true);
    g_scene->lights[0].direction = {0, 0, 1};
    g_scene->lights[0].intensity.setSpecular({0});
    g_scene->lights[0].intensity.setDiffuse ({0.5});

    g_scene->lights[1].setIsActive(true);
    g_scene->lights[1].setIsDirect(true);
    g_scene->lights[1].direction = {0, 0, -1};
    g_scene->lights[1].intensity.setSpecular({0});
    g_scene->lights[1].intensity.setDiffuse ({0.5});

    g_scene->lights[2].setIsActive(true);
    g_scene->lights[2].setIsDirect(true);
    g_scene->lights[2].direction = {0, 1, 0};
    g_scene->lights[2].intensity.setSpecular({0});
    g_scene->lights[2].intensity.setDiffuse ({0.5});

    g_scene->lights[3].setIsActive(true);
    g_scene->lights[3].setIsDirect(true);
    g_scene->lights[3].direction = {0, -1, 0};
    g_scene->lights[3].intensity.setSpecular({0});
    g_scene->lights[3].intensity.setDiffuse ({0.5});

    g_scene->lights[4].setIsActive(true);
    g_scene->lights[4].setIsDirect(true);
    g_scene->lights[4].direction = {1, 0, 0};
    g_scene->lights[4].intensity.setSpecular({0});
    g_scene->lights[4].intensity.setDiffuse ({0.5});

    g_scene->lights[5].setIsActive(true);
    g_scene->lights[5].setIsDirect(true);
    g_scene->lights[5].direction = {-1, 0, 0};
    g_scene->lights[5].intensity.setSpecular({0});
    g_scene->lights[5].intensity.setDiffuse ({0.5});

    g_scene->lights[6].setIsActive(true);
    g_scene->lights[6].setIsDirect(false);
    g_scene->lights[6].intensity.setSpecular({1});
    g_scene->lights[6].intensity.setDiffuse ({0.5});

    g_scene->lights[7].setIsActive(true);
    g_scene->lights[7].setIsDirect(false);
    g_scene->lights[7].direction = {0, -0.5, 1};
    g_scene->lights[7].setAngleOfLight(0.5f);
    g_scene->lights[7].intensity.setSpecular({1});
    g_scene->lights[7].intensity.setDiffuse ({0.5});

    // Origin for the model is offset due to creation
    g_scene->models->add("BoxHierarchy.fbx");
    //g_scene->models->add("Deathwing.obj");
    // g_scene->models->add(g_meshFiles[1]);
    g_scene->models->add(g_meshFiles[2]);
    // VAO is already prepared by the assimp class
}

/******************************************************************/

void
initShaders ()
{
    // Create shader programs, which consist of linked shaders.
    // No need to use the program until we draw or set uniform variables.
    g_shaderProgram = new ShaderProgram ();
    g_shaderProgram->createVertexShader ("Vec3Norm.vert");
    g_shaderProgram->createFragmentShader ("Vec3.frag");
    g_shaderProgram->link ();
}

/******************************************************************/

void
updateScene (double deltaTime)
{
    // couldnt figure out how to add text to the screen
    // std::cout << 1 / deltaTime << " fps" << std::flush;

    Model* model = g_scene->models->getModel("model.dae");
    if (model != nullptr)
    {
        model->m_bone->update(deltaTime * g_animationMultiplier);
    }
}

/******************************************************************/

void
drawScene (GLFWwindow* window, double deltaTime)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    unsigned numTriangles = g_scene->draw( g_shaderProgram );

    if ((fps == 0) || (frameTime > 1.0))
    {
        fps = static_cast<int>(frameCounter / frameTime);
        
    }
    std::cout << "\r" << "FPS = " << std::setw(6) << fps << " | Number of Triangles = " << std::setw(6) << numTriangles << std::flush;
    
    // Swap the front and back buffers.
    // We draw to the back buffer, which is then swapped with the front
    //   for display.
    glfwSwapBuffers (window);
}

/******************************************************************/

void
processMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT)
        {
            if (g_scene->mouseBuffer.isRightClicked()) g_scene->mouseBuffer.setReleased();
            else
            {
                g_scene->mouseBuffer.setClick(window);
            }
        }
        else if (button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            if (g_scene->mouseBuffer.isLeftClicked()) g_scene->mouseBuffer.setReleased();
            else
            {
                g_scene->mouseBuffer.setClick(window, false);
            }
        }
    }
    else if (action == GLFW_RELEASE) g_scene->mouseBuffer.setReleased();
}

/******************************************************************/

void 
processMousePosition(GLFWwindow* window, double x, double y)
{
    g_scene->processDrag(x, y);
}

/******************************************************************/

// Callback for handling mouse wheel scroll events.
// Use this function for zooming using "yOffset". 
void
processScroll (GLFWwindow* window, double xOffset, double yOffset)
{
    g_scene->setZoom(yOffset);
}

/******************************************************************/

void
recordKeys (GLFWwindow* window, int key, int scanCode, int action,
 int modifiers)
{
    // Actions are GLFW_PRESS, GLFW_RELEASE, and GLFW_REPEAT
    // Functions moved here so that they are only processed 
    //      once per key press.
    if ( action == GLFW_PRESS )
    {
        if ( key == GLFW_KEY_ESCAPE )
        {
            // Exit if ESC is pressed
            glfwSetWindowShouldClose (window, GL_TRUE);
            return;
        }

        if (key == GLFW_KEY_F7)
        {
            Model* model = g_scene->models->getModel("model.dae");
            if (model != nullptr)
            {
                model->m_bone->bind.moveUp(1);
            }
        }

        if (key == GLFW_KEY_F8)
        {
            Model* model = g_scene->models->getModel("model.dae");
            if (model != nullptr)
            {
                model->m_bone->bind.moveUp(-1);
            }
        }

        if (key == GLFW_KEY_F9)
        {
            if (g_animationMultiplier == 1.0f)
            {
                g_animationMultiplier = 2.0f;
            }
            else if (g_animationMultiplier == 2.0f)
            {
                g_animationMultiplier = 0.5f;
            }
            else
            {
                g_animationMultiplier = 1.0f;
            }
        }

        if (key == GLFW_KEY_F10)
        {
            Model* model = g_scene->models->getModel("model.dae");
            if (model != nullptr)
            {
                model->m_bone->isAnimated = false;
            }
        }
        if (key == GLFW_KEY_F11)
        {
            Model* model = g_scene->models->getModel("model.dae");
            if (model != nullptr)
            {
                model->m_bone->isAnimated = true;
            }
        }
             
        if (key == GLFW_KEY_F12)
        {
            Model* model = g_scene->models->getModel("model.dae");
            if (model != nullptr)
            {
                model->m_bone->time = 0;
            }
        }

        if ( key == GLFW_KEY_O )
        {
            g_scene->setToOrtho(-15.0f, 15.0f, -15.0f, 15.0f, 0.1f, 120.0f);
        }
        else if ( key == GLFW_KEY_P )
        {
            g_scene->setToSymmetric();
        }
        else if ( key == GLFW_KEY_LEFT_BRACKET )
        {
            g_scene->setToAsymmetric(-0.075f, 0.125f, -0.075f, 0.125f, 0.1f, 120.0f);
        }

        if ( key == GLFW_KEY_MINUS )
        {
            g_scene->models->prev();
        }
        else if ( key == GLFW_KEY_EQUAL )
        {
            g_scene->models->next();
        }

        if ( key == GLFW_KEY_F1 )
        {
            g_scene->models->setActiveToDraw();
        }
        else if ( key == GLFW_KEY_F2 )
        {
            g_scene->models->setActiveToDraw(false);
        }
        else if ( key == GLFW_KEY_F3 )
        {
            g_scene->models->fillToDraw();
        }
        else if ( key == GLFW_KEY_F4 )
        {
            g_scene->models->fillToDraw(false);
        }
        else if ( key == GLFW_KEY_F5 )
        {
            g_scene->models->removeActive();
        }
        else if ( key == GLFW_KEY_F6 )
        {
            g_scene->models->removeAll();
        }

        g_keyBuffer.setKeyDown( key );
    }
    else if ( action == GLFW_RELEASE )
    {
        g_keyBuffer.setKeyUp( key );
    }
}

/******************************************************************/

void
processKeys()
{
    static constexpr float MOVEMENT_DELTA = 0.1f;
    static constexpr float ANGLE_DELTA = 1.5f;
    // Translate camera/eye point using WASD keys

    if ( g_keyBuffer[ GLFW_KEY_W ] != g_keyBuffer[ GLFW_KEY_S ])
    {
        g_scene->camera.moveBack((g_keyBuffer[ GLFW_KEY_W ] ? -1 : 1) * MOVEMENT_DELTA);
    }

    if ( g_keyBuffer[ GLFW_KEY_A ] != g_keyBuffer[ GLFW_KEY_D ])
    {
        g_scene->camera.moveRight((g_keyBuffer[ GLFW_KEY_A ] ? -1 : 1) * MOVEMENT_DELTA);
    }

    if ( g_keyBuffer[ GLFW_KEY_F ] != g_keyBuffer[ GLFW_KEY_C ])
    {
        g_scene->camera.moveUp((g_keyBuffer[ GLFW_KEY_C ] ? -1 : 1) * MOVEMENT_DELTA);
    }

    if ( g_keyBuffer[ GLFW_KEY_I ] != g_keyBuffer[ GLFW_KEY_K ])
    {
        g_scene->camera.pitch((g_keyBuffer[ GLFW_KEY_K ] ? -1 : 1) * ANGLE_DELTA);
    }

    if (( g_keyBuffer[ GLFW_KEY_J ] || g_keyBuffer[ GLFW_KEY_Q ])
       != (g_keyBuffer[ GLFW_KEY_L ] || g_keyBuffer[ GLFW_KEY_E ]))
    {
        g_scene->camera.yaw(g_keyBuffer[ GLFW_KEY_L ] || g_keyBuffer[ GLFW_KEY_E ] ? -1 : 1 * ANGLE_DELTA);
    }

    if ( g_keyBuffer[ GLFW_KEY_N ] != g_keyBuffer[ GLFW_KEY_M ])
    {
        g_scene->camera.roll((g_keyBuffer[ GLFW_KEY_M ] ? -1 : 1) * ANGLE_DELTA);
    }

    if ( g_keyBuffer[ GLFW_KEY_R ])
    {
        g_scene->camera.reset();
    }

    if ( g_keyBuffer[ GLFW_KEY_1 ] != g_keyBuffer[ GLFW_KEY_2 ] )
    {
        g_scene->models->getActiveTransform().moveRight((g_keyBuffer[ GLFW_KEY_1 ] ? -1 : 1) * MOVEMENT_DELTA );
    }

    if ( g_keyBuffer[ GLFW_KEY_3 ] != g_keyBuffer[ GLFW_KEY_4 ] )
    {
        g_scene->models->getActiveTransform().moveUp((g_keyBuffer[ GLFW_KEY_3 ] ? -1 : 1) * MOVEMENT_DELTA );
    }

    if ( g_keyBuffer[ GLFW_KEY_5 ] != g_keyBuffer[ GLFW_KEY_6 ] )
    {
        g_scene->models->getActiveTransform().moveBack((g_keyBuffer[ GLFW_KEY_6 ] ? -1 : 1) * MOVEMENT_DELTA );
    }

    if ( g_keyBuffer[ GLFW_KEY_7 ] != g_keyBuffer[ GLFW_KEY_8 ] )
    {
        g_scene->models->getActiveTransform().scaleLocal((g_keyBuffer[ GLFW_KEY_8 ] ? -0.1f : 0.1f) + 1.0f);
    }

    if ( g_keyBuffer[ GLFW_KEY_9 ] != g_keyBuffer[ GLFW_KEY_0 ] )
    {
        g_scene->models->getActiveTransform().yaw((g_keyBuffer[ GLFW_KEY_9 ] ? -1 : 1) * ANGLE_DELTA);
    }
}

/******************************************************************/

void
releaseGlResources ()
{
    delete g_shaderProgram;
    delete g_scene;
}

/******************************************************************/

void
outputGlfwError (int error, const char* description)
{
    fprintf (stderr, "GLFW error: %s, code %d\n", description, error);
}

/******************************************************************/