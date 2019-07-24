/* A beginning OpenGL program that uses OpenGL 3.3
     to draw a triangle. The triangle is now specified with 3D
     coordinates.
   A virtual camera has been defined and limited key-based
     movement has been added.
   Author: Gary M. Zoppetti, Ph.D.
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
#include <iostream>
#include <sstream>
#include <string>

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
#include "Mesh.h"
#include "Camera.h"
#include "KeyBuffer.h"
#include "Transform.h"
#include "MouseState.h"

/******************************************************************/
// Type declarations/globals variables/prototypes

// Need a shader program to transform and light the primitives
ShaderProgram* g_shaderProgram;
Mesh* g_mesh;
Mesh* g_mesh2;
Camera g_camera;
KeyBuffer g_keyBuffer;
MouseState g_mouseState;

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
drawScene (GLFWwindow* window);

void
mouse_callback(GLFWwindow* window, int button, int action, int mods);

void 
processMouseDrag(GLFWwindow* window);

void
processScroll (GLFWwindow* window, double xOffset, double yOffset);

void
recordKeys (GLFWwindow* window, int key, int scanCode, int action,
       int modifiers);

void
processKeys (GLFWwindow* window);

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

  // Game/render loop
  while (!glfwWindowShouldClose (window))
  {
    drawScene (window);
    // Process events in the event queue, which results in callbacks
    //   being invoked.
    glfwPollEvents ();
    processKeys (window);
    processMouseDrag (window);
  }

  releaseGlResources ();
  // Destroying the window destroys the OpenGL context
  glfwDestroyWindow (window);
  glfwTerminate ();

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
  glfwSetKeyCallback (window, recordKeys);
  glfwSetMouseButtonCallback(window, mouse_callback);
  glfwSetScrollCallback(window, processScroll);
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
  g_mouseState.setWidth(width);
  g_mouseState.setHeight(height);
  g_mouseState.setXFOV(g_camera.getXFOV());
  g_mouseState.setYFOV(g_camera.getYFOV());
}

/******************************************************************/

void
initGlew ()
{
  GLenum status = glewInit ();
  if (status != GLEW_OK)
  {
    fprintf (stderr, "Failed to initialize GLEW -- exiting"
	     " (%s).\n",
	     glewGetErrorString (status));
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
  g_camera.setAspectRatio((float)(width / height));
  g_mouseState.setWidth(width);
  g_mouseState.setHeight(height);
  g_mouseState.setXFOV(g_camera.getXFOV());
  g_mouseState.setYFOV(g_camera.getYFOV());
}

/******************************************************************/

void
initScene ()
{
  // Compile and link all shader programs
  initShaders ();

  g_mesh = new Mesh();
  g_mesh->importFromFile("bear.obj");
  g_mesh->prepareVao();

  g_mesh2 = new Mesh();
  g_mesh2->importFromFile("Sphere.obj");
  g_mesh2->prepareVao();
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
drawScene (GLFWwindow* window)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  g_mesh->draw( g_shaderProgram, g_camera );
  g_mesh2->draw( g_shaderProgram, g_camera );

  // Swap the front and back buffers.
  // We draw to the back buffer, which is then swapped with the front
  //   for display.
  glfwSwapBuffers (window);
}

/******************************************************************/

void
mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
  if (action == GLFW_PRESS)
  {
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
      if (g_mouseState.isRightClicked())
      {
          g_mouseState.setReleased();
      }
      else
      {
          double x;
          double y;
          glfwGetCursorPos(window, &x, &y);
          g_mouseState.setLeftClick(x, y);
      }
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
      if (g_mouseState.isLeftClicked())
      {
          g_mouseState.setReleased();
      }
      else
      {
          double x;
          double y;
          glfwGetCursorPos(window, &x, &y);
          g_mouseState.setRightClick(x, y);
      }
    }
  }
  else if(action == GLFW_RELEASE 
    &&   (button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT))
  {
      g_mouseState.setReleased();
  }
}

/******************************************************************/

void 
processMouseDrag(GLFWwindow* window)
{
  if (g_mouseState.isLeftClicked())
  {
    double x;
    double y;
    glfwGetCursorPos(window, &x, &y);
    g_mouseState.translate(x, y);
    g_camera.yaw(g_mouseState.getXDegrees());
    g_camera.pitch(g_mouseState.getYDegrees());
  }
  else if (g_mouseState.isRightClicked())
  {
    double x;
    double y;
    glfwGetCursorPos(window, &x, &y);
    g_mouseState.translate(x, y);
    g_camera.roll(g_mouseState.getXDegrees());
  }
}

/******************************************************************/

// Callback for handling mouse wheel scroll events.
// Use this function for zooming using "yOffset". 
void
processScroll (GLFWwindow* window, double xOffset, double yOffset)
{
  g_camera.zoom(yOffset);
  g_mouseState.setXFOV(g_camera.getXFOV());
  g_mouseState.setYFOV(g_camera.getYFOV());
}

/******************************************************************/

void
recordKeys (GLFWwindow* window, int key, int scanCode, int action,
       int modifiers)
{
  // Actions are GLFW_PRESS, GLFW_RELEASE, and GLFW_REPEAT
  if ( action == GLFW_PRESS )
  {
    g_keyBuffer.setKeyDown( key );
  }
  else if ( action == GLFW_RELEASE )
  {
    g_keyBuffer.setKeyUp( key );
  }
}

/******************************************************************/

void
processKeys(GLFWwindow* window)
{
  if ( g_keyBuffer.isKeyDown( GLFW_KEY_ESCAPE ))
  {
    // Exit if ESC is pressed
    glfwSetWindowShouldClose (window, GL_TRUE);
  }
  else
  {
    static const float MOVEMENT_DELTA = 0.1f;
    static const float ANGLE_DELTA = 1.5f;
    // Translate camera/eye point using WASD keys
    if ( g_keyBuffer.isKeyDown( GLFW_KEY_W ) 
      != g_keyBuffer.isKeyDown( GLFW_KEY_S ))
    {
      if ( g_keyBuffer.isKeyDown( GLFW_KEY_W ))
      {
        g_camera.moveBack( -MOVEMENT_DELTA );
      }
      else
      {
        g_camera.moveBack( MOVEMENT_DELTA );
      }
    }
    
    if ( g_keyBuffer.isKeyDown( GLFW_KEY_A ) 
      != g_keyBuffer.isKeyDown( GLFW_KEY_D ))
    {
      if ( g_keyBuffer.isKeyDown( GLFW_KEY_A ))
      {
        g_camera.moveRight( -MOVEMENT_DELTA );
      }
      else
      {
        g_camera.moveRight( MOVEMENT_DELTA );
      }
    }
    
    if ( g_keyBuffer.isKeyDown( GLFW_KEY_F ) 
      != g_keyBuffer.isKeyDown( GLFW_KEY_C ))
    {
      if ( g_keyBuffer.isKeyDown( GLFW_KEY_F ))
      {
        g_camera.moveUp( MOVEMENT_DELTA );
      }
      else
      {
        g_camera.moveUp( -MOVEMENT_DELTA );
      }
    }
    
    if ( g_keyBuffer.isKeyDown( GLFW_KEY_I ) 
      != g_keyBuffer.isKeyDown( GLFW_KEY_K ))
    {
      if ( g_keyBuffer.isKeyDown( GLFW_KEY_I ))
      {
        g_camera.pitch( ANGLE_DELTA );
      }
      else
      {
        g_camera.pitch( -ANGLE_DELTA );
      }
    }
    
    if ( g_keyBuffer.isKeyDown( GLFW_KEY_J ) 
      != g_keyBuffer.isKeyDown( GLFW_KEY_L ))
    {
      if ( g_keyBuffer.isKeyDown( GLFW_KEY_J ))
      {
        g_camera.yaw( ANGLE_DELTA );
      }
      else
      {
        g_camera.yaw( -ANGLE_DELTA );
      }
    }
    
    if ( g_keyBuffer.isKeyDown( GLFW_KEY_N ) 
      != g_keyBuffer.isKeyDown( GLFW_KEY_M ))
    {
      if ( g_keyBuffer.isKeyDown( GLFW_KEY_N ))
      {
        g_camera.roll( ANGLE_DELTA );
      }
      else
      {
        g_camera.roll( -ANGLE_DELTA );
      }
    }
    
    if ( g_keyBuffer.isKeyDown( GLFW_KEY_R ))
    {
      g_camera.reset();
      g_mesh->reset();
    }

    if ( g_keyBuffer.isKeyDown( GLFW_KEY_1 ))
    {
      g_mesh->moveRight( -MOVEMENT_DELTA );
    }

    if ( g_keyBuffer.isKeyDown( GLFW_KEY_2 ))
    {
      g_mesh->moveUp( MOVEMENT_DELTA );
    }

    if ( g_keyBuffer.isKeyDown( GLFW_KEY_3 ))
    {
      g_mesh->moveWorld( MOVEMENT_DELTA, Vector3(1,0,0) );
    }

    if ( g_keyBuffer.isKeyDown( GLFW_KEY_4 ))
    {
      g_mesh->pitch( ANGLE_DELTA );
    }

    if ( g_keyBuffer.isKeyDown( GLFW_KEY_5 ))
    {
      g_mesh->yaw( ANGLE_DELTA );
    }

    if ( g_keyBuffer.isKeyDown( GLFW_KEY_6 ))
    {
      g_mesh->roll( ANGLE_DELTA );
    }

    if ( g_keyBuffer.isKeyDown( GLFW_KEY_7 ))
    {
      g_mesh->alignWithWorldY();
    }

    if ( g_keyBuffer.isKeyDown( GLFW_KEY_8 ))
    {
      g_mesh->scaleLocal(0.995f);
    }

    if ( g_keyBuffer.isKeyDown( GLFW_KEY_9 ))
    {
      g_mesh->scaleWorld(1.005f);
    }

    if ( g_keyBuffer.isKeyDown( GLFW_KEY_0 ))
    {
      g_mesh->shearLocalXByYz(1.0001f, 1.0001f);
    }

    if (g_keyBuffer.isKeyDown( GLFW_KEY_O ))
    {
      g_camera.setOrthoProjection(-15.0f, 15.0f, -15.0f, 15.0f, 0.1f, 120.0f);
      g_mouseState.setXFOV(g_camera.getXFOV());
      g_mouseState.setYFOV(g_camera.getYFOV());
    }

    if (g_keyBuffer.isKeyDown( GLFW_KEY_P ))
    {
      g_camera.setProjection();
      g_mouseState.setXFOV(g_camera.getXFOV());
      g_mouseState.setYFOV(g_camera.getYFOV());
    }

    if (g_keyBuffer.isKeyDown( GLFW_KEY_LEFT_BRACKET ))
    {
      g_camera.setProjection(-0.075f, 0.125f, -0.075f, 0.125f, 0.1f, 120.0f);
      g_mouseState.setXFOV(g_camera.getXFOV());
      g_mouseState.setYFOV(g_camera.getYFOV());
    }
  }
}

/******************************************************************/
// Deallocate Resources
void
releaseGlResources ()
{
  delete g_shaderProgram;
  delete g_mesh;
  delete g_mesh2;
}

/******************************************************************/

void
outputGlfwError (int error, const char* description)
{
  fprintf (stderr, "GLFW error: %s, code %d\n", description, error);
}

/******************************************************************/