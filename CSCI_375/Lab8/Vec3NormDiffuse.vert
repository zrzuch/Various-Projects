#version 330

/*********************************************************/
// Vertex attributes
// Incoming position attribute for each vertex
layout (location = 0) in vec3 aPosition;
// Incoming normal attribute for each vertex
layout (location = 1) in vec3 aNormal;

/*********************************************************/
// Uniforms are constant for all vertices from a single
//   draw call.
// Specify world and view transform for object.
//   This matrix should contain Projection * View * World.
uniform mat4 uProjectionViewWorld;
//	 Eye Space Matrix
uniform mat3 uNormalMatrix;

/*********************************************************/
// Vertex Normal and Position in Eye Space
out vec3 eyeNormal;

void
main ()
{
	// 		Transform the vertex from world space to clip space
	gl_Position = uProjectionViewWorld * vec4 (aPosition, 1.0);
	// 		Transform local/model normal to eye space.
	// 		Make sure matrix and vector are normalized prior to calculation to
	// 			reduce operations.
	eyeNormal = normalize(uNormalMatrix * aNormal);
}
// tutorial used as a source
// https://github.com/SonarSystems/Modern-OpenGL-Tutorials/blob/master/%5BLIGHTING%5D/%5B8%5D%20Basic%20Lighting/res/shaders/lighting.frag