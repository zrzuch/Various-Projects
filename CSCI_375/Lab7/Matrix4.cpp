#include <cmath>
#include "Math.h"

#include "Matrix4.h"

// Initialize to identity. 
Matrix4::Matrix4 ()
: m_right      (1,0,0,0)
, m_up         (0,1,0,0)
, m_back       (0,0,1,0)
, m_translation(0,0,0,1)
{ }

Matrix4::Matrix4(const Vector4& right, const Vector4& up, 
    const Vector4& back, const Vector4& translation)
: m_right(right), m_up(up), m_back(back), m_translation(translation)
{ }

Matrix4::Matrix4(float rx, float ry, float rz, float rw,
          float ux, float uy, float uz, float uw,
          float bx, float by, float bz, float bw,
          float tx, float ty, float tz, float tw)
: m_right      (rx, ry, rz, rw)
, m_up         (ux, uy, uz, uw)
, m_back       (bx, by, bz, bw)
, m_translation(tx, ty, tz, tw)
{ }

// Set to identity matrix. 
void
Matrix4::setToIdentity ()
{
  m_right       = {1,0,0,0};
  m_up          = {0,1,0,0};
  m_back        = {0,0,1,0};
  m_translation = {0,0,0,1};
}

// Set to zero matrix. 
void
Matrix4::setToZero ()
{
  m_right.set(0);
  m_up.set(0);
  m_back.set(0);
  m_translation.set(0);
}
  
// Return a const pointer to the first element.
const float*
Matrix4::data () const
{
  return m_right.data();
}

glm::mat4
Matrix4::getMat4 () const
{
  return
  { 
    m_right.x,       m_right.y,       m_right.z,       m_right.w,
    m_up.x,          m_up.y,          m_up.z,          m_up.w,
    m_back.x,        m_back.y,        m_back.z,        m_back.w,
    m_translation.x, m_translation.y, m_translation.z, m_translation.w
  };
}

// For the projection methods, do all computations using
//   double-s and only cast to float when NECESSARY. 

// Set this to a perspective projection matrix. 
void
Matrix4::setToPerspectiveProjection (double fovYDegrees, double aspectRatio,
		      double nearPlaneZ, double farPlaneZ)
{
  double tanFOVdiv2 = tan( Math::toRadians(fovYDegrees) / 2);
  double a00 = 1 / (aspectRatio * tanFOVdiv2);
  double a11 = 1 / tanFOVdiv2;
  double a22 = (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ);
  double a23 = (2 * nearPlaneZ * farPlaneZ) / (nearPlaneZ - farPlaneZ);

  m_right       = {(float)a00, 0,           0,          0 };
  m_up          = {0,          (float)a11,  0,          0 };
  m_back        = {0,          0,           (float)a22, -1};
  m_translation = {0,          0,           (float)a23, 0 };
}

// Set this to a perspective projection matrix using the
//   6 clip planes specified as parameters. 
void
Matrix4::setToPerspectiveProjection (double left, double right,
		      double bottom, double top,
		      double nearPlaneZ, double farPlaneZ)
{
  double a00 = 2 * nearPlaneZ / (right - left);
  double a11 = 2 * nearPlaneZ / (top - bottom);
  double a02 = (right + left) / (right - left);
  double a12 = (top + bottom) / (top - bottom);
  double a22 = (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ);
  double a23 = (2 * nearPlaneZ * farPlaneZ) / (nearPlaneZ - farPlaneZ);

  m_right       = {(float)a00, 0,          0,          0 };
  m_up          = {0,          (float)a11, 0,          0 };
  m_back        = {(float)a02, (float)a12, (float)a22, -1};
  m_translation = {0,          0,          (float)a23, 0 };
}

// Set this to an orthographic projection matrix using the
//   6 clip planes specified as parameters. 
void
Matrix4::setToOrthographicProjection (double left, double right,
		       double bottom, double top,
		       double nearPlaneZ, double farPlaneZ)
{
  double nearFarDist = nearPlaneZ - farPlaneZ;
  double a00 = 2/(right-left);
  double a11 = 2/(top-bottom);
  double a22 = 2/nearFarDist;
  double a03 = -(right + left) / (right - left);
  double a13 = -(top + bottom) / (top - bottom);
  double a23 = (nearPlaneZ + farPlaneZ) / nearFarDist;
  
  m_right       = {(float)a00, 0,          0,          0};
  m_up          = {0,          (float)a11, 0,          0};
  m_back        = {0,          0,          (float)a22, 0};
  m_translation = {(float)a03, (float)a13, (float)a23, 1};
}