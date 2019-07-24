/*
  FileName    : Mesh.h
  Author      : Zachary Zuch
  Course      : CSCI 375
  Assignment  : Lab 2
  Description : This file is the mesh soure file which has the implementation
  				of the draw calls and vbo and vao creation and management.
*/

#include <vector>
#include <iterator>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include "ShaderProgram.h"
#include "Mesh.h"

using std::vector;
using glm::mat4;
using std::end;
using std::begin;

// Initialize the mesh. Generate a VAO and VBO.
// Use member initializers when possible.
Mesh::Mesh ()
	: m_vao(), m_vbo(), m_mesh()
{
	 glGenVertexArrays ( 1, &m_vao );
	 glGenBuffers ( 1, &m_vbo );	
}

// Free allocated resources. Delete generated VAO and VBO. 
Mesh::~Mesh ()
{
	glDeleteVertexArrays ( 1, &m_vao );
	glDeleteBuffers ( 1, &m_vbo );
}

// Append geometry to the mesh.
// Do NOT buffer the data in a VBO until "prepareVao" is called. 
void
Mesh::addGeometry (const vector<float>& geometry)
{	
	m_mesh.insert( end( m_mesh ) , begin( geometry ), end( geometry ));
}

// Set the state of the VAO for rendering.
// Bind VAO, VBO, buffer the data, etc.
void
Mesh::prepareVao ()
{
	glBindVertexArray ( m_vao );
	glBindBuffer ( GL_ARRAY_BUFFER, m_vbo );
		
	glBufferData ( GL_ARRAY_BUFFER, m_mesh.size() * sizeof(float),
		m_mesh.data(), GL_STATIC_DRAW );

	glEnableVertexAttribArray (POSITION_ATTRIB_INDEX);
	glVertexAttribPointer (POSITION_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 
		FLOATS_PER_VERTEX * sizeof(float), reinterpret_cast<void*> ( 0 ));

	glEnableVertexAttribArray (COLOR_ATTRIB_INDEX);
 	glVertexAttribPointer (COLOR_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 
 		FLOATS_PER_VERTEX * sizeof(float), 
 		reinterpret_cast<void*> ( 3 * sizeof(float)));

	glBindVertexArray (0);
}

// Draw the mesh.
// Determine the appropriate parameters.
// Enable the shader program, set the model-view uniform, etc. 
void
Mesh::draw ( ShaderProgram* g_shaderProgram, const mat4& modelView )
{
	g_shaderProgram->enable ();
	g_shaderProgram->setUniformMatrix ( "uModelView", modelView );
	
	glBindVertexArray( m_vao );
	glDrawArrays ( GL_TRIANGLES, 0, m_mesh.size() / FLOATS_PER_VERTEX );
	glBindVertexArray ( 0 );

	g_shaderProgram->disable ();
}