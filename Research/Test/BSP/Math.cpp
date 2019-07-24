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

  // float
  // getLargestEigenValue(Matrix3& A)
  // {
  //   // ax^3 + bx^2 + cx + d
  //   constexpr float a = -1;

  //   float b = A.getValue(0,0) 
  //           + A.getValue(1,1) 
  //           + A.getValue(2,2);

  //   float c = (A.getValue(1,2) * A.getValue(2,1)) 
  //           + (A.getValue(0,1) * A.getValue(1,0)) 
  //           + (A.getValue(0,2) * A.getValue(2,0))
  //           - (A.getValue(0,0) * A.getValue(1,1)) 
  //           - (A.getValue(0,0) * A.getValue(2,2)) 
  //           - (A.getValue(1,1) * A.getValue(2,2));

  //   float d = (A.getValue(0,0) * A.getValue(1,1) * A.getValue(2,2)) 
  //           + (A.getValue(0,1) * A.getValue(1,2) * A.getValue(2,0)) 
  //           + (A.getValue(0,2) * A.getValue(1,0) * A.getValue(2,1)) 
  //           - (A.getValue(0,0) * A.getValue(1,2) * A.getValue(2,1)) 
  //           - (A.getValue(0,0) + A.getValue(1,1) + A.getValue(2,2)) 
  //           - (A.getValue(0,2) + A.getValue(1,1) + A.getValue(2,0));

  //   float p = b / 3;
  //   float q = (p * p * p) + ((b * c) + ((3 * d) / 6));
  //   float r = -c / 3;

  //   float innerRP2 = r - (p * p);
  //   // float innerRP2to3 = innerRP2 * innerRP2 * innerRP2;
  //   float innerSqrt = (q * q) + (innerRP2 * innerRP2 * innerRP2);
  //   float 
  // }
}
