#version 330

const int MAX_BONES = 50;
const int BONES_PER_VERTEX = 3;

/*********************************************************/
// Vertex attributes
// Incoming position attribute for each vertex
layout (location = 0) in vec3 aPosition;
// Incoming normal attribute for each vertex
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aBoneWeight;
layout (location = 4) in ivec3 aBoneIndices;

/*********************************************************/
// Uniforms are constant for all vertices from a single
//   draw call.
// Specify world and view transform for object.
//   This matrix should contain Projection * View * World.
uniform mat4 uProjection;
uniform mat4 uModelView;
uniform mat4 uBones[MAX_BONES];
//	 Eye Space Matrix
uniform mat3 uNormalMatrix;
uniform mat4 identity;
uniform mat4 zeroMatrix = mat4(0.0f);
uniform bool hasBones;

/*********************************************************/
// Vertex Normal and Position in Eye Space
out vec3 eyeNormal;
out vec3 eyePos;
out vec2 texCoord;

void
main ()
{
	vec4 position;
	if (hasBones)
	{
		vec3 boneWeights 	= normalize(aBoneWeight);
		mat4 BoneMatrix		= mat4(0.0);
		for (int i = 0; i < BONES_PER_VERTEX; ++i)
		{
			BoneMatrix += uBones[aBoneIndices[i]] * boneWeights[i];
		}

		// 		Transform the vertex from world space to clip space
		position 		= uModelView * BoneMatrix * vec4(aPosition, 1.0);
		// Transform local/model normal to eye space.
		// Make sure matrix and vector are normalized prior to calculation to
		// 		reduce operations.
		// Normalize in Fragment Shader
		eyeNormal 		= uNormalMatrix * (BoneMatrix * vec4(aNormal, 1.0)).xyz;
	}
	else
	{
		position 		= uModelView * 	vec4(aPosition, 1.0);
		eyeNormal 		= uNormalMatrix * aNormal;
	}
	
	eyePos 			= position.xyz;
	texCoord 		= aTexCoord;
	gl_Position 	= uProjection * position;
}
