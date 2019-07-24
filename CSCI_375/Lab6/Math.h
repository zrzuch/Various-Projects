#ifndef MATH_H
#define MATH_H

#include "Vector3.h"

namespace Math
{
  extern float PI;
  extern float DEFAULT_TOLERANCE;

  float
  toRadians (float degrees);

  float
  toDegrees (float radians);

  bool
  equalsUsingTolerance (float n1, float n2, float tolerance = DEFAULT_TOLERANCE);

  bool
  equalsUsingTolerance (const Vector3 &v1, const Vector3& v2, 
  	float tolerance = DEFAULT_TOLERANCE);

  bool
  equalsPlusOrMinusUsingTolerance (const Vector3 &v1, const Vector3& v2, 
  	float tolerance = DEFAULT_TOLERANCE);
}

#endif