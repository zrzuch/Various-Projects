#version 330
// We are using a single directional light to illuminate
//   our scene. 
// You can modify these parameters for your model.
// "uLightDir" MUST point TOWARD the light source. 
// uniform vec3 uLightDir = vec3 (0, 0, 1);
uniform vec3 uLightSource;
uniform vec3 uCameraPosition;
// Color of the light
uniform vec3 uLightIntensity;
uniform vec3 uAmbientCoefficient = vec3(0.1);
uniform vec3 uObjectColor = vec3(1);
uniform vec3 uMaterialSpecularColor = vec3(1);
uniform float uMaterialShininess = 32;

// Computed vertex color outputted by the vertex shader
// Type and name must be an exact match
in vec3 eyeNormal;
in vec3 eyePos;
// Fragment color we will output
out vec4 fColor;

void
main ()
{
	vec3 lightDir = normalize(uLightSource - eyePos);
	// 		How directly is the light shining on the surface? DIFF
	// 		Ensure brightness is between 0 and 1
	float diffuseCoefficient = clamp(dot (eyeNormal, lightDir), 0.0, 1.0);

	vec3 incidence = lightDir;
	vec3 reflection = reflect(incidence, eyeNormal);
	vec3 surfaceToCamera = normalize(uCameraPosition - eyePos);
	float cosAngle = max(0.0, dot(surfaceToCamera, reflection));
	float specularCoefficient = pow(cosAngle, uMaterialShininess);

	vec3 specular = specularCoefficient * uMaterialSpecularColor;
	vec3 ambient_diffuse = (uAmbientCoefficient + diffuseCoefficient) * uObjectColor;

	// Output fragment color, with red, green, blue, and alpha components (RGBA)
	fColor = vec4((ambient_diffuse + specular) * uLightIntensity, 1.0);
}
