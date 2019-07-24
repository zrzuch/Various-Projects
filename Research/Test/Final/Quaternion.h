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

	// Quaternion(const Matrix3& A)
	// : x(0), y(0), z(0), w(1)
	// {
	// 	// A must be a symmetric matrix.
	// 	// returns quaternion q such that its corresponding matrix Q 
	// 	// can be used to Diagonalize A
	// 	// Diagonal matrix D = Q * A * Transpose(Q);  and  A = QT*D*Q
	// 	// The rows of q are the eigenvectors D's diagonal is the eigenvalues
	// 	// As per 'row' convention if float3x3 Q = q.getmatrix(); then v*Q = q*v*conj(q)
	// 	constexpr unsigned MAX_STEPS = 24;  // certainly wont need that many.
	// 	for(unsigned i = 0; i < MAX_STEPS; i++)
	// 	{
	// 		Matrix3 Q  = q.toMatrix3(); // v*Q == q*v*conj(q)
	// 		Matrix3 QT = Q;
	// 		QT.transpose();
	// 		Matrix3 D  = Q * A * QT;  // A = Q^T*D*Q
	// 		Vector3 offdiag( D[1][2], D[0][2], D[0][1] ); // elements not on the diagonal
	// 		Vector3 om(fabsf(offdiag.x),fabsf(offdiag.y),fabsf(offdiag.z)); // mag of each offdiag elem
	// 		int k = (om.x > om.y && om.x > om.z) ? 0 : ( om.y > om.z ) ? 1 : 2; // index of largest element of offdiag
	// 		int k1 = ( k + 1 ) % 3;
	// 		int k2 = ( k + 2 ) % 3;
	// 		if(offdiag[k]==0.0f)
	// 		{
	// 			break;  // diagonal already
	// 		}

	// 		float thet = ( D[k2][k2] - D[k1][k1] ) / ( 2.0f * offdiag[k] );
	// 		float sgn = ( thet > 0.0f ) ? 1.0f : -1.0f;
	// 		thet    *= sgn; // make it positive
	// 		float t = sgn /(thet +((thet < 1.E6f)?sqrtf(sqr(thet)+1.0f):thet)) ; // sign(T)/(|T|+sqrt(T^2+1))
	// 		float c = 1.0f/sqrtf(sqr(t)+1.0f); //  c= 1/(t^2+1) , t=s/c 
	// 		if(c==1.0f) break;  // no room for improvement - reached machine precision.
	// 		Quaternion jr(0,0,0,0); // jacobi rotation for this iteration.
	// 		jr[k] = sgn*sqrtf((1.0f-c)/2.0f);  // using 1/2 angle identity sin(a/2) = sqrt((1-cos(a))/2)  
	// 		jr[k] *= -1.0f; // since our quat-to-matrix convention was for v*M instead of M*v
	// 		jr.w  = sqrtf(1.0f - sqr(jr[k]));
	// 		if(jr.w==1.0f) break; // reached limits of floating point precision
	// 		q =  q*jr;  
	// 		q.Normalize();
	// 	}
	// }

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

