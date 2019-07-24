/*
  FileName    : Mesh.h
  Author      : Zachary Zuch
  Course      : CSCI 375
  Assignment  : Lab 3
  Description : This file is the mesh soure file which has the implementation
  				of the draw calls and vbo and vao creation and management.
*/
#include <string>
#include <iostream>

#include "Mesh.h"
#include "AiScene.h"
#include "Matrix4.h"

// Initialize the mesh. Generate a VAO and VBO.
Mesh::Mesh ()
	: m_vao()
	, m_vbo()
	, m_ibo()
	, m_vertexData()
	, m_indices()
	, m_transforms()
{
	 glGenVertexArrays ( 1, &m_vao );
	 glGenBuffers ( 1, &m_vbo );
	 glGenBuffers ( 1, &m_ibo );		
}

Mesh::Mesh (const std::string& filename)
	: m_vao()
	, m_vbo()
	, m_ibo()
	, m_vertexData()
	, m_indices()
	, m_transforms()
{
	 glGenVertexArrays ( 1, &m_vao );
	 glGenBuffers ( 1, &m_vbo );
	 glGenBuffers ( 1, &m_ibo );
	 importFromFile ( filename );
}

// Free allocated resources. Delete generated VAO and VBO. 
Mesh::~Mesh ()
{
	glDeleteVertexArrays ( 1, &m_vao );
	glDeleteBuffers ( 1, &m_vbo );
	glDeleteBuffers ( 1, &m_ibo );
}

// Read vertex data from a file using the AiScene class. 
void
Mesh::importFromFile (const std::string& filename)
{
	AiScene scene(filename);
	std::vector<float> vertexData = scene.getAllVertexData();
	std::vector<unsigned> indices = scene.getAllFaceIndices();
	addGeometry(vertexData, indices);
	m_transforms.push_back(Transform());
}

void
Mesh::addGeometry (const std::vector<float>& vertices, 
	const std::vector<unsigned>& indices)
{
	unsigned beginSize = m_indices.size();
	m_indices.insert(m_indices.end(), indices.begin(), indices.end());
	if ( m_vertexData.size() != 0 )
	{
		for (unsigned i = beginSize; i < m_indices.size(); ++i)
		{
			m_indices[i] += m_vertexData.size();
		}	
	}
	m_vertexData.insert(m_vertexData.end(), vertices.begin(), vertices.end());
}

// Set the state of the VAO for rendering.
// Bind VAO, VBO, buffer the data, etc.
void
Mesh::prepareVao ()
{
	constexpr GLint POSITION_ATTRIB_INDEX = 0;
  	constexpr GLint NORMAL_ATTRIB_INDEX = 1;

	glBindVertexArray ( m_vao );

	glBindBuffer ( GL_ARRAY_BUFFER, m_vbo );
	glBufferData ( GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float),
		m_vertexData.data(), GL_STATIC_DRAW );

	glEnableVertexAttribArray (POSITION_ATTRIB_INDEX);
	glVertexAttribPointer (POSITION_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 
		FLOATS_PER_VERTEX * sizeof(float), reinterpret_cast<void*> (0));

	glEnableVertexAttribArray (NORMAL_ATTRIB_INDEX);
 	glVertexAttribPointer (NORMAL_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, 
 		FLOATS_PER_VERTEX * sizeof(float), 
 		reinterpret_cast<void*> ( 3 * sizeof(float)));

 	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, m_ibo );
	glBufferData ( GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned),
		m_indices.data(), GL_STATIC_DRAW );

	glBindVertexArray (0);
}

// Enable the shader program --> Set the model-view and projection uniform
// --> Bind VAO --> DrawArrays --> Unbind --> Disable the shader program 
void
Mesh::draw(ShaderProgram* shaderProgram, const Camera& camera)
{
	shaderProgram->enable ();
	draw(shaderProgram, camera, true);
	shaderProgram->disable ();
}

// Precondition: Shader Program is enabled, disabled, 
//	and Eye Matric Uniform is set by the caller
void
Mesh::draw(ShaderProgram* shaderProgram, const Camera& camera, bool isShaderHandled)
{
	for (const Transform& world : m_transforms)
	{
		Transform worldView = camera.getViewMatrix();
		worldView.combine(world);
		Matrix3 normalMatrix = worldView.getOrientation();
		shaderProgram->setUniformMatrix ("uCameraPosition", 
			normalMatrix * worldView.getPosition());
		normalMatrix.invert();
		normalMatrix.transpose();
		shaderProgram->setUniformMatrix ("uNormalMatrix", normalMatrix);

		Matrix4 projectionViewWorld = camera.getProjectionMatrix();
		projectionViewWorld *= worldView.getTransform();
		shaderProgram->setUniformMatrix ("uProjectionViewWorld", 
			projectionViewWorld);

		glBindVertexArray( m_vao );
		glDrawElements ( GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 
			reinterpret_cast<void*> (0));
		glBindVertexArray(0);
	}
}

void
Mesh::addCopy()
{
	m_transforms.push_back(Transform());
}

void
Mesh::addCopy(unsigned num)
{
	std::vector<Transform> transforms(num);
	m_transforms.insert(m_transforms.end(), transforms.begin(), transforms.end());
}

Transform& 
Mesh::getTransform (unsigned index)
{
	return m_transforms[index];
}

unsigned
Mesh::numTransforms() const
{
	return m_transforms.size();
}

bool
Mesh::isEmpty() const
{
	return numTransforms() == 0;
}