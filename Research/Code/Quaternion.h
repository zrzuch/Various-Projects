#pragma once

#include "Matrix4.h"
#include "Matrix3.h"
#include <cmath>

// Source: https://github.com/TheThinMatrix/OpenGL-Animation
// However, the methods have been changed to be used with c++ and all the methods being used
// 	were created by myself with inspiration
class Quaternion 
{
public:

	float x;
	float y;
	float z;
	float w;

	/**
	 * Creates a quaternion and normalizes it.
	 * 
	 * @param x
	 * @param y
	 * @param z
	 * @param w
	 */
	Quaternion(float x = 0, float y = 0, float z = 0, float w = 0)
		: x(x)
		, y(y)
		, z(z)
		, w(w)
	{
		normalize();
	}

	Quaternion(Matrix4 matrix)
	{
		init(matrix);
	}

	/**
	 * Normalizes the quaternion.
	 */
	void
	normalize()
	{
		(*this) /= length();
	}

	float
	length()
	{
		return sqrt(w * w + x * x + y * y + z * z);
	}

	Quaternion&
	operator/= (float divisor)
	{
		w /= divisor;
		x /= divisor;
		y /= divisor;
		z /= divisor;
		return *this;
	}

	/**
	 * Converts the quaternion to a 4x4 matrix representing the exact same
	 * rotation as this quaternion. (The rotation is only contained in the
	 * top-left 3x3 part, but a 4x4 matrix is returned here for convenience
	 * seeing as it will be multiplied with other 4x4 matrices).
	 * 
	 * More detailed explanation here:
	 * http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/
	 * 
	 * @return The rotation matrix which represents the exact same rotation as
	 *         this quaternion.
	 */
	Matrix4 
	toRotationMatrix()
	{
		float xy = x * y;
		float xz = x * z;
		float xw = x * w;
		float yz = y * z;
		float yw = y * w;
		float zw = z * w;
		float xSquared = x * x;
		float ySquared = y * y;
		float zSquared = z * z;

		return Matrix4
		(
			1 - 2 * (ySquared + zSquared), 	2 * (xy + zw), 					2 * (xz - yw), 					0, 
			2 * (xy - zw), 					1 - 2 * (xSquared + zSquared), 	2 * (yz + xw), 					0,
			2 * (xz + yw), 					2 * (yz - xw), 					1 - 2 * (xSquared + ySquared), 	0,
			0, 								0, 								0, 								1 
		);
	}

	Matrix3
	toMatrix3()
	{
		float xy = x * y;
		float xz = x * z;
		float xw = x * w;
		float yz = y * z;
		float yw = y * w;
		float zw = z * w;
		float xSquared = x * x;
		float ySquared = y * y;
		float zSquared = z * z;

		return Matrix3
		(
			1 - 2 * (ySquared + zSquared), 	2 * (xy + zw), 					2 * (xz - yw),
			2 * (xy - zw), 					1 - 2 * (xSquared + zSquared), 	2 * (yz + xw),
			2 * (xz + yw), 					2 * (yz - xw), 					1 - 2 * (xSquared + ySquared)
		);
	}

	/**
	 * Interpolates between two quaternion rotations and returns the resulting
	 * quaternion rotation. The interpolation method here is "nlerp", or
	 * "normalized-lerp". Another mnethod that could be used is "slerp", and you
	 * can see a comparison of the methods here:
	 * https://keithmaggio.wordpress.com/2011/02/15/math-magician-lerp-slerp-and-nlerp/
	 * 
	 * and here:
	 * http://number-none.com/product/Understanding%20Slerp,%20Then%20Not%20Using%20It/
	 * 
	 * @param a
	 * @param b
	 * @param blend
	 *            - a value between 0 and 1 indicating how far to interpolate
	 *            between the two quaternions.
	 * @return The resulting interpolated rotation in quaternion format.
	 */
	Quaternion
	interpolate(Quaternion b, float blend) 
	{
		Quaternion result(0, 0, 0, 1);
		float dot = w * b.w + x * b.x + y * b.y + z * b.z;
		float blendI = 1.0f - blend;
		if (dot < 0)
		{
			result.w = blendI * w + blend * -b.w;
			result.x = blendI * x + blend * -b.x;
			result.y = blendI * y + blend * -b.y;
			result.z = blendI * z + blend * -b.z;
		} 
		else 
		{
			result.w = blendI * w + blend * b.w;
			result.x = blendI * x + blend * b.x;
			result.y = blendI * y + blend * b.y;
			result.z = blendI * z + blend * b.z;
		}
		result.normalize();
		return result;
	}

private:

	/**
	 * Extracts the rotation part of a transformation matrix and converts it to
	 * a quaternion using the magic of maths.
	 * 
	 * More detailed explanation here:
	 * http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
	 * 
	 * @param matrix
	 *            - the transformation matrix containing the rotation which this
	 *            quaternion shall represent.
	 */
	void 
	init(Matrix4 matrix) 
	{
		float diagonal = matrix.m_right.x + matrix.m_up.y + matrix.m_back.z;
		if (diagonal > 0) 
		{
			float w4 = static_cast<float>(sqrt(diagonal + 1.0f) * 2.0f);
			w = w4 / 4.0f;
			x = (matrix.m_up.z - matrix.m_right.z) / w4;
			y = (matrix.m_back.x - matrix.m_right.z) / w4;
			z = (matrix.m_right.y - matrix.m_up.x) / w4;
		} 
		else if ((matrix.m_right.x > matrix.m_up.y) && (matrix.m_right.x > matrix.m_back.z)) 
		{
			float x4 = static_cast<float>(sqrt(1.0f + matrix.m_right.x - matrix.m_up.y - matrix.m_back.z) * 2.0f);
			w = (matrix.m_up.z - matrix.m_back.y) / x4;
			x = x4 / 4.0f;
			y = (matrix.m_up.x + matrix.m_right.y) / x4;
			z = (matrix.m_back.x + matrix.m_right.z) / x4;
		} 
		else if (matrix.m_up.y > matrix.m_back.z) 
		{
			float y4 = static_cast<float>(sqrt(1.0f + matrix.m_up.y - matrix.m_right.x - matrix.m_back.z) * 2.0f);
			w = (matrix.m_back.x - matrix.m_right.z) / y4;
			x = (matrix.m_up.x + matrix.m_right.y) / y4;
			y = y4 / 4.0f;
			z = (matrix.m_right.z + matrix.m_up.z) / y4;
		} 
		else 
		{
			float z4 = static_cast<float>(sqrt(1.0f + matrix.m_back.z - matrix.m_right.x - matrix.m_up.y) * 2.0f);
			w = (matrix.m_right.y - matrix.m_up.x) / z4;
			x = (matrix.m_back.x + matrix.m_right.z) / z4;
			y = (matrix.m_right.z + matrix.m_up.z) / z4;
			z = z4 / 4.0f;
		}
	}
};