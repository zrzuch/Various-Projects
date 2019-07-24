#include "Material.h"

Material::Material()
	: ambientLight	(0.1)
  	, ambientRefl	(0.5)
  	, diffuseRefl	(1 )
  	, specularRefl	(1 )
  	, shininess		(16)
{ }

Material::Material(Vector3 ambient, Vector3 ambientR, Vector3 diffuseR, Vector3 specularR, float shine)
	: ambientLight	(ambient)
  	, ambientRefl	(ambientR)
  	, diffuseRefl	(diffuseR)
  	, specularRefl	(specularR)
  	, shininess		(shine)
{ }

void
Material::setUniforms(ShaderProgram* shaderProgram)
{
	shaderProgram->setUniform("uMaterial.ambientLight", ambientLight);

	shaderProgram->setUniform("uMaterial.ambientRefl", 	ambientRefl);

	shaderProgram->setUniform("uMaterial.diffuseRefl", 	diffuseRefl);

	shaderProgram->setUniform("uMaterial.specularRefl", specularRefl);

	shaderProgram->setUniform("uMaterial.shininess", 	shininess);
}