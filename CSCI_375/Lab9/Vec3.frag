#version 330

// Texture 2D Sampler
uniform sampler2D uSampler;
uniform bool uHasTexture;

// Represents a (Point / Spot / Directional) Light
struct Light
{
	// Color of the light
  	// These are diffuse, and specular light intensities
  	vec3 diffuse;
  	vec3 specular;
  	// Point or Direction
  	// Points toward the light source (which is infinitely far away)
  	// Light Direction MUST point TOWARD the light source. 
  	vec3 position;
  	vec3 direction;
  	// x * d^2 + y * d + z
  	vec3 attenuation;
  	float angleOfVisibility;
  	float falloff;
  	bool isDirect;
  	bool isActive;
};

struct Material
{
	vec3 ambientLight;
	// These are reflectances
  	vec3 ambientRefl;
  	vec3 diffuseRefl;
  	vec3 specularRefl;

  	float shininess;
};

const int lightSize = 8;
uniform Light uLight[lightSize];

uniform Material uMaterial;

// Computed vertex color outputted by the vertex shader
// Type and name must be an exact match
in vec3 eyeNormal;
in vec3 eyePos;
in vec2 texCoord;
in mat3 normalMatrix;
// Fragment color we will output
out vec4 fColor;

vec3 normalizeEyeNormal;
vec3 diffuseMaterial;
// camera is at (0,0,0) 
// 	so view is negative vertex position
vec3 viewDir;

vec3
calculateLight(int index);

void
main ()
{
	viewDir = normalize(-eyePos);
	normalizeEyeNormal = normalize(eyeNormal);
	if (uHasTexture)
	{
		diffuseMaterial = texture(uSampler, texCoord).xyz;
	}
	else
	{
		diffuseMaterial = uMaterial.diffuseRefl;
	}
	vec3 linearColor = uMaterial.ambientLight * uMaterial.ambientRefl;
	for (int i = 0; i < lightSize; ++i)
	{
		if (uLight[i].isActive)
		{
			linearColor += calculateLight(i);
		}
	}
	// Output fragment color, with red, green, blue, and alpha components (RGBA)
	fColor = vec4(clamp(linearColor, 0.0, 1.0), 1.0);
}

vec3
calculateLight(int index)
{
	vec3 lightVector;
	vec3 distance;
	if (uLight[index].isDirect)
	{
		lightVector = normalize(uLight[index].direction);
	}
	else
	{
		distance = uLight[index].position - eyePos;
		lightVector = normalize(distance);
	}
	
	// 		How directly is the light shining on the surface? DIFF
	// 		Ensure brightness is between 0 and 1
	float lambertianCoef = dot(lightVector, normalizeEyeNormal);
	
	vec3 diffuse_specular = vec3(0.0);
	if (lambertianCoef > 0.0)
	{
		// diffuse calculation
		diffuse_specular   	+= lambertianCoef * uLight[index].diffuse * diffuseMaterial;
		vec3 reflection 	= reflect(-lightVector, normalizeEyeNormal);

		// Vector pointing toward the eye (0, 0, 0)
		float cosAngle = dot(viewDir, reflection);
		// Replaced max call since it is only used to guage if Specular component is 0
		if (cosAngle > 0.0)
		{
			float specularCoefficient = pow(cosAngle, uMaterial.shininess);
			// specular calculation
			diffuse_specular 	+= specularCoefficient * uLight[index].specular * uMaterial.specularRefl;
		}
		
		if (!uLight[index].isDirect)
		{
			if (uLight[index].angleOfVisibility > 0.0f)
			{
				float cosTheta = dot (-lightVector, normalize(uLight[index].direction));
      			if (cosTheta >= uLight[index].angleOfVisibility)
      			{
      				diffuse_specular *= pow(cosTheta, uLight[index].falloff);
      			}
      			else
      			{
      				return vec3(0);
      			}
			}
			float d2 = dot(distance, distance);
			float d = sqrt(d2);
			float atten = 1.0f / (( uLight[index].attenuation.x * d2 )
								+ ( uLight[index].attenuation.y * d  )
								+   uLight[index].attenuation.z	   	 );
			diffuse_specular *= atten;
		}
	}
	return diffuse_specular;
}
