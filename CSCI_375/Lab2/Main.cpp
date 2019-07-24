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
  Assignment  : Lab 2
  Description : This file is the main file to initialize GLEW and GLFW,
              and send draw calls.
*/

/******************************************************************/
// System includes
#include <cstdio>
#include <cstdlib>
#include <vector>
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

// GLM is a header-only library, so we do not need to link to it
// It provides matrix classes and mathematical functions
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
// Need for "value_ptr", which allows us to get a pointer from a matrix
#include <glm/gtc/type_ptr.hpp>
// Transforms like lookat, perspective, rotate, scale, translate
#include <glm/gtc/matrix_transform.hpp>

/******************************************************************/
// Local includes
#include "ShaderProgram.h"
#include "Mesh.h"

/******************************************************************/
// Type declarations/globals variables/prototypes
using std::cout;
using std::endl;


// We use one VAO for each object we draw
//std::vector<GLuint> g_vaos;

// Need a shader program to transform and light the primitives
ShaderProgram* g_shaderProgram;

Mesh* g_mesh;

// A type for a virtual camera, or eye point
struct Camera
{
  // Location of camera
  glm::vec3 position;
  // Point camera is looking at
  glm::vec3 at;
  // Camera's up vector
  glm::vec3 up;
  // Projection (defines view volume)
  glm::mat4 projection;
};

Camera g_camera;

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
initCamera ();

void
updateScene (double time);

void
drawScene (GLFWwindow* window);

void
drawObject ();

void
processKeys (GLFWwindow* window, int key, int scanCode, int action,
	     int modifiers);

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
  double previousTime = glfwGetTime ();
  while (!glfwWindowShouldClose (window))
  {
    double currentTime = glfwGetTime ();
    // Compute frame times, which we can use later for frame rate computation,
    //   animation, and physics.
    double deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    updateScene (deltaTime);
    drawScene (window);
    // Process events in the event queue, which results in callbacks
    //   being invoked.
    glfwPollEvents ();
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
  glfwSetKeyCallback (window, processKeys);
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
}

/******************************************************************/

void
initScene ()
{
  // Compile and link all shader programs
  initShaders ();

  initCamera ();

  g_mesh = new Mesh();
  // First 3 floats are position second 3 floats are color for one vertex
  // These vectors make a fully connected 3D sword with 34 Triangles
  std::vector<float> triVertices_front
    {
      // Triangle 1
      0.0f, 5.0f, -0.1f, 
      1.0f, 0.0f, 0.0f,

      -0.25f, 4.5f, 0.0f,
      0.0f, 1.0f, 0.0f,

      0.25f, 4.5f, 0.0f,
      0.0f, 0.0f, 1.0f,

      // Triangle 2
      -0.25f, -4.0f, 0.0f,
      1.0f, 0.0f, 0.0f,

      0.25f, -4.0f, 0.0f,
      0.0f, 1.0f, 0.0f,

      0.25f, 4.5f, 0.0f,
      0.0f, 0.0f, 1.0f,

      // Triangle 3
      -0.25f, 4.5f, 0.0f,
      0.0f, 1.0f, 0.0f,

      -0.25f, -4.0f, 0.0f,
      1.0f, 0.0f, 0.0f,

      0.25f, 4.5f, 0.0f,
      0.0f, 0.0f, 1.0f,

      // Triangle 4
      -1.75f, -4.0f, 0.0f,
      1.0f, 0.0f, 0.0f,

      -1.75f, -4.1f, 0.0f,
      0.0f, 1.0f, 0.0f,

      1.75f, -4.1f, 0.0f,
      0.0f, 0.0f, 1.0f,

      // Triangle 5
      -1.75f, -4.0f, 0.0f,
      1.0f, 0.0f, 0.0f,

      1.75f, -4.1f, 0.0f,
      0.0f, 0.0f, 1.0f,

      1.75f, -4.0f, 0.0f,
      0.0f, 0.0f, 1.0f,

      // Triangle 6
      0.1f, -4.1f, 0.0f,
      0.7f, 0.0f, 0.3f,

      -0.1f, -4.1f, 0.0f,
      0.3f, 0.0f, 0.7f,

      -0.1f, -5.6f, 0.0f,
      0.0f, 0.7f, 0.3f,

      // Triangle 7
      0.1f, -4.1f, 0.0f,
      0.7f, 0.0f, 0.3f,

      -0.1f, -5.6f, 0.0f,
      0.0f, 0.7f, 0.3f,

      0.1f, -5.6f, 0.0f,
      0.3f, 0.0f, 0.7f
    };

  std::vector<float> triVertices_back
    {
      // Back
      // Triangle 8
      // To how one triangle from behind
      // in order to show the setup of -z rendering
      0.0f, 5.0f, -0.1f, 
      1.0f, 0.0f, 0.0f,

      // Last 2 vertices are swapped for rending from -z
      0.25f, 4.5f, -0.2f,
      0.0f, 0.0f, 1.0f,

      -0.25f, 4.5f, -0.2f,
      0.0f, 1.0f, 0.0f,

      // Triangle 9
      -0.25f, 4.5f, -0.2f,
      0.0f, 1.0f, 0.0f,

      0.25f, 4.5f, -0.2f,
      0.0f, 0.0f, 1.0f,

      0.25f, -4.0f, -0.2f,
      1.0f, 0.0f, 0.0f,

      // Triangle 10
      -0.25f, 4.5f, -0.2f,
      0.0f, 1.0f, 0.0f,

      0.25f, -4.0f, -0.2f,
      1.0f, 0.0f, 0.0f,

      -0.25f, -4.0f, -0.2f,
      0.0f, 0.0f, 1.0f,

      // Triangle 11
      1.75f, -4.0f, -0.2f,
      1.0f, 0.0f, 0.0f,

      1.75f, -4.1f, -0.2f,
      0.0f, 1.0f, 0.0f,

      -1.75f, -4.1f, -0.2f,
      0.0f, 0.0f, 1.0f,

      // Triangle 12
      1.75f, -4.0f, -0.2f,
      1.0f, 0.0f, 0.0f,

      -1.75f, -4.1f, -0.2f,
      0.0f, 0.0f, 1.0f,

      -1.75f, -4.0f, -0.2f,
      0.0f, 0.0f, 1.0f,

      // Triangle 13
      -0.1f, -4.1f, -0.2f,
      0.7f, 0.0f, 0.3f,

      0.1f, -4.1f, -0.2f,
      0.3f, 0.0f, 0.7f,

      0.1f, -5.6f, -0.2f,
      0.0f, 0.7f, 0.3f,

      // Triangle 14
      -0.1f, -4.1f, -0.2f,
      0.7f, 0.0f, 0.3f,

      0.1f, -5.6f, -0.2f,
      0.0f, 0.7f, 0.3f,

      -0.1f, -5.6f, -0.2f,
      0.3f, 0.0f, 0.7f,
    };

  std::vector<float> triVertices_depth
    {
      //Depth
      // Triangle 15
      0.0f, 5.0f, -0.1f, 
      1.0f, 1.0f, 1.0f,

      0.25f, 4.5f, 0.0f,
      1.0f, 1.0f, 1.0f,

      0.25f, 4.5f, -0.2f,
      1.0f, 1.0f, 1.0f,

      // Triangle 16
      0.25f, 4.5f, -0.2f,
      1.0f, 1.0f, 1.0f,

      0.25f, 4.5f, 0.0f,
      1.0f, 1.0f, 1.0f,

      0.25f, -4.0f, 0.0f,
      1.0f, 1.0f, 1.0f,

      // Triangle 17
      0.25f, 4.5f, -0.2f,
      1.0f, 1.0f, 1.0f,

      0.25f, -4.0f, 0.0f,
      1.0f, 1.0f, 1.0f,

      0.25f, -4.0f, -0.2f,
      1.0f, 1.0f, 1.0f,

      // Triangle 18
      // Top-Handle Side
      -1.75f, -4.0f, -0.2f,
      1.0f, 1.0f, 1.0f,

      -1.75f, -4.0f, 0.0f,
      1.0f, 1.0f, 1.0f,

      1.75f, -4.0f, 0.0f,
      1.0f, 1.0f, 1.0f,

      // Triangle 19
      -1.75f, -4.0f, -0.2f,
      1.0f, 1.0f, 1.0f,

      1.75f, -4.0f, 0.0f,
      1.0f, 1.0f, 1.0f,

      1.75f, -4.0f, -0.2f,
      1.0f, 1.0f, 1.0f,

      // Right-Handle Side
      // Triangle 20
      1.75f, -4.0f, -0.2f,
      1.0f, 1.0f, 1.0f,

      1.75f, -4.0f, 0.0f,
      1.0f, 1.0f, 1.0f,

      1.75f, -4.1f, 0.0f,
      1.0f, 1.0f, 1.0f,

      // Triangle 21
      1.75f, -4.0f, -0.2f,
      1.0f, 1.0f, 1.0f,

      1.75f, -4.1f, 0.0f,
      1.0f, 1.0f, 1.0f,

      1.75f, -4.1f, -0.2f,
      1.0f, 1.0f, 1.0f,

      // Bottom-Handle Side
      // Triangle 22
      1.75f, -4.1f, -0.2f,
      1.0f, 1.0f, 1.0f,

      1.75f, -4.1f, 0.0f,
      1.0f, 1.0f, 1.0f,

      -1.75f, -4.1f, 0.0f,
      1.0f, 1.0f, 1.0f,

      // Triangle 23
      1.75f, -4.1f, -0.2f,
      1.0f, 1.0f, 1.0f,

      -1.75f, -4.1f, 0.0f,
      1.0f, 1.0f, 1.0f,

      -1.75f, -4.1f, -0.2f,
      1.0f, 1.0f, 1.0f,

      // Hilt-Right Side
      // Triangle 24
      0.1f, -4.1f, -0.2f,
      1.0f, 1.0f, 1.0f,

      0.1f, -4.1f, 0.0f,
      1.0f, 1.0f, 1.0f,

      0.1f, -5.6f, 0.0f,
      1.0f, 1.0f, 1.0f,

      // Triangle 25
      0.1f, -4.1f, -0.2f,
      1.0f, 1.0f, 1.0f,

      0.1f, -5.6f, 0.0f,
      1.0f, 1.0f, 1.0f,

      0.1f, -5.6f, -0.2f,
      1.0f, 1.0f, 1.0f,

      // Bottom Hilt
      // Triangle 26
      0.1f, -5.6f, 0.0f,
      1.0f, 1.0f, 1.0f,

      -0.1f, -5.6f, 0.0f,
      1.0f, 1.0f, 1.0f,

      -0.1f, -5.6f, -0.2f,
      1.0f, 1.0f, 1.0f,

      // Triangle 27
      0.1f, -5.6f, 0.0f,
      1.0f, 1.0f, 1.0f,

      -0.1f, -5.6f, -0.2f,
      1.0f, 1.0f, 1.0f,

      0.1f, -5.6f, -0.2f,
      1.0f, 1.0f, 1.0f,

      // Left Side
      // Triangle 28
      0.0f, 5.0f, -0.1f, 
      1.0f, 1.0f, 1.0f,

      -0.25f, 4.5f, -0.2f,
      1.0f, 1.0f, 1.0f,

      -0.25f, 4.5f, 0.0f,
      1.0f, 1.0f, 1.0f,

      // Triangle 29
      -0.25f, 4.5f, 0.0f,
      1.0f, 1.0f, 1.0f,

      -0.25f, 4.5f, -0.2f,
      1.0f, 1.0f, 1.0f,

      -0.25, -4.0f, -0.2f,
      1.0f, 1.0f, 1.0f,

      // Triangle 30
      -0.25f, 4.5f, 0.0f,
      1.0f, 1.0f, 1.0f,

      -0.25, -4.0f, -0.2f,
      1.0f, 1.0f, 1.0f,

      -0.25, -4.0f, 0.0f,
      1.0f, 1.0f, 1.0f,

      //Guard-Left Side
      // Triangle 31
      -1.75f, -4.0f, 0.0f,
      1.0f, 1.0f, 1.0f,

      -1.75f, -4.0f, -0.2f,
      1.0f, 1.0f, 1.0f,

      -1.75f, -4.1f, -0.2f,
      1.0f, 1.0f, 1.0f,

      // Triangle 32
      -1.75f, -4.0f, 0.0f,
      1.0f, 1.0f, 1.0f,

      -1.75f, -4.1f, -0.2f,
      1.0f, 1.0f, 1.0f,

      -1.75f, -4.1f, 0.0f,
      1.0f, 1.0f, 1.0f,

      // Hilt-Left Side
      // Triangle 33
      -0.1f, -4.1f, 0.0f,
      1.0f, 1.0f, 1.0f,

      -0.1f, -4.1f, -0.2f,
      1.0f, 1.0f, 1.0f,

      -0.1f, -5.6f, -0.2f,
      1.0f, 1.0f, 1.0f,

      // Triangle 34
      -0.1f, -4.1f, 0.0f,
      1.0f, 1.0f, 1.0f,

      -0.1f, -5.6f, -0.2f,
      1.0f, 1.0f, 1.0f,

      -0.1f, -5.6f, 0.0f,
      1.0f, 1.0f, 1.0f
    };

  g_mesh->addGeometry( triVertices_front );
  g_mesh->addGeometry( triVertices_back );
  g_mesh->addGeometry( triVertices_depth );
  g_mesh->prepareVao();
}

/******************************************************************/

void
initShaders ()
{
  // Create shader programs, which consist of linked shaders.
  // No need to use the program until we draw or set uniform variables.
  g_shaderProgram = new ShaderProgram ();
  g_shaderProgram->createVertexShader ("Vec3.vert");
  g_shaderProgram->createFragmentShader ("Vec3.frag");
  g_shaderProgram->link ();
}

/******************************************************************/

void
initCamera ()
{
  // Define the projection, which will remain constant
  float verticalFov = glm::radians (50.0f);
  float aspectRatio = 1200.0f / 900;
  // Near plane
  float nearZ = 0.01f;
  // Far plane
  float farZ = 40.0f;
  g_camera.projection = glm::perspective (verticalFov, aspectRatio, nearZ,
					  farZ);
  // Enable shader program so we can set uniforms
  g_shaderProgram->enable ();
  g_shaderProgram->setUniformMatrix ("uProjection", g_camera.projection);
  // Define the camera's coordinate system
  g_camera.position = glm::vec3 (0, 0, 12.0f);
  g_camera.at = glm::vec3 (0, 0, 0);
  g_camera.up = glm::vec3 (0, 1, 0);
}

/******************************************************************/

void
updateScene (double time)
{
  // AI, Physics, Game/application logic
  // cout << "FPS = " << (1 / time) << endl;
}

/******************************************************************/

void
drawScene (GLFWwindow* window)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Iterate over each object in scene and draw it
  // Here we have only one object
  drawObject ();

  // Swap the front and back buffers.
  // We draw to the back buffer, which is then swapped with the front
  //   for display.
  glfwSwapBuffers (window);
}

/******************************************************************/

void
drawObject ()
{
  // The shader program is already enabled, but we do not want to
  //   make that assumption in general.
  // Set shader uniforms
  // Only the model-view matrix needs set, since the projection is
  //   already set and it will persist.
  // Create view matrix
  glm::mat4 modelView = glm::lookAt (g_camera.position, g_camera.at, g_camera.up);
  g_mesh->draw( g_shaderProgram, modelView );
}

/******************************************************************/

void
processKeys (GLFWwindow* window, int key, int scanCode, int action,
	     int modifiers)
{
  // Actions are GLFW_PRESS, GLFW_RELEASE, and GLFW_REPEAT
  // Exit if ESC is pressed
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose (window, GL_TRUE);
    return;
  }

  // Translate camera/eye point using WASD keys
  const float MOVEMENT_DELTA = 1.0f;
  if (key == GLFW_KEY_W && action == GLFW_PRESS)
  {
    g_camera.position.z -= MOVEMENT_DELTA;
  }
  else if (key == GLFW_KEY_S && action == GLFW_PRESS)
  {
    g_camera.position.z += MOVEMENT_DELTA;
  }
  else if (key == GLFW_KEY_A && action == GLFW_PRESS)
  {
    g_camera.position.x -= MOVEMENT_DELTA;
  }
  else if (key == GLFW_KEY_D && action == GLFW_PRESS)
  {
    g_camera.position.x += MOVEMENT_DELTA;
  }
  else if (key == GLFW_KEY_F && action == GLFW_PRESS)
  {
    g_camera.position.y += MOVEMENT_DELTA;
  }
  else if (key == GLFW_KEY_C && action == GLFW_PRESS)
  {
    g_camera.position.y -= MOVEMENT_DELTA;
  }

  if ( action == GLFW_PRESS )
  {
    cout << "Current Position = ( " 
      << g_camera.position.x << ", " 
      << g_camera.position.y << ", " 
      << g_camera.position.z << " )" << endl;
  }
  // TODO: Add support for movement along x and y axes
}

/******************************************************************/

void
releaseGlResources ()
{
  // Delete OpenGL resources, particularly important if program will
  //   continue running
  delete g_shaderProgram;
  delete g_mesh;
}

/******************************************************************/

void
outputGlfwError (int error, const char* description)
{
  fprintf (stderr, "GLFW error: %s, code %d\n", description, error);
}

/******************************************************************/
