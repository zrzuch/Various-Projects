#pragma once

#include "Frustum.h"
#include "Mesh.h"
#include "Camera.h"
#include "Debug.h"
#include <gsl/gsl_eigen.h>

struct BSPNode
{
	Plane 		splitter;
	Mesh* 		polygons;
	// parent added for iterative traversal
	// will be added later
	// BSPNode* 	parent;
	BSPNode* 	front;
	BSPNode* 	back;
	BoxBV 		box;

	// init node constructor
	BSPNode(Mesh* polygonList = nullptr, /*BSPNode* nodeParent = nullptr,*/ BSPNode* nodeFront = nullptr, BSPNode* nodeBack = nullptr);

	~BSPNode();

	void
	calculateSplitter();

	void
	initBox();
};

class BSPTree
{
public:
	
	BSPTree(Mesh* polygonList);

	~BSPTree();

	void
	draw(ShaderProgram* shaderProgram, const Camera& camera, Transform& modelView, SphereDebug& sphereD);

	void
	prepare();

	void
	initBoxes();

private:

	void
	buildTree(BSPNode* node);

	bool
	isFront(const Vector3& position, BSPNode* node);

	void
	draw(ShaderProgram* shaderProgram, const Camera& camera, Transform& modelView, SphereDebug& sphereD, BSPNode* node);

	void
	prepare(BSPNode* node);

	void
	initBoxes(BSPNode* node);

	BSPNode* root;
};