// Matrix4 class for representing 4x4 matrices. 
// Author: Gary M. Zoppetti, Ph.D.

#ifndef MATRIX4_H
#define MATRIX4_H

#include <iostream>

#include "Vector4.h"

// Basis vectors are stored in Vector4-s and form
//   the columns of a 4x4 matrix. 
// The matrix is interpreted thus:
// [ rx ux bx tx ]
// [ ry uy by ty ]
// [ rz uz bz tz ]
// [ rw uw bw tw ]

// If the last row contains [ 0 0 0 1 ] the transform is affine,
//   otherwise it is projective.

// Operations are consistent with column vectors (v' = M * v).
class Matrix4
{
public:

  Vector4 m_right;
  Vector4 m_up;
  Vector4 m_back;
  Vector4 m_translation;

  // Initialize to identity. 
  Matrix4 ();

  Matrix4(const Vector4& right, const Vector4& up, 
    const Vector4& back, const Vector4& translation);

  Matrix4(const Vector4& position);

  Matrix4(float rx, float ry, float rz, float rw,
          float ux, float uy, float uz, float uw,
          float bx, float by, float bz, float bw,
          float tx, float ty, float tz, float tw);

  // Set to identity matrix. 
  void
  setToIdentity ();

  // Set to zero matrix. 
  void
  setToZero ();
    
  // Return a const pointer to the first element.
  const float*
  data () const;

  float
  determinate();

  void
  transpose();

  void
  invert();

  Vector4
  transform(const Vector4& v);

  // For the projection methods, do all computations using
  //   double-s and only cast to float when NECESSARY. 

  // Set this to a perspective projection matrix. 
  void
  setToPerspectiveProjection (double fovYDegrees, double aspectRatio,
			      double nearPlaneZ, double farPlaneZ);

  // Set this to a perspective projection matrix using the
  //   6 clip planes specified as parameters. 
  void
  setToPerspectiveProjection (double left, double right,
			      double bottom, double top,
			      double nearPlaneZ, double farPlaneZ);

  // Set this to an orthographic projection matrix using the
  //   6 clip planes specified as parameters. 
  void
  setToOrthographicProjection (double left, double right,
			       double bottom, double top,
			       double nearPlaneZ, double farPlaneZ);
  Matrix4&
  operator*= (const Matrix4& m);
};

std::ostream&
operator<< (std::ostream& out, const Matrix4& m);

#endif
