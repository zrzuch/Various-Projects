#pragma once

#include "Vector3.h"
#include "ShaderProgram.h"

class Material
{
public:

	Material();

	~Material() = default;

	void
	setUniforms(ShaderProgram* shaderProgram);

	// Ambient Light recieved from the material
	Vector3 ambientLight;
	// These are reflectances
  	Vector3 ambientRefl;
  	Vector3 diffuseRefl;
  	Vector3 specularRefl;
  	float 	shininess;
};