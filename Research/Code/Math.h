#ifndef MATH_H
#define MATH_H

#include <cmath>
#include "Vector3.h"

namespace Math
{
  extern const float PI;
  extern const float DEFAULT_TOLERANCE;

  float
  toRadians (float degrees);

  float
  toDegrees (float radians);

  template <class valType>
  valType 
  clamp(valType x, valType min, valType max)
  {
    return std::min(std::max(x, min), max);
  }

  // is x in (min, max)
  template <class valType>
  bool 
  within(valType x, valType min, valType max)
  {
    if (x <= min) return false;
    if (x >= max) return false;
    return true;
  }

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