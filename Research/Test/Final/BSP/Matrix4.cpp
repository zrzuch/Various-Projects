#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
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

Vector4
Matrix4::transform(const Vector4& v)
{
  return
  {
    v.dot(m_right.x, m_up.x, m_back.x, m_translation.x),
    v.dot(m_right.y, m_up.y, m_back.y, m_translation.y),
    v.dot(m_right.z, m_up.z, m_back.z, m_translation.z),
    v.dot(m_right.w, m_up.w, m_back.w, m_translation.w)
  };
}

void
Matrix4::transpose()
{
  std::swap( m_right.y, m_up.x          );
  std::swap( m_right.z, m_back.x        );
  std::swap( m_right.w, m_translation.x );
  
  std::swap( m_translation.y, m_up.w    );
  std::swap( m_translation.z, m_back.w  );

  std::swap( m_up.z, m_back.y           );
}

float
Matrix4::determinate()
{
  float a00 = m_up.y  * m_back.z * m_translation.w - 
  m_up.y  * m_translation.z * m_back.w - 
  m_up.z  * m_back.y  * m_translation.w + 
  m_up.z  * m_translation.y  * m_back.w +
  m_up.w * m_back.y  * m_translation.z - 
  m_up.w * m_translation.y  * m_back.z;

  float a10 = -m_right.y  * m_back.z * m_translation.w + 
  m_right.y  * m_translation.z * m_back.w + 
  m_right.z  * m_back.y  * m_translation.w - 
  m_right.z  * m_translation.y  * m_back.w - 
  m_right.w * m_back.y  * m_translation.z + 
  m_right.w * m_translation.y  * m_back.z;

  float a20 = m_right.y  * m_up.z * m_translation.w - 
  m_right.y  * m_translation.z * m_up.w - 
  m_right.z  * m_up.y * m_translation.w + 
  m_right.z  * m_translation.y * m_up.w + 
  m_right.w * m_up.y * m_translation.z - 
  m_right.w * m_translation.y * m_up.z;

  float a30 = -m_right.y  * m_up.z * m_back.w + 
  m_right.y  * m_back.z * m_up.w +
  m_right.z  * m_up.y * m_back.w - 
  m_right.z  * m_back.y * m_up.w - 
  m_right.w * m_up.y * m_back.z + 
  m_right.w * m_back.y * m_up.z;

  return m_right.x * a00 + m_up.x * a10 + m_back.x * a20 + m_translation.x * a30;
}

void
Matrix4::invert()
{
    float det = determinate();
    if (det == 0.0)
    {
        return;
    }
    det = 1 / det;

    float a00 = m_up.y  * m_back.z * m_translation.w - 
                m_up.y  * m_translation.z * m_back.w - 
                m_up.z  * m_back.y  * m_translation.w + 
                m_up.z  * m_translation.y  * m_back.w +
                m_up.w * m_back.y  * m_translation.z - 
                m_up.w * m_translation.y  * m_back.z;
    a00 *= det;

    float a10 = -m_right.y  * m_back.z * m_translation.w + 
                m_right.y  * m_translation.z * m_back.w + 
                m_right.z  * m_back.y  * m_translation.w - 
                m_right.z  * m_translation.y  * m_back.w - 
                m_right.w * m_back.y  * m_translation.z + 
                m_right.w * m_translation.y  * m_back.z;
    a10 *= det;

    float a20 = m_right.y  * m_up.z * m_translation.w - 
                m_right.y  * m_translation.z * m_up.w - 
                m_right.z  * m_up.y * m_translation.w + 
                m_right.z  * m_translation.y * m_up.w + 
                m_right.w * m_up.y * m_translation.z - 
                m_right.w * m_translation.y * m_up.z;
    a20 *= det;

    float a30 = -m_right.y  * m_up.z * m_back.w + 
                m_right.y  * m_back.z * m_up.w +
                m_right.z  * m_up.y * m_back.w - 
                m_right.z  * m_back.y * m_up.w - 
                m_right.w * m_up.y * m_back.z + 
                m_right.w * m_back.y * m_up.z;
    a30 *= det;

    float a01 = -m_up.x  * m_back.z * m_translation.w + 
                m_up.x  * m_translation.z * m_back.w + 
                m_up.z  * m_back.x * m_translation.w - 
                m_up.z  * m_translation.x * m_back.w - 
                m_up.w * m_back.x * m_translation.z + 
                m_up.w * m_translation.x * m_back.z;
    a01 *= det;

    float a11 = m_right.x  * m_back.z * m_translation.w - 
                m_right.x  * m_translation.z * m_back.w - 
                m_right.z  * m_back.x * m_translation.w + 
                m_right.z  * m_translation.x * m_back.w + 
                m_right.w * m_back.x * m_translation.z - 
                m_right.w * m_translation.x * m_back.z;
    a11 *= det;

    float a21 = -m_right.x  * m_up.z * m_translation.w + 
                m_right.x  * m_translation.z * m_up.w + 
                m_right.z  * m_up.x * m_translation.w - 
                m_right.z  * m_translation.x * m_up.w - 
                m_right.w * m_up.x * m_translation.z + 
                m_right.w * m_translation.x * m_up.z;
    a21 *= det;

    float a31 = m_right.x  * m_up.z * m_back.w - 
                m_right.x  * m_back.z * m_up.w - 
                m_right.z  * m_up.x * m_back.w + 
                m_right.z  * m_back.x * m_up.w + 
                m_right.w * m_up.x * m_back.z - 
                m_right.w * m_back.x * m_up.z;
    a31 *= det;

    float a02 = m_up.x  * m_back.y * m_translation.w - 
                m_up.x  * m_translation.y * m_back.w - 
                m_up.y  * m_back.x * m_translation.w + 
                m_up.y  * m_translation.x * m_back.w + 
                m_up.w * m_back.x * m_translation.y - 
                m_up.w * m_translation.x * m_back.y;
    a02 *= det;

    float a12 = -m_right.x  * m_back.y * m_translation.w + 
                m_right.x  * m_translation.y * m_back.w + 
                m_right.y  * m_back.x * m_translation.w - 
                m_right.y  * m_translation.x * m_back.w - 
                m_right.w * m_back.x * m_translation.y + 
                m_right.w * m_translation.x * m_back.y;
    a12 *= det;

    float a22 = m_right.x  * m_up.y * m_translation.w - 
                m_right.x  * m_translation.y * m_up.w - 
                m_right.y  * m_up.x * m_translation.w + 
                m_right.y  * m_translation.x * m_up.w + 
                m_right.w * m_up.x * m_translation.y - 
                m_right.w * m_translation.x * m_up.y;
    a22 *= det;

    float a32 = -m_right.x  * m_up.y * m_back.w + 
                m_right.x  * m_back.y * m_up.w + 
                m_right.y  * m_up.x * m_back.w - 
                m_right.y  * m_back.x * m_up.w - 
                m_right.w * m_up.x * m_back.y + 
                m_right.w * m_back.x * m_up.y;
    a32 *= det;

    float a03 = -m_up.x * m_back.y * m_translation.z + 
                m_up.x * m_translation.y * m_back.z + 
                m_up.y * m_back.x * m_translation.z - 
                m_up.y * m_translation.x * m_back.z - 
                m_up.z * m_back.x * m_translation.y + 
                m_up.z * m_translation.x * m_back.y;
    a03 *= det;

    float a13 = m_right.x * m_back.y * m_translation.z - 
                m_right.x * m_translation.y * m_back.z - 
                m_right.y * m_back.x * m_translation.z + 
                m_right.y * m_translation.x * m_back.z + 
                m_right.z * m_back.x * m_translation.y - 
                m_right.z * m_translation.x * m_back.y;
    a13 *= det;

    float a23 = -m_right.x * m_up.y * m_translation.z + 
                m_right.x * m_translation.y * m_up.z + 
                m_right.y * m_up.x * m_translation.z - 
                m_right.y * m_translation.x * m_up.z - 
                m_right.z * m_up.x * m_translation.y + 
                m_right.z * m_translation.x * m_up.y;
    a23 *= det;

    float a33 = m_right.x * m_up.y * m_back.z - 
                m_right.x * m_back.y * m_up.z - 
                m_right.y * m_up.x * m_back.z + 
                m_right.y * m_back.x * m_up.z + 
                m_right.z * m_up.x * m_back.y - 
                m_right.z * m_back.x * m_up.y;
    a33 *= det;

    (*this) = Matrix4
    (
        a00, a10, a20, a30,
        a01, a11, a21, a31,
        a02, a12, a22, a32,
        a03, a13, a23, a33
    );
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

Matrix4&
Matrix4::operator*= (const Matrix4& m)
{
  Vector4 newRight        = transform(m.m_right);
  Vector4 newUp           = transform(m.m_up);
  Vector4 newBack         = transform(m.m_back);
  Vector4 newTranslation  = transform(m.m_translation);

  m_right         = newRight;
  m_up            = newUp;
  m_back          = newBack;
  m_translation   = newTranslation;

  return *this;
}

std::ostream&
operator<< (std::ostream& out, const Matrix4& m)
{
    std::ios_base::fmtflags origState = out.flags();
    
    out << std::setprecision(2) << std::setw(10)
    << m.m_right.x << std::setw(10) << m.m_up.x << std::setw(10) << m.m_back.x << std::setw(10) << m.m_translation.x << "\n"
    << std::setw(10)
    << m.m_right.y << std::setw(10) << m.m_up.y << std::setw(10) << m.m_back.y << std::setw(10) << m.m_translation.y << "\n"
    << std::setw(10)
    << m.m_right.z << std::setw(10) << m.m_up.z << std::setw(10) << m.m_back.z << std::setw(10) << m.m_translation.z << "\n"
    << std::setw(10)
    << m.m_right.w << std::setw(10) << m.m_up.w << std::setw(10) << m.m_back.w << std::setw(10) << m.m_translation.w << "\n\n";

    out.flags( origState );
    return out;
}