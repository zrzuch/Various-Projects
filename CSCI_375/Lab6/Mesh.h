/*
  FileName    : Mesh.h
  Author      : Zachary Zuch
  Course      : CSCI 375
  Assignment  : Lab 3
  Description : This file is the mesh header which is used to 
  				abstract the draw calls and vbo and vao creation 
  				and management.
*/

#ifndef MESH_H
#define MESH_H

#include <vector>
#include <GL/glew.h>

#include "ShaderProgram.h"
#include "Camera.h"

class Mesh
{
public:
	Mesh ();

	~Mesh ();

	// Disable default copy ctor and copy assignment
  	Mesh (const Mesh&) = delete;
  	Mesh& operator= (const Mesh&) = delete;

  	// Read vertex data from a file using the AiScene class. 
	void
	importFromFile (const std::string& filename);

	void
	reset();

	// Key: "1"
	void
	moveRight (float distance);

	// Key: "2"
	void
	moveUp (float distance);

	void
	moveBack (float distance);

	void
	moveLocal (float distance, const Vector3& localDirection);

	// Key: "3"
	void
	moveWorld (float distance, const Vector3& worldDirection);

	// Key: "4"
	void
	pitch (float angleDegrees);

	// Key: "5"
	void
	yaw (float angleDegrees);

	// Key: "6"
	void
	roll (float angleDegrees);

	void
	rotateLocal (float angleDegrees, const Vector3& axis);

	// Key: "7"
	void
	alignWithWorldY ();

	// Key: "8"
	void
	scaleLocal (float scale);

	void
	scaleLocal (float scaleX, float scaleY, float scaleZ);
	    
	// Key: "9"
	void
	scaleWorld (float scale);

	void
	scaleWorld (float scaleX, float scaleY, float scaleZ);

	// Key: "0"
	void
	shearLocalXByYz (float shearY, float shearZ);

	void
	shearLocalYByXz (float shearX, float shearZ);

	void
	shearLocalZByXy (float shearX, float shearY);

	void
	addGeometry (const std::vector<float>& vertices, 
		const std::vector<unsigned>& indices);

	void
	prepareVao ();

	void
	draw ( ShaderProgram* g_shaderProgram, const Camera& camera );

private:

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;

	std::vector<float> m_vertexData;
	std::vector<unsigned> m_indices;

	Transform m_world;

	const static unsigned FLOATS_PER_VERTEX = 6;
};

#endif