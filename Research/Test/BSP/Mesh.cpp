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
			const std::string&	texturePath, 
			const std::vector<float>& boneWeights, const std::vector<unsigned>& boneIndices)
	: textureFilePath(texturePath)
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

	 // FLOATS_PER_VERTEX = (hasTexture()) ? 8 : 6;
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
void
Mesh::getRadius(SphereBV& sphere)
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

Vector3
Mesh::getMassSum()
{
	Vector3 sum;
	for (unsigned n = 0; n * FLOATS_PER_VERTEX < m_vertexData.size(); ++n)
	{
		sum.x += m_vertexData[ FLOATS_PER_VERTEX * n ];
		sum.y += m_vertexData[ FLOATS_PER_VERTEX * n + 1 ];
		sum.z += m_vertexData[ FLOATS_PER_VERTEX * n + 2 ];
	}
	return sum;
}

Matrix3
Mesh::getCovarianceMatrix(const Vector3& mean)
{
	Matrix3 covarianceMatrix = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	constexpr unsigned MATRIX_MAX = 3;
	for (unsigned i = 0; i < MATRIX_MAX; ++i)
	{
		for (unsigned j = 0; j < MATRIX_MAX; ++j)
		{
			unsigned n = 0;
			for (; n * FLOATS_PER_VERTEX < m_vertexData.size(); ++n)
			{
				covarianceMatrix.getValue(i, j) += 
					((mean[i] - m_vertexData[ FLOATS_PER_VERTEX * n + i ]) * 
					 (mean[j] - m_vertexData[ FLOATS_PER_VERTEX * n + j ]));
			}
			covarianceMatrix.getValue(i, j) /= (n - 1);
		}
	}
}

// first  = front
// second = back
std::pair<Mesh*, Mesh*>
Mesh::split(Plane& splitter)
{
	std::vector<float> 		frontVertexData;
	std::vector<unsigned> 	frontOldIndices;
	std::vector<unsigned> 	frontIndices;

	std::vector<float> 		backVertexData;
	std::vector<unsigned> 	backOldIndices;
	std::vector<unsigned> 	backIndices;

	Vector3 temp;

	for (unsigned numVertex = 0; numVertex * FLOATS_PER_VERTEX < m_vertexData.size(); ++numVertex)
	{
		temp = 
		{
			m_vertexData[ FLOATS_PER_VERTEX * numVertex     ],
			m_vertexData[ FLOATS_PER_VERTEX * numVertex + 1 ],
			m_vertexData[ FLOATS_PER_VERTEX * numVertex + 2 ]
		};

		if (splitter.dist(temp) >= 0)
		{
			frontVertexData.insert(frontVertexData.end(), 
			{
				m_vertexData[ FLOATS_PER_VERTEX * numVertex     ],
				m_vertexData[ FLOATS_PER_VERTEX * numVertex + 1 ],
				m_vertexData[ FLOATS_PER_VERTEX * numVertex + 2 ],
				m_vertexData[ FLOATS_PER_VERTEX * numVertex + 3 ],
				m_vertexData[ FLOATS_PER_VERTEX * numVertex + 4 ],
				m_vertexData[ FLOATS_PER_VERTEX * numVertex + 5 ],
				m_vertexData[ FLOATS_PER_VERTEX * numVertex + 6 ],
				m_vertexData[ FLOATS_PER_VERTEX * numVertex + 7 ]
			});
			frontOldIndices.push_back(numVertex);
		}
		else
		{
			backVertexData.insert(backVertexData.end(), 
			{
				m_vertexData[ FLOATS_PER_VERTEX * numVertex     ],
				m_vertexData[ FLOATS_PER_VERTEX * numVertex + 1 ],
				m_vertexData[ FLOATS_PER_VERTEX * numVertex + 2 ],
				m_vertexData[ FLOATS_PER_VERTEX * numVertex + 3 ],
				m_vertexData[ FLOATS_PER_VERTEX * numVertex + 4 ],
				m_vertexData[ FLOATS_PER_VERTEX * numVertex + 5 ],
				m_vertexData[ FLOATS_PER_VERTEX * numVertex + 6 ],
				m_vertexData[ FLOATS_PER_VERTEX * numVertex + 7 ]
			});
			backOldIndices.push_back(numVertex);
		}
		// Calculate new indices and clip and make new vertices and indices
	}
	constexpr unsigned INDICES_PER_TRIANGLE = 3; 
	for (unsigned numTriangles = 0; numTriangles * INDICES_PER_TRIANGLE < m_indices.size(); ++numTriangles)
	{
		unsigned A = m_indices[ INDICES_PER_TRIANGLE * numTriangles     ];
		unsigned B = m_indices[ INDICES_PER_TRIANGLE * numTriangles + 1 ];
		unsigned C = m_indices[ INDICES_PER_TRIANGLE * numTriangles + 2 ];

		// Improve search algorithm
		std::pair<bool, unsigned> isAFront = isIn(frontOldIndices, A);
		std::pair<bool, unsigned> isBFront = isIn(frontOldIndices, B);
		std::pair<bool, unsigned> isCFront = isIn(frontOldIndices, C);
		bool isAllFront =   isAFront.first  &&   isBFront.first  &&   isCFront.first;
		bool isAllBack  = (!isAFront.first) && (!isBFront.first) && (!isCFront.first);

		if (isAllFront)
		{
			frontIndices.insert(frontIndices.end(), 
			{
				isAFront.second,
				isBFront.second,
				isCFront.second
			});
		}
		else if (isAllBack)
		{
			std::pair<bool, unsigned> isABack = isIn(backOldIndices, A);
			std::pair<bool, unsigned> isBBack = isIn(backOldIndices, B);
			std::pair<bool, unsigned> isCBack = isIn(backOldIndices, C);
			backIndices.insert(backIndices.end(), 
			{
				isABack.second,
				isBBack.second,
				isCBack.second
			});
		}
		else
		{
			// Split Polygon Case

			// Vertex Positions

			// ORDER : A -> B -> C
			Vector3 aPosition = 
			{
				m_vertexData[ FLOATS_PER_VERTEX * A     ],
				m_vertexData[ FLOATS_PER_VERTEX * A + 1 ],
				m_vertexData[ FLOATS_PER_VERTEX * A + 2 ],
			};
			Vector3 bPosition = 
			{
				m_vertexData[ FLOATS_PER_VERTEX * B     ],
				m_vertexData[ FLOATS_PER_VERTEX * B + 1 ],
				m_vertexData[ FLOATS_PER_VERTEX * B + 2 ],
			};
			Vector3 cPosition = 
			{
				m_vertexData[ FLOATS_PER_VERTEX * C     ],
				m_vertexData[ FLOATS_PER_VERTEX * C + 1 ],
				m_vertexData[ FLOATS_PER_VERTEX * C + 2 ],
			};

			if (isAFront)
			{
				if (isBFront)
				{
					// C is solo on the back
					std::pair<bool, unsigned> isCBack = isIn(backOldIndices, C);
					Vector3 CtoA = aPosition;
					CtoA 		-= cPosition;
					Vector3 CtoB = bPosition;
					CtoB 		-= cPosition;

					Vector3 CtoAPoint = splitter.pointIntersection(cPosition, CtoA);
					Vector3 CtoBPoint = splitter.pointIntersection(cPosition, CtoB);

					// BACK
					backIndices.insert(backIndices.end(), 
					{
						backVertexData.size(),
						backVertexData.size() + 1,
						isCBack.second
					});
					backVertexData.insert(backVertexData.end(), 
					{
						CtoAPoint,
						CtoBPoint
					});

					// FRONT
					frontIndices.insert(frontIndices.end(), 
					{
						// Triangle 1
						isAFront.second,
						isBFront.second,
						frontVertexData.size(),

						// Triangle 2
						frontVertexData.size(),
						isBFront.second,
						frontVertexData.size() + 1
					});
					frontVertexData.insert(frontVertexData.end(), 
					{
						CtoAPoint,
						CtoBPoint
					});
				}
				else if (isCFront)
				{
					// B is solo on Back
					std::pair<bool, unsigned> isBBack = isIn(backOldIndices, B);
					Vector3 BtoA = aPosition;
					BtoA 		-= bPosition;
					Vector3 BtoC = cPosition;
					BtoC 		-= bPosition;

					Vector3 BtoAPoint = splitter.pointIntersection(bPosition, BtoA);
					Vector3 BtoCPoint = splitter.pointIntersection(bPosition, BtoC);

					// BACK
					backIndices.insert(backIndices.end(), 
					{
						backVertexData.size(),
						isBBack.second,
						backVertexData.size() + 1
					});
					backVertexData.insert(backVertexData.end(), 
					{
						BtoAPoint,
						BtoCPoint
					});

					// FRONT
					frontIndices.insert(frontIndices.end(), 
					{
						// Triangle 1
						isAFront.second,
						frontVertexData.size(),
						isCFront.second,

						// Triangle 2
						frontVertexData.size(),
						frontVertexData.size() + 1,
						isCFront.second
					});
					frontVertexData.insert(frontVertexData.end(), 
					{
						BtoAPoint,
						BtoCPoint
					});
				}
				else
				{
					// A is solo on Front
					std::pair<bool, unsigned> isBBack = isIn(backOldIndices, B);
					std::pair<bool, unsigned> isCBack = isIn(backOldIndices, C);

					Vector3 AtoB = bPosition;
					AtoB 		-= aPosition;
					Vector3 AtoC = cPosition;
					AtoC 		-= aPosition;

					Vector3 AtoBPoint = splitter.pointIntersection(bPosition, AtoB);
					Vector3 AtoCPoint = splitter.pointIntersection(bPosition, AtoC);

					// BACK
					frontIndices.insert(frontIndices.end(), 
					{
						isAFront.second,
						frontVertexData.size(),
						frontVertexData.size() + 1
					});
					frontVertexData.insert(frontVertexData.end(), 
					{
						AtoBPoint,
						AtoCPoint
					});

					// FRONT
					backIndices.insert(backIndices.end(), 
					{
						// Triangle 1
						backVertexData.size(),
						isBBack.second,
						isCBack.second,

						// Triangle 2
						backVertexData.size() + 1,
						backVertexData.size(),
						isCBack.second
					});
					backVertexData.insert(backVertexData.end(), 
					{
						AtoBPoint,
						AtoCPoint
					});
				}
			}
			else if (isBFront)
			{
				std::pair<bool, unsigned> isABack = isIn(backOldIndices, A);
				if (isCFront)
				{
					// A is solo on Back
					Vector3 AtoB = bPosition;
					AtoB 		-= aPosition;
					Vector3 AtoC = cPosition;
					AtoC 		-= aPosition;

					Vector3 AtoBPoint = splitter.pointIntersection(bPosition, AtoB);
					Vector3 AtoCPoint = splitter.pointIntersection(bPosition, AtoC);

					// BACK
					backIndices.insert(backIndices.end(), 
					{
						isABack.second,
						backVertexData.size(),
						backVertexData.size() + 1
					});
					backVertexData.insert(backVertexData.end(), 
					{
						AtoBPoint,
						AtoCPoint
					});

					// FRONT
					frontIndices.insert(frontIndices.end(), 
					{
						// Triangle 1
						frontVertexData.size(),
						isBFront.second,
						isCFront.second,

						// Triangle 2
						frontVertexData.size() + 1,
						frontVertexData.size(),
						isCFront.second
					});
					frontVertexData.insert(frontVertexData.end(), 
					{
						AtoBPoint,
						AtoCPoint
					});
				}
				else
				{
					// B is solo on Front
					std::pair<bool, unsigned> isCBack = isIn(backOldIndices, C);
					Vector3 BtoA = aPosition;
					BtoA 		-= bPosition;
					Vector3 BtoC = cPosition;
					BtoC 		-= bPosition;

					Vector3 BtoAPoint = splitter.pointIntersection(bPosition, BtoA);
					Vector3 BtoCPoint = splitter.pointIntersection(bPosition, BtoC);

					// FRONT
					frontIndices.insert(frontIndices.end(), 
					{
						frontVertexData.size(),
						isBFront.second,
						frontVertexData.size() + 1
					});
					frontVertexData.insert(frontVertexData.end(), 
					{
						BtoAPoint,
						BtoCPoint
					});

					// BACK
					backIndices.insert(backIndices.end(), 
					{
						// Triangle 1
						isABack.second,
						backVertexData.size(),
						isCBack.second,

						// Triangle 2
						backVertexData.size(),
						backVertexData.size() + 1,
						isCBack.second
					});
					backVertexData.insert(backVertexData.end(), 
					{
						BtoAPoint,
						BtoCPoint
					});
				}
			}
			else
			{
				// C is solo on Front
				std::pair<bool, unsigned> isABack = isIn(backOldIndices, A);
				std::pair<bool, unsigned> isBBack = isIn(backOldIndices, B);

				Vector3 CtoA = aPosition;
				CtoA 		-= cPosition;
				Vector3 CtoB = bPosition;
				CtoB 		-= cPosition;

				Vector3 CtoAPoint = splitter.pointIntersection(cPosition, CtoA);
				Vector3 CtoBPoint = splitter.pointIntersection(cPosition, CtoB);

				// FRONT 
				frontIndices.insert(frontIndices.end(), 
				{
					frontVertexData.size(),
					frontVertexData.size() + 1,
					isCFront.second
				});
				frontVertexData.insert(frontVertexData.end(), 
				{
					CtoAPoint,
					CtoBPoint
				});

				// BACK
				backIndices.insert(backIndices.end(), 
				{
					// Triangle 1
					isABack.second,
					isBBack.second,
					backVertexData.size(),

					// Triangle 2
					backVertexData.size(),
					isBBack.second,
					backVertexData.size() + 1
				});
				backVertexData.insert(backVertexData.end(), 
				{
					CtoAPoint,
					CtoBPoint
				});
			}
		}
	}
	Mesh* front = new Mesh(frontVertexData, frontIndices);
	Mesh* back  = new Mesh(backVertexData , backIndices );
	return std::make_pair(front, back);
}

// returns if it is in the vector 
//	and the position since the position will be the new index
//	since the vertices were put in order
std::pair<bool, unsigned>
isIn(const std::vector<unsigned>& v, unsigned A)
{
	unsigned left = 0;
	unsigned right = v.size() - 1;
	unsigned middle = 0;
	while (left < right)
	{
		middle = (left + right) / 2;
		if (v[middle] == A)
		{
			return std::make_pair(true, middle);
		}
		else if (v[middle] > A)
		{
			left = middle + 1;
		}
		else
		{
			right = middle - 1;
		}
	}
	return std::make_pair(false, 0);
}
