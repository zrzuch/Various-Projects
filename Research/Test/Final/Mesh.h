/*
  FileName    : Mesh.h
  Author      : Zachary Zuch
  Course      : CSCI 375
  Assignment  : Lab 3
  Description : This file is the mesh header which is used to 
  				abstract the draw calls and vbo and vao creation 
  				and management.
*/
#pragma once

#include <vector>
#include <string>

#include <GL/glew.h>
#include "Texture.h"
#include "Vector3.h"
#include "ShaderProgram.h"
#include "Frustum.h"

class Mesh
{
public:

	std::string textureFilePath;

	Mesh(const std::vector<float>& vertexData,  
		 const std::vector<unsigned>& indices, 
		 const std::string&	texturePath 			= "",
		 const std::vector<float>& boneWeights 		= std::vector<float>(), 
		 const std::vector<unsigned>& boneIndices 	= std::vector<unsigned>());

	~Mesh ();

	// Disable default copy ctor and copy assignment
  	Mesh (const Mesh&) = delete;
  	Mesh& operator= (const Mesh&) = delete;

	void
	addGeometry (const std::vector<float>& vertices, 
		const std::vector<unsigned>& indices);

	void
	addBoneData(const std::vector<float   >& boneWeights, 
				const std::vector<unsigned>& boneIndices);

	void
	prepareVao ();

	void
	draw();

	bool
	hasTexture() const;

	bool
	isBoneless() const;

	bool
	isEmpty() const;

	unsigned
	numIndices() const;

	unsigned
	numVertices() const;

	Vector3
	getMeshCenter() const;

	Vector3
	getMassSum();

	void
	getRadius(SphereBV& sphere);

	Matrix3
	getCovarianceMatrix(const Vector3& mean, Matrix3& covarianceMatrix);

	void
	getBoxBV(std::vector<float>& lrbtnf);

	void
	getBoxBV(std::vector<float>& lrbtnf, const Matrix3& rotation);

	std::pair<Mesh*, Mesh*>
	split(Plane& splitter);

private:

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;
	GLuint m_vboBoneWeight;
	GLuint m_vboBoneIndex;

	std::vector<float> m_vertexData;
	std::vector<unsigned> m_indices;
	std::vector<float> m_boneWeights;
	std::vector<unsigned> m_boneIndices;

	bool isPrepared;
	
	static constexpr unsigned FLOATS_PER_VERTEX = 8;
	static constexpr unsigned NUM_BONE_INDICES = 3;
};

std::pair<bool, unsigned>
isIn(std::vector<unsigned>& v, unsigned A);
