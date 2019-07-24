#version 330
// We are using a single directional light to illuminate
//   our scene. 
// You can modify these parameters for your model.
// "uLightDir" MUST point TOWARD the light source. 
uniform vec3 uLightDir;
// Color of the light
uniform vec3 uLightIntensity;

// Computed vertex color outputted by the vertex shader
// Type and name must be an exact match
in vec3 eyeNormal;
// Fragment color we will output
out vec4 fColor;

void
main ()
{
	// 		How directly is the light shining on the surface? DIFF
	// 		Ensure brightness is between 0 and 1
	float diffuseCoefficient = clamp(dot (eyeNormal, normalize(uLightDir)), 0.0, 1.0);

	// Output fragment color, with red, green, blue, and alpha components (RGBA)
	fColor = vec4(diffuseCoefficient * uLightIntensity, 1.0);
}
