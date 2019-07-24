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

	void
	addGeometry (const std::vector<float>& geometry);

	void
	prepareVao ();

	void
	draw ( ShaderProgram* g_shaderProgram, Camera& camera );

private:

	GLuint m_vao;
	GLuint m_vbo;
	std::vector<float> m_mesh;

	const static unsigned FLOATS_PER_VERTEX = 6;
};

#endif