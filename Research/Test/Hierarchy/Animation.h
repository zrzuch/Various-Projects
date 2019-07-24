#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "ShaderProgram.h"
#include "Transform.h"
#include "Matrix4.h"
#include "Quaternion.h"

struct Vector3Key
{
	Vector3Key(Vector3 value = Vector3(), float timeStamp = 0);

	Vector3 value;
	float timeStamp;
};

struct QuaternionKey
{
	QuaternionKey(Quaternion value = Quaternion(), float timeStamp = 0);

	Quaternion value;
	float timeStamp;
};

struct Animation
{
	std::string name;
	std::vector<Vector3Key> positions;
	std::vector<Vector3Key> scalings;
	std::vector<QuaternionKey> rotations;
	float duration;
	float ticksPerSecond;

	void
	printAnimation();

	Transform
	getAnimationMatrix(float time);

	Vector3
	getPosition(float time);

	Vector3
	getScaleMatrix(float time);

	Matrix3
	getRotationMatrix(float time);
};

class Bone
{
	static const Transform m_parent;

public:

	Bone(std::string name = "", const Transform& bind = Transform(), const Transform& global = Transform(), 
		const Transform& local = Transform());

	~Bone();
	
	void
	addChild(Bone* child);

	void
	update(float deltaTime);

	void
	setAnimation(float deltaTime);

	void
	reset();

	void
	setUniforms(ShaderProgram* shaderProgram);

	void
	getTransforms(std::vector<Transform>& transforms, const Transform& parent);

	unsigned
	numChildren();

	Bone*
	find(std::string name);

public:
	const std::string name;

private:
	Transform animation;

public:
	 Transform bind;
	const Transform global;
	const Transform local;
	
public:
	std::vector<Bone*> children;
	std::vector<Animation> animations;
	bool isAnimated;
	int index;
	float time;
};
