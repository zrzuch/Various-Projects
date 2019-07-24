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
#include <string>
#include <GL/glew.h>

#include "ShaderProgram.h"
#include "Transform.h"
#include "Camera.h"

class Mesh
{
public:

	Mesh ();

	Mesh (const std::string& filename);

	~Mesh ();

	// Disable default copy ctor and copy assignment
  	Mesh (const Mesh&) = delete;
  	Mesh& operator= (const Mesh&) = delete;

  	// Read vertex data from a file using the AiScene class. 
	void
	importFromFile (const std::string& filename);

	void
	addGeometry (const std::vector<float>& vertices, 
		const std::vector<unsigned>& indices);

	void
	addCopy();

	void
	addCopy(unsigned num);

	void
	prepareVao ();

	void
	draw(ShaderProgram* shaderProgram, const Camera& camera);

	void
	draw(ShaderProgram* shaderProgram, const Camera& camera, 
		bool isShaderHandled);

	Transform& 
	getTransform (unsigned index);

	unsigned
	numTransforms() const;

	bool
	isEmpty() const;

private:

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;

	std::vector<float> m_vertexData;
	std::vector<unsigned> m_indices;
	std::vector<Transform> m_transforms;

	static constexpr unsigned FLOATS_PER_VERTEX = 6;
};

#endif