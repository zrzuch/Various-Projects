/*
  FileName    : Mesh.h
  Author      : Zachary Zuch
  Course      : CSCI 375
  Assignment  : Lab 2
  Description : This file is the mesh header which is used to 
  				abstract the draw calls and vbo and vao creation 
  				and management.
*/

#ifndef MESH_H
#define MESH_H

#include <vector>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include "ShaderProgram.h"

using std::vector;
using glm::mat4;

class Mesh
{
public:
	Mesh ();

	~Mesh ();

	void
	addGeometry (const vector<float>& geometry);

	void
	prepareVao ();

	void
	draw ( ShaderProgram* g_shaderProgram, const mat4& modelView );

private:

	GLuint m_vao;
	GLuint m_vbo;
	vector<float> m_mesh;

	const unsigned FLOATS_PER_VERTEX = 6;
	const GLint POSITION_ATTRIB_INDEX = 0;
  	const GLint COLOR_ATTRIB_INDEX = 1;
};

#endif