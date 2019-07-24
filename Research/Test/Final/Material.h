#pragma once

#include "Vector3.h"
#include "ShaderProgram.h"

class Material
{
public:

	Material();

	Material(Vector3 ambient, Vector3 ambientR = Vector3(0), Vector3 diffuseR = Vector3(0), 
		Vector3 specularR = Vector3(0), float shine = 0);

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