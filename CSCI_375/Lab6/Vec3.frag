#version 330

// Computed vertex color outputted by the vertex shader
// Type and name must be an exact match
in  vec3 vColor;
// Fragment color we will output
out vec4 fColor;

void
main ()
{
  // Output fragment color, with red, green, blue, and alpha components (RGBA)
  fColor = vec4 (vColor, 1.0);
}
