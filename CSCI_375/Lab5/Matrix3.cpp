#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <limits>
#include <algorithm>
#include <iomanip>

#include "Matrix3.h"
#include "Vector3.h"

// Basis vectors are stored in Vector3-s and form
//   the columns of a 3x3 matrix. 
// The matrix is interpreted thus:
// [ rx ux bx ]
// [ ry uy by ]
// [ rz uz bz ]
// Operations are consistent with column vectors (v' = M * v).

// Initialize to identity. 
Matrix3::Matrix3 ()
	: m_right( 1, 0, 0 ), m_up( 0, 1, 0 ), m_back( 0, 0, 1 )
{ }

// Initial right vector to (rz, ry, rz),
//   up to (ux, uy, uz), and
//   back to (bx, by, bz).
Matrix3::Matrix3 (float rx, float ry, float rz,
       float ux, float uy, float uz,
       float bx, float by, float bz)
	: m_right( rx, ry, rz ), m_up( ux, uy, uz ), m_back( bx, by, bz )
{ }

// Initialize corresponding basis vector.
Matrix3::Matrix3 (const Vector3& right, const Vector3& up,
       const Vector3& back)
	: m_right( right ), m_up( up ), m_back( back )
{ }

// Initialize right, up, and back. Compute back via a cross product.
// If "makeOrthonormal" is true, call "orthonormalize".
Matrix3::Matrix3 (const Vector3& right, const Vector3& up,
       bool makeOrthonormal)
	: m_right( right ), m_up( up ), m_back( right.cross( up ))
{
	if ( makeOrthonormal ) orthonormalize();
}

// Set to identity matrix.
void
Matrix3::setToIdentity ()
{
	m_right = 	{ 1, 0, 0 }; 
	m_up = 		{ 0, 1, 0 };
	m_back = 	{ 0, 0, 1 };
}

// Set all elements to 0.
void
Matrix3::setToZero ()
{
	m_right.set(0);
	m_up.set(0);
	m_back.set(0);
}

// Return a pointer to the first element.
float*
Matrix3::data ()
{
	return &m_right.x;
}

// Return a const pointer to the first element.
const float*
Matrix3::data () const
{
	return &m_right.x;
}

// Set the right vector. Do not modify others. 
void
Matrix3::setRight (const Vector3& right)
{
	m_right = right;
}

// Get the right vector.
Vector3
Matrix3::getRight () const
{
	return m_right;
}

// Set the up vector only. Do not modify others. 
void
Matrix3::setUp (const Vector3& up)
{
	m_up = up;
}

// Get the up vector. 
Vector3
Matrix3::getUp () const
{
	return m_up;
}

// Set the back vector. Do not modify others. 
void
Matrix3::setBack (const Vector3& back)
{
	m_back = back;
}

// Get the back vector.
Vector3
Matrix3::getBack () const
{
	return m_back;
}

// Set the back vector to the negation of "forward".
void
Matrix3::setForward (const Vector3& forward)
{
	m_back = -forward;
}

// Get the forward vector.
Vector3
Matrix3::getForward () const
{
	return -m_back;
}

// Invert this matrix, assuming it's a rotation matrix.
void
Matrix3::invertRotation ()
{
	transpose();
}

// Invert this matrix.
void
Matrix3::invert ()
{
	float det = determinant();
	// Check Later
	if ( std::abs( det ) > std::numeric_limits<float>::epsilon())
	{
		float detReciprocal = 1 / det;
		Vector3 newRight(
			( m_up.y * m_back.z - m_back.y * m_up.z ) * detReciprocal,
			( m_back.y * m_right.z - m_right.y * m_back.z ) * detReciprocal,
			( m_right.y * m_up.z - m_up.y * m_right.z ) * detReciprocal
		);
		Vector3 newUp(
			( m_back.x * m_up.z - m_up.x * m_back.z ) * detReciprocal,
			( m_right.x * m_back.z - m_back.x * m_right.z ) * detReciprocal,
			( m_up.x * m_right.z - m_right.x * m_up.z ) * detReciprocal
		);
		Vector3 newBack(
			( m_up.x * m_back.y - m_back.x * m_up.y ) * detReciprocal,
			( m_back.x * m_right.y - m_right.x * m_back.y ) * detReciprocal,
			( m_right.x * m_up.y - m_up.x * m_right.y ) * detReciprocal
		);
		m_right = newRight;
		m_up = newUp;
		m_back = newBack;
	}
}

// Return the determinant. 
float
Matrix3::determinant () const
{
	float i_determinant = m_right.x * ( m_up.y * m_back.z - m_back.y * m_up.z );
	float j_determinant = m_up.x * ( m_right.y * m_back.z - m_back.y * m_right.z );
	float k_determinant = m_back.x * ( m_right.y * m_up.z - m_up.y * m_right.z );
	return i_determinant - j_determinant + k_determinant;
}

// Transpose this. 
void
Matrix3::transpose ()
{
	std::swap( m_right.y, m_up.x );
	std::swap( m_right.z, m_back.x );
	std::swap( m_up.z, m_back.y );
}

// Ensure all axes are of unit length and mutually perpendicular.
//   Bias toward the back vector by assuming it is pointing
//   in the correct direction. Normalize it, compute right via cross, 
//   normalize it, and finally compute up. 
void
Matrix3::orthonormalize ()
{
	m_back.normalize();
	m_right = m_up.cross( m_back );
	m_right.normalize();
	m_up = m_back.cross( m_right );
}

// For each "set" method, ensure you set ALL matrix entries!
// Set to a uniform scale matrix. 
void
Matrix3::setToScale (float scale)
{
	m_right.x = scale;
	m_right.y = 0;
	m_right.z = 0;

	m_up.x = 0;
	m_up.y = scale;
	m_up.z = 0;

	m_back.x = 0;
	m_back.y = 0;
	m_back.z = scale;
}

// Set to a non-uniform scale matrix.
void
Matrix3::setToScale (float scaleX, float scaleY, float scaleZ)
{
	m_right.x = scaleX;
	m_right.y = 0;
	m_right.z = 0;

	m_up.x = 0;
	m_up.y = scaleY;
	m_up.z = 0;

	m_back.x = 0;
	m_back.y = 0;
	m_back.z = scaleZ;
}

// Set to a shear matrix that shears x by y and z.
void
Matrix3::setToShearXByYz (float shearY, float shearZ)
{
	m_right.x = 1;
	m_right.y = 0;
	m_right.z = 0;

	m_up.x = shearY;
	m_up.y = 1;
	m_up.z = 0;

	m_back.x = shearZ;
	m_back.y = 0;
	m_back.z = 1;
}

// Set to a shear matrix that shears y by x and z.
void
Matrix3::setToShearYByXz (float shearX, float shearZ)
{
	m_right.x = 1;
	m_right.y = shearX;
	m_right.z = 0;

	m_up.x = 0;
	m_up.y = 1;
	m_up.z = 0;

	m_back.x = 0;
	m_back.y = shearZ;
	m_back.z = 1;
}

// Set to a shear matrix that shears z by x and y.
void
Matrix3::setToShearZByXy (float shearX, float shearY)
{
	m_right.x = 1;
	m_right.y = 0;
	m_right.z = shearX;

	m_up.x = 0;
	m_up.y = 1;
	m_up.z = shearY;

	m_back.x = 0;
	m_back.y = 0;
	m_back.z = 1;
}

// Set to an x-axis rotation matrix.
void
Matrix3::setToRotationX (float angleDegrees)
{
	float cos_theta = glm::cos( glm::radians( angleDegrees ));
	float sin_theta = glm::sin( glm::radians( angleDegrees ));

	m_right.x = 1;
	m_right.y = 0;
	m_right.z = 0;

	m_up.x = 0;
	m_up.y = cos_theta;
	m_up.z = sin_theta;

	m_back.x = 0;
	m_back.y = -sin_theta;
	m_back.z = cos_theta;
}

// Set to a y-axis rotation matrix.
void
Matrix3::setToRotationY (float angleDegrees)
{
	float cos_theta = glm::cos( glm::radians( angleDegrees ));
	float sin_theta = glm::sin( glm::radians( angleDegrees ));

	m_right.x = cos_theta;
	m_right.y = 0;
	m_right.z = -sin_theta;

	m_up.x = 0;
	m_up.y = 1;
	m_up.z = 0;

	m_back.x = sin_theta;
	m_back.y = 0;
	m_back.z = cos_theta;
}

// Set to a z-axis rotation matrix.
void
Matrix3::setToRotationZ (float angleDegrees)
{
	float cos_theta = glm::cos( glm::radians( angleDegrees ));
	float sin_theta = glm::sin( glm::radians( angleDegrees ));

	m_right.x = cos_theta;
	m_right.y = sin_theta;
	m_right.z = 0;

	m_up.x = -sin_theta;
	m_up.y = cos_theta;
	m_up.z = 0;

	m_back.x = 0;
	m_back.y = 0;
	m_back.z = 1;
}

// Set to a general rotation matrix that rotates about "axis". 
// http://ksuweb.kennesaw.edu/~plaval//math4490/rotgen.pdf
void
Matrix3::setFromAngleAxis (float angleDegrees, const Vector3& axis)
{
	float cos_theta = glm::cos( glm::radians( angleDegrees ));
	float sin_theta = glm::cos( glm::radians( angleDegrees ));
	float t = 1 - cos_theta;

	m_right.x = t * axis.x * axis.x + cos_theta;
	m_right.y = t * axis.x * axis.y + sin_theta * axis.z;
	m_right.z = t * axis.x * axis.z - sin_theta * axis.y;

	m_up.x = t * axis.x * axis.y - sin_theta * axis.z;
	m_up.y = t * axis.y * axis.y + cos_theta;
	m_up.z = t * axis.y * axis.z + sin_theta * axis.x;

	m_back.x = t * axis.x * axis.z + sin_theta * axis.y;
	m_back.y = t * axis.y * axis.z - sin_theta * axis.x;
	m_back.z = t * axis.z * axis.z + cos_theta;
}

// Negate this.
void
Matrix3::negate ()
{
	m_right.negate();
	m_up.negate();
	m_back.negate();
}

// Return *this * v.
Vector3
Matrix3::transform (const Vector3& v) const
{
	return *this * v;
}

Matrix3&
Matrix3::operator+= (const Matrix3& m)
{
	m_right += m.m_right;
	m_up += m.m_up;
	m_back += m.m_back;
	return *this;
}

Matrix3&
Matrix3::operator-= (const Matrix3& m)
{
	m_right -= m.m_right;
	m_up -= m.m_up;
	m_back -= m.m_back;
	return *this;
}

// Scalar matrix multiply.
Matrix3&
Matrix3::operator*= (float scalar)
{
	m_right *= scalar;
	m_up *= scalar;
	m_back *= scalar;
	return *this;
}

// Matrix multiply.
Matrix3&
Matrix3::operator*= (const Matrix3& m)
{
	Vector3 newRight = transform( m.m_right );
	Vector3 newUp = transform( m.m_up );
	Vector3 newBack = transform( m.m_back );

	m_right = newRight;
	m_up = newUp;
	m_back = newBack;

	return *this;
}	

Matrix3
operator+ (const Matrix3& m1, const Matrix3& m2)
{
	Matrix3 matrix( m1 );
	return matrix += m2; 
}

Matrix3
operator- (const Matrix3& m1, const Matrix3& m2)
{
	Matrix3 matrix( m1 );
	return matrix -= m2; 
}

// Unary negation.
Matrix3
operator- (const Matrix3& m)
{
	Matrix3 matrix( m );
	matrix.negate();
	return matrix;
}

Matrix3
operator* (const Matrix3& m, float scalar)
{
	Matrix3 matrix( m );
	return matrix *= scalar; 
}

Matrix3
operator* (float scalar, const Matrix3& m)
{
	Matrix3 matrix( m );
	return matrix *= scalar; 
}

Matrix3
operator* (const Matrix3& m1, const Matrix3& m2)
{
	Matrix3 matrix( m1 );
	return matrix *= m2;
}

Vector3
operator* (const Matrix3& m, const Vector3& v)
{
	return Vector3(
		v.x * m.getRight().x + v.y * m.getUp().x + v.z * m.getBack().x,
		v.x * m.getRight().y + v.y * m.getUp().y + v.z * m.getBack().y,
		v.x * m.getRight().z + v.y * m.getUp().z + v.z * m.getBack().z
	);
}

// Print "m" in a neat, tabular format using TWO digits
//   of precision and a field width of 10 for each entry. 
std::ostream&
operator<< (std::ostream& out, const Matrix3& m)
{
	std::ios state( NULL );
	state.copyfmt( out );
	out << std::endl << std::setprecision(2) << std::setw(10)
		<< m.getRight().x << std::setw(10) << m.getUp().x << std::setw(10) 
		<< m.getBack().x << "\n" << std::setw(10)
		<< m.getRight().y << std::setw(10) << m.getUp().y << std::setw(10) 
		<< m.getBack().y << "\n" << std::setw(10)
		<< m.getRight().z << std::setw(10) << m.getUp().z << std::setw(10) 
		<< m.getBack().z << std::endl;
	out.copyfmt( state );
	return out;
}