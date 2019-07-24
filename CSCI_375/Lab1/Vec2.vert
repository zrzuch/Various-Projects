#version 330

// Only vertex shaders have attributes
// Incoming position attribute for each vertex
layout (location = 0) in vec2 aPosition;
// Incoming color attribute for each vertex
layout (location = 1) in vec4 aColor;
// Vertex color we will output
out vec4 vColor;

void
main ()
{
  // Every vertex shader must write gl_Position
  gl_Position = vec4 (aPosition, 0.0, 1.0f);
  vColor = aColor;
}
