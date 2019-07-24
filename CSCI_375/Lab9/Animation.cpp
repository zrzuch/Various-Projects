#include "Animation.h"

const Transform Bone::m_parent = Transform();

Vector3Key::Vector3Key(Vector3 value, float timeStamp)
	: value		(value)
	, timeStamp	(timeStamp)
{ }

QuaternionKey::QuaternionKey(Quaternion value, float timeStamp)
	: value		(value)
	, timeStamp	(timeStamp)
{ }

void
Animation::printAnimation()
{
	std::cout << "Animation Name 	= " << name << std::endl;
	std::cout << "Num of Positions 	= " << positions.size() << std::endl;
	std::cout << "Num of Scalings 	= " << scalings.size() << std::endl;
	std::cout << "Num of Rotations 	= " << rotations.size() << std::endl;
}

Transform
Animation::getAnimationMatrix(float time)
{
	//std::cout << time << std::endl;
	Transform animation(getPosition(time), getRotationMatrix(time));
	animation.innerScale(getScaleMatrix(time));
	return animation;
}

Vector3
Animation::getPosition(const float time)
{
	for (unsigned index = 1; index < positions.size(); ++index)
	{
		if (positions[index].timeStamp > time)
		{
			// std::cout << "Position Index = " << index << std::endl;
			float totalTime = positions[index].timeStamp - positions[index - 1].timeStamp;
			float currTime = time - positions[index - 1].timeStamp;
			float blend = currTime / totalTime;
			Vector3 next = positions[index    ].value;
			Vector3 prev = positions[index - 1].value;
			return prev.interpolate(next, blend);
		}
	}
	return Vector3();
}

Vector3
Animation::getScaleMatrix(const float time)
{
	for (unsigned index = 1; index < scalings.size(); ++index)
	{
		if (scalings[index].timeStamp > time)
		{
			// std::cout << "Scale Index = " << index << std::endl;
			float totalTime = scalings[index].timeStamp - scalings[index - 1].timeStamp;
			float currTime = time - scalings[index - 1].timeStamp;
			float blend = currTime / totalTime;
			Vector3 next = scalings[index    ].value;
			Vector3 prev = scalings[index - 1].value;
			return prev.interpolate(next, blend);
		}
	}
	return Vector3();
}

Matrix3
Animation::getRotationMatrix(const float time)
{
	for (unsigned index = 1; index < rotations.size(); ++index)
	{
		if (rotations[index].timeStamp > time)
		{
			// std::cout << "Rotation Index = " << index << std::endl;
			float totalTime = rotations[index].timeStamp - rotations[index - 1].timeStamp;
			float currTime = time - rotations[index - 1].timeStamp;
			float blend = currTime / totalTime;
			Quaternion next = rotations[index    ].value;
			Quaternion prev = rotations[index - 1].value;
			return prev.interpolate(next, blend).toMatrix3();
		}
	}
	return Matrix3();
}

Bone::Bone(std::string name, const Transform& bind, const Transform& global, const Transform& local)
	: name(name)
	, bind(bind)
	, global(global)
	, local(local)
	, children()
	, isAnimated(true)
	, index(0)
	, time(0.0f)
{
	// inverseBind.invert();
}

Bone::~Bone()
{
	for (Bone* child : children)
	{
		delete child;
	}
}

void
Bone::addChild(Bone* child)
{
	children.push_back(child);
}

void
Bone::setUniforms(ShaderProgram* shaderProgram)
{
	std::vector<Transform> transforms;
	this->getTransforms(transforms, Transform());
	for (unsigned i = 0; i < transforms.size(); ++i)
	{
		shaderProgram->setUniform("uBones[" + std::to_string(i) + "]", transforms[i].getTransform());
	}
}

void
Bone::getTransforms(std::vector<Transform>& transforms, const Transform& parent)
{
	// Calculate the nodes Transform relative to the parent's transform
	Transform node = parent;
	if (isAnimated)
	{
		node.combine(animation);
	}
	else
	{
		node.combine(local);
	}
	
	Transform mat = global;
	mat.combine(node);
	mat.combine(bind);

	// Add it to vector
	transforms.push_back(mat);
	// Then recurse over all children to get their relative transforms
	for (Bone* child : children)
	{
		child->getTransforms(transforms, node);
	}
}

void
Bone::update(float deltaTime)
{
	if (isAnimated)
	{
		setAnimation(deltaTime);
		for (Bone* child : children)
		{
			child->update(deltaTime);
		}
	}
}

void
Bone::setAnimation(float deltaTime)
{
    time = fmod(time + deltaTime, animations[index].duration);
	animation = animations[index].getAnimationMatrix(time);
}

unsigned
Bone::numChildren()
{
	return children.size();
}

Bone*
Bone::find(std::string name)
{
	if (this->name == name)
	{
		return this;
	}

	Bone* childPtr;
	for (Bone* child : children)
	{
		childPtr = child->find(name);
		if (childPtr != nullptr)
		{
			return childPtr;
		}
	}

	return nullptr;
}