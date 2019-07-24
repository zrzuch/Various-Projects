// Transform class for representing affine transformations like
//   scales, rotations, shears, reflections, and translations. 
// Author: Gary M. Zoppetti, Ph.D.
#include "Math.h"
#include "Transform.h"

#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>

// A Transform represents a 3x4 matrix, stored in
//   column-major order as follows:
//   [ rx ux bx px ]
//   [ ry uy by py ]
//   [ rz uz bz pz ]
//   [  0  0  0  1 ] 
// 'r', 'u', 'b', and 'p' are the right, up, back,
//   and position vectors, respectively. 
// The last row is not explicitly stored since it is always
//    [  0  0  0  1 ].

// Initialize to identity transform, that represents no
//   scale, rotation, shear, or translation. 
Transform::Transform (float px, float py, float pz)
: m_rotScale(1,0,0,0,1,0,0,0,1), m_position(px, py, pz)
{ }

Transform::Transform (const Vector3& position, const Matrix3& rotation)
: m_rotScale(rotation), m_position(position)
{ }

Transform::Transform (Vector3 scale, bool isScale)
: m_rotScale
  (
    scale.x,  0,        0,
    0,        scale.y,  0,
    0,        0,        scale.z
  )
, m_position(0)
{ }

// Orthonormalize the Matrix3 component.
void
Transform::orthonormalize ()
{
  m_rotScale.orthonormalize();
}

// Reset to identity transform. 
void
Transform::reset ()
{
  m_rotScale.setToIdentity();
  m_position.set(0);
}

// Return this as a Matrix4 object.
// This function REPLACES the one that returns a 4x4 GLM matrix.
Matrix4
Transform::getTransform () const
{
  return 
  {
    m_rotScale.getRight().x, m_rotScale.getRight().y, m_rotScale.getRight().z,  0,
    m_rotScale.getUp().x,    m_rotScale.getUp().y,    m_rotScale.getUp().z,     0,
    m_rotScale.getBack().x,  m_rotScale.getBack().y,  m_rotScale.getBack().z,   0,
    m_position.x,            m_position.y,            m_position.z,             1
  };
}

// Store this transform in "array". 
// Remember we are using column-major storage, so
//   the order is [ rx ry rz 0 ux uy uz 0 bx by bz 0 px py pz 1 ].
void
Transform::getTransform (float array[16]) const
{
  array[0]  = m_rotScale.getRight().x;
  array[1]  = m_rotScale.getRight().y;
  array[2]  = m_rotScale.getRight().z;
  array[3]  = 0;
  array[4]  = m_rotScale.getUp().x;
  array[5]  = m_rotScale.getUp().y;
  array[6]  = m_rotScale.getUp().z;
  array[7]  = 0;
  array[8]  = m_rotScale.getBack().x;
  array[9]  = m_rotScale.getBack().y;
  array[10] = m_rotScale.getBack().z;
  array[11] = 0;
  array[12] = m_position.x;
  array[13] = m_position.y;
  array[14] = m_position.z;
  array[15] = 1;
}

// Get the position component. 
Vector3
Transform::getPosition () const
{
  return m_position;
}

// Set the position component. 
void
Transform::setPosition (const Vector3& position)
{
  m_position = position;
}

// Set the position component. 
void
Transform::setPosition (float x, float y, float z)
{
  m_position = { x, y, z };
}

// Get the right basis vector. 
Vector3
Transform::getRight () const
{
  return m_rotScale.getRight();
}

// Get the up basis vector. 
Vector3
Transform::getUp () const
{
  return m_rotScale.getUp();
}

// Get the back basis vector. 
Vector3
Transform::getBack () const
{
  return m_rotScale.getBack();
}

// Move "distance" units along the right vector. 
void
Transform::moveRight (float distance)
{
  m_position += m_rotScale.getRight() * distance;
}

// Move "distance" units along the up vector. 
void
Transform::moveUp (float distance)
{
  m_position += m_rotScale.getUp() * distance;
}

// Move "distance" units along the back vector. 
void
Transform::moveBack (float distance)
{
  m_position += m_rotScale.getBack() * distance;
}

// Move "distance" units in "localDirection", which is relative
//   to the coordinate system defined by this transform. 
void
Transform::moveLocal (float distance, const Vector3& localDirection)
{
  m_position += m_rotScale.transform(localDirection) * distance;
}

// Move "distance" units in "worldDirection", which is relative
//   to the world coodinate system. 
void
Transform::moveWorld (float distance, const Vector3& worldDirection)
{
  m_position += worldDirection * distance;
}

// Get the orientation and scale matrix.
Matrix3
Transform::getOrientation () const
{
  return m_rotScale;
}

const Matrix3&
Transform::getOrientation (bool getConst) const
{
  return m_rotScale;
}

// Set the orientation and scale matrix. 
void
Transform::setOrientation (const Matrix3& orientation)
{
  m_rotScale = orientation;
}

// Set the orientation and scale matrix. 
void
Transform::setOrientation (const Vector3& right, const Vector3& up,
 const Vector3& back)
{
  m_rotScale.setRight( right );
  m_rotScale.setUp( up );
  m_rotScale.setBack( back );
}

// Rotate about the local X axis.
void
Transform::pitch (float angleDegrees)
{
  Matrix3 rotateX;
  rotateX.setToRotationX(angleDegrees);
  m_rotScale *= rotateX;
}

// Rotate about the local Y axis.
void
Transform::yaw (float angleDegrees)
{
  Matrix3 rotateY;
  rotateY.setToRotationY(angleDegrees);
  m_rotScale *= rotateY;
}

// Rotate about the local Z axis.
void
Transform::roll (float angleDegrees)
{
  Matrix3 rotateZ;
  rotateZ.setToRotationZ(angleDegrees);
  m_rotScale *= rotateZ;
}

// Rotate about an arbitrary local unit vector "axis".
void
Transform::rotateLocal (float angleDegrees, const Vector3& axis)
{
  Matrix3 rotate;
  rotate.setFromAngleAxis( angleDegrees, axis );
  m_rotScale *= rotate;
}

// Set "up" to world Y, and adjust "back" and "right"
//   to ensure the matrix is orthogonal.
// If "back" is pointing in the Y or -Y direction,
//   make it [ 0 0 1 ]. 
void
Transform::alignWithWorldY ()
{
  m_rotScale.setUp(0,1,0);
  if ( Math::equalsPlusOrMinusUsingTolerance( m_rotScale.getUp(), 
    m_rotScale.getBack()))
  {
    m_rotScale.setBack(0,0,1);
    m_rotScale.setRight(1,0,0);
  }
  else
  {
    Vector3 newRight = m_rotScale.getUp().cross( m_rotScale.getBack());
    newRight.normalize();
    m_rotScale.setRight( newRight );
    m_rotScale.setBack( newRight.cross( m_rotScale.getUp()));
  }
}

// Rotate around the world unit vector "axis".
void
Transform::rotateWorld (float angleDegrees, const Vector3& axis)
{
  Matrix3 scaleMatrix;
  scaleMatrix.setFromAngleAxis( angleDegrees, axis );
  m_rotScale = scaleMatrix * m_rotScale;
  m_position = scaleMatrix * m_position;
}

void
Transform::innerScale(const Vector3& scale)
{
  m_rotScale.scaleMatrix(scale);
}

// Scale locally using a uniform scale.
void
Transform::scaleLocal (float scale)
{
  Matrix3 scaleMatrix;
  scaleMatrix.setToScale(scale);
  m_rotScale *= scaleMatrix;
}

// Scale locally using a non-uniform scale.
void
Transform::scaleLocal (float scaleX, float scaleY, float scaleZ)
{
  Matrix3 scaleMatrix;
  scaleMatrix.setToScale(scaleX, scaleY, scaleZ);
  m_rotScale *= scaleMatrix;
}

// Scale wrt world using a uniform scale.
void
Transform::scaleWorld (float scale)
{
  Matrix3 scaleMatrix;
  scaleMatrix.setToScale(scale);
  m_rotScale = scaleMatrix * m_rotScale;
  m_position = scaleMatrix * m_position;
}

// Scale wrt world using a non-uniform scale.
void
Transform::scaleWorld (float scaleX, float scaleY, float scaleZ)
{
  Matrix3 scaleMatrix;
  scaleMatrix.setToScale(scaleX, scaleY, scaleZ);
  m_rotScale = scaleMatrix * m_rotScale;
  m_position = scaleMatrix * m_position;
}

// Shear local X by Y and Z. 
void
Transform::shearLocalXByYz (float shearY, float shearZ)
{
  Matrix3 shearMatrix;
  shearMatrix.setToShearXByYz(shearY, shearZ);
  m_rotScale *= shearMatrix;
}

// Shear local Y by X and Z. 
void
Transform::shearLocalYByXz (float shearX, float shearZ)
{
  Matrix3 shearMatrix;
  shearMatrix.setToShearYByXz(shearX, shearZ);
  m_rotScale *= shearMatrix;
}

// Shear local Z by X and Y. 
void
Transform::shearLocalZByXy (float shearX, float shearY)
{
  Matrix3 shearMatrix;
  shearMatrix.setToShearZByXy(shearX, shearY);
  m_rotScale *= shearMatrix;
}

// Invert this transform assuming it consists of a pure rotation
  //   and a translation.
  // This can be used to compute the view transform. 
void
Transform::invertRt ()
{
  m_rotScale.invertRotation();
  m_position = m_rotScale * (-m_position);
}

Transform
Transform::invertRtR ()
{
  Transform t = *this;
  t.invertRt();
  return t;
}

void
Transform::invert()
{
  m_rotScale.invert();
  m_position = m_rotScale * (-m_position);
}

// Combine this with "t" in the order this * t. 
void
Transform::combine (const Transform& t)
{
  m_position += m_rotScale.transform(t.getPosition());
  m_rotScale *= t.getOrientation();
}

Vector3
Transform::translate(Vector3 position)
{
  return m_rotScale * position + m_position;
}

std::ostream&
operator<< (std::ostream& out, const Transform& t)
{
  std::ios_base::fmtflags origState = out.flags();
  out << std::endl << std::setprecision(2) << std::setw(10)
    << t.getOrientation().getRight().x << std::setw(10) << t.getOrientation().getUp().x << std::setw(10) 
    << t.getOrientation().getBack().x << "\n" << std::setw(10)
    << t.getOrientation().getRight().y << std::setw(10) << t.getOrientation().getUp().y << std::setw(10) 
    << t.getOrientation().getBack().y << "\n" << std::setw(10)
    << t.getOrientation().getRight().z << std::setw(10) << t.getOrientation().getUp().z << std::setw(10) 
    << t.getOrientation().getBack().z
    << std::setw(10) << 0 << std::setw(10) << 0 << std::setw(10) << 0 << std::setw(10) << 1 
    << std::endl << std::endl;
  out.flags( origState );
  return out;
}