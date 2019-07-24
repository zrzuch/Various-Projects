#include "Debug.h"
#include "AiScene.h"

SphereDebug::SphereDebug()
: boxMesh(nullptr)
, type(BVType::SPHERE)
, local()
, material()
{
	AiScene scene("Sphere.obj");
	sphereMesh = new Mesh(scene.getAllVertexData(), scene.getAllFaceIndices());
	sphereMesh->prepareVao();
}

SphereDebug::~SphereDebug()
{
	delete sphereMesh;
}

void
SphereDebug::init(const SphereBV& sphereBV)
{
	type = BVType::SPHERE;
	Transform sphereBVLocal(sphereBV.center);
	sphereBVLocal.scaleLocal(sphereBV.radius);
	local = sphereBVLocal;
}

void
SphereDebug::init(const BoxBV& boxBV)
{
	type = BVType::BOX;
	if (boxMesh != nullptr)
	{
		delete boxMesh;
	}

	std::vector<unsigned> indices = 
	{
		0, 4, 6,
		0, 6, 2,
		1, 7, 5,
		1, 3, 7,
		1, 0, 2,
		1, 2, 3,
		5, 6, 4,
		5, 7, 6,
		2, 6, 7,
		2, 7, 3,
		0, 5, 4,
		0, 1, 5
	};

	// Edges 
	Vector3 a04 = boxBV.points[0] - boxBV.points[4];
	Vector3 a46 = boxBV.points[4] - boxBV.points[6];
	Vector3 a26 = boxBV.points[2] - boxBV.points[6];
	Vector3 a20 = boxBV.points[2] - boxBV.points[0];

	Vector3 a13 = boxBV.points[1] - boxBV.points[3];
	Vector3 a15 = boxBV.points[1] - boxBV.points[5];
	Vector3 a73 = boxBV.points[7] - boxBV.points[3];
	Vector3 a75 = boxBV.points[7] - boxBV.points[5];

	Vector3 a10 = boxBV.points[1] - boxBV.points[0];
	Vector3 a32 = boxBV.points[3] - boxBV.points[2];
	Vector3 a54 = boxBV.points[5] - boxBV.points[4];
	Vector3 a76 = boxBV.points[7] - boxBV.points[6];

	Vector3 fn046 = a04;
	fn046.cross(a46);

	Vector3 fn062 = a26;
	fn062.cross(a20);

	Vector3 fn102 = a10;
	fn102.cross(a20);

	Vector3 fn123 = a32;
	fn102.cross(a13);

	Vector3 fn267 = a26;
	fn102.cross(a76);

	Vector3 fn273 = a73;
	fn102.cross(a32);

	Vector3 fn175 = a75;
	fn175.cross(a15);

	Vector3 fn137 = a13;
	fn175.cross(a73);

	Vector3 fn564 = a46;
	fn564.cross(a54);

	Vector3 fn576 = a75;
	fn576.cross(a76);

	Vector3 fn054 = a54;
	fn576.cross(a04);

	Vector3 fn015 = a10;
	fn576.cross(a15);

	Vector3 vn0 = fn046 + fn102 + fn054;
	vn0.normalize();

	Vector3 vn1 = fn175 + fn102 + fn054;
	vn1.normalize();

	Vector3 vn2 = fn046 + fn102 + fn267;
	vn2.normalize();

	Vector3 vn3 = fn175 + fn102 + fn267;
	vn3.normalize();

	Vector3 vn4 = fn046 + fn564 + fn054;
	vn4.normalize();

	Vector3 vn5 = fn175 + fn564 + fn054;
	vn5.normalize();

	Vector3 vn6 = fn046 + fn564 + fn267;
	vn6.normalize();

	Vector3 vn7 = fn175 + fn564 + fn267;
	vn7.normalize();

	std::vector<float> vertexData = 
	{ 
		boxBV.points[0].x, boxBV.points[0].y, boxBV.points[0].z, vn0.x, vn0.y, vn0.z, 0, 0,
		boxBV.points[1].x, boxBV.points[1].y, boxBV.points[1].z, vn1.x, vn1.y, vn1.z, 0, 0, 
		boxBV.points[2].x, boxBV.points[2].y, boxBV.points[2].z, vn2.x, vn2.y, vn2.z, 0, 0, 
		boxBV.points[3].x, boxBV.points[3].y, boxBV.points[3].z, vn3.x, vn3.y, vn3.z, 0, 0, 
		boxBV.points[4].x, boxBV.points[4].y, boxBV.points[4].z, vn4.x, vn4.y, vn4.z, 0, 0, 
		boxBV.points[5].x, boxBV.points[5].y, boxBV.points[5].z, vn5.x, vn5.y, vn5.z, 0, 0, 
		boxBV.points[6].x, boxBV.points[6].y, boxBV.points[6].z, vn6.x, vn6.y, vn6.z, 0, 0, 
		boxBV.points[7].x, boxBV.points[7].y, boxBV.points[7].z, vn7.x, vn7.y, vn7.z, 0, 0, 
	};

	boxMesh = new Mesh(vertexData, indices);
	boxMesh->prepareVao();
}

void
SphereDebug::draw(ShaderProgram* shaderProgram, Transform modelView)
{
	shaderProgram->setUniform ("hasBones", false);
	material.setUniforms(shaderProgram);
	if (type == BVType::SPHERE)
	{
		modelView.combine(local);
	}
	shaderProgram->setUniform ("uModelView", modelView.getTransform());
	Matrix3 normalMatrix = modelView.getOrientation();
	normalMatrix.invert();
	normalMatrix.transpose();
	shaderProgram->setUniform ("uNormalMatrix", normalMatrix);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (type == BVType::BOX)
	{
		boxMesh->draw();
	}
	else
	{
		sphereMesh->draw();
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}