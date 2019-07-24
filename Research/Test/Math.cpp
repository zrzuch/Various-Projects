#include <limits>
#include "Math.h"

namespace Math
{
  const float PI = 3.14159265;
  const float DEFAULT_TOLERANCE = std::numeric_limits<float>::epsilon();

  float
  toRadians (float degrees)
  {
    return degrees * (PI/180);
  }

  float
  toDegrees (float radians)
  {
    return radians * (180/PI);
  }

  bool
  equalsUsingTolerance (float n1, float n2, float tolerance)
  {
    float delta = std::abs (n1 - n1);
    return delta <= tolerance;
  }

  bool
  equalsUsingTolerance (const Vector3 &v1, const Vector3& v2, 
                float tolerance)
  {
    return equalsUsingTolerance (v1.x, v2.x, tolerance)
        && equalsUsingTolerance (v1.y, v2.y, tolerance)
        && equalsUsingTolerance (v1.z, v2.z, tolerance);
  }

  bool
  equalsPlusOrMinusUsingTolerance (const Vector3 &v1, const Vector3& v2,
                float tolerance)
  {
    return equalsUsingTolerance(std::abs(v1.x), std::abs(v2.x), tolerance)
        && equalsUsingTolerance(std::abs(v1.y), std::abs(v2.y), tolerance)
        && equalsUsingTolerance(std::abs(v1.z), std::abs(v2.z), tolerance);
  }
}
