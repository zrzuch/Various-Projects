/*
  FileName    : Mesh.h
  Author      : Zachary Zuch
  Course      : CSCI 375
  Assignment  : Lab 3
  Description : This file is the mesh soure file which has the implementation
  				of the draw calls and vbo and vao creation and management.
*/
#include "Mesh.h"
#include <iostream>

// Initialize the mesh. Generate a VAO and VBO.
Mesh::Mesh (const std::vector<float>& vertexData,  const std::vector<unsigned>& indices, 
			const std::vector<float>& boneWeights, const std::vector<unsigned>& boneIndices)
	: textureFilePath("")
	, m_vao				( )
	, m_vbo 			( )
	, m_ibo				( )
	, m_vboBoneWeight	( )
	, m_vboBoneIndex	( )
	, m_vertexData		(vertexData)
	, m_indices 		(indices)
	, m_boneWeights		(boneWeights)
	, m_boneIndices		(boneIndices)
{
	 glGenVertexArrays ( 1, &m_vao );
	 glGenBuffers ( 1, &m_vbo );
	 if (!isBoneless())
	 {
	 	glGenBuffers ( 1, &m_vboBoneWeight );
	 	glGenBuffers ( 1, &m_vboBoneIndex );
	 }
	 glGenBuffers ( 1, &m_ibo );
}

// Free allocated resources. Delete generated VAO and VBO. 
Mesh::~Mesh ()
{
	glDeleteVertexArrays ( 1, &m_vao );
	glDeleteBuffers ( 1, &m_vbo );
	if (!isBoneless())
	{
	 	glDeleteBuffers ( 1, &m_vboBoneWeight );
		glDeleteBuffers ( 1, &m_vboBoneIndex );
	}
	glDeleteBuffers ( 1, &m_ibo );
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

void
Mesh::addBoneData(const std::vector<float   >& boneWeights, 
			const std::vector<unsigned>& boneIndices)
{
	m_boneWeights.insert(m_boneWeights.end(), boneWeights.begin(), boneWeights.end());
	m_boneIndices.insert(m_boneIndices.end(), boneIndices.begin(), boneIndices.end());
}

// Set the state of the VAO for rendering.
// Bind VAO, VBO, buffer the data, etc.
void
Mesh::prepareVao ()
{
	constexpr GLint POSITION_ATTRIB_INDEX = 0;
  	constexpr GLint NORMAL_ATTRIB_INDEX = 1;
  	constexpr GLint TEXCOORD_ATTRIB_INDEX = 2;
  	constexpr GLint BONE_WEIGHT_ATTRIB_INDEX = 3;
  	constexpr GLint BONE_INDEX_ATTRIB_INDEX = 4;

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

 	glEnableVertexAttribArray (TEXCOORD_ATTRIB_INDEX);
 	glVertexAttribPointer (TEXCOORD_ATTRIB_INDEX, 2, GL_FLOAT, GL_FALSE, 
 		FLOATS_PER_VERTEX * sizeof(float), 
 		reinterpret_cast<void*> ( 6 * sizeof(float)));

	if (!isBoneless())
	{
		// Buffer Bone Weights
		glBindBuffer ( GL_ARRAY_BUFFER, m_vboBoneWeight );
	 	glBufferData ( GL_ARRAY_BUFFER, m_boneWeights.size() * sizeof(float),
			m_boneWeights.data(), GL_STATIC_DRAW );

	 	glEnableVertexAttribArray	(BONE_WEIGHT_ATTRIB_INDEX);
	 	glVertexAttribPointer 		(BONE_WEIGHT_ATTRIB_INDEX, NUM_BONE_INDICES, GL_FLOAT, GL_FALSE, 
	 		NUM_BONE_INDICES * sizeof(float), reinterpret_cast<void*> (0));

	 	// Buffer Bone Indices
	 	glBindBuffer ( GL_ARRAY_BUFFER, m_vboBoneIndex );
	 	glBufferData ( GL_ARRAY_BUFFER, m_boneIndices.size() * sizeof(unsigned),
			m_boneIndices.data(), GL_STATIC_DRAW );

	 	glEnableVertexAttribArray 	(BONE_INDEX_ATTRIB_INDEX);
	 	glVertexAttribIPointer 		(BONE_INDEX_ATTRIB_INDEX, NUM_BONE_INDICES, GL_UNSIGNED_INT, 
	 		NUM_BONE_INDICES * sizeof(float), reinterpret_cast<void*> (0));
	}
		
 	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, m_ibo );
	glBufferData ( GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned),
		m_indices.data(), GL_STATIC_DRAW );

	glBindVertexArray (0);
}

// Precondition: Shader Program is enabled and uniforms are set
void
Mesh::draw()
{
	glBindVertexArray( m_vao );
	glDrawElements ( GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 
		reinterpret_cast<void*> (0));
	glBindVertexArray(0);
}

unsigned
Mesh::numIndices() const
{
	return m_indices.size();
}

unsigned
Mesh::numVertices() const
{
	return m_vertexData.size() / FLOATS_PER_VERTEX;
}

bool
Mesh::isEmpty() const
{
	return numVertices() == 0;
}

bool
Mesh::isBoneless() const
{
	return m_boneWeights.size() == 0 || m_boneIndices.size() == 0;
}

bool
Mesh::hasTexture() const
{
	return textureFilePath != "";
}

Vector3
Mesh::getMeshCenter() const
{
	Vector3 sum;
	unsigned n;
	for ( n = 0; n * FLOATS_PER_VERTEX < m_vertexData.size(); ++n )
	{
		sum.x += m_vertexData[ FLOATS_PER_VERTEX * n ];
		sum.y += m_vertexData[ FLOATS_PER_VERTEX * n + 1 ];
		sum.z += m_vertexData[ FLOATS_PER_VERTEX * n + 2 ];
	} 

	sum /= n;
	return sum;
}

// Radial Length from a point
float
Mesh::getRadius(SphereBV sphere)
{
	for ( unsigned n = 0; n * FLOATS_PER_VERTEX < m_vertexData.size(); ++n )
	{
		Vector3 vertexDistance( m_vertexData[ FLOATS_PER_VERTEX * n ],		// x
								m_vertexData[ FLOATS_PER_VERTEX * n + 1 ],	// y
								m_vertexData[ FLOATS_PER_VERTEX * n + 2 ]); // z
		vertexDistance -= sphere.center;

		float vertexLength = vertexDistance.length();
		if ( vertexLength > sphere.radius )
		{
			sphere.radius = vertexLength;
		}
	}
	return sphere.radius;
}

// Left Right Bottom Top Near Far
void
Mesh::getBoxBV(std::vector<float>& lrbtnf)
{
	for ( unsigned n = 0; n * FLOATS_PER_VERTEX < m_vertexData.size(); ++n )
	{
		float x = m_vertexData[ FLOATS_PER_VERTEX * n ];
		float y = m_vertexData[ FLOATS_PER_VERTEX * n + 1 ];
		float z = m_vertexData[ FLOATS_PER_VERTEX * n + 2 ];

		if ( x < lrbtnf[0] ) lrbtnf[0] = x;
		if ( x > lrbtnf[1] ) lrbtnf[1] = x;
		if ( y < lrbtnf[2] ) lrbtnf[2] = y;
		if ( y > lrbtnf[3] ) lrbtnf[3] = y;
		if ( z < lrbtnf[4] ) lrbtnf[4] = z;
		if ( z > lrbtnf[5] ) lrbtnf[5] = z;
	}
}