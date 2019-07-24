#version 330

/*********************************************************/
// Vertex attributes
// Only vertex shaders have attributes
// Incoming position attribute for each vertex
layout (location = 0) in vec3 aPosition;
// Incoming color attribute for each vertex
layout (location = 1) in vec3 aColor;

/*********************************************************/
// Uniforms are constant for all vertices from a single
//   draw call.
// Specify world and view transform for object
uniform mat4 uModelView;
// Specify projection
uniform mat4 uProjection;

// Vertex color we will output
out vec3 vColor;

/*********************************************************/

void
main ()
{
  // Transform the vertex from world space to clip space
  gl_Position = uProjection * uModelView * vec4 (aPosition, 1.0);
  vColor = aColor;
}
