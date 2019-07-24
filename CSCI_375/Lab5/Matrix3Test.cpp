/* A simple testing framework for testing scalar, Vector3,
     and Matrix3 methods. 
   Author: Gary M. Zoppetti, Ph.D.
*/

#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

#include "Matrix3.h"
#include "Vector3.h"

// ENSURE you define operator<< for your Vector3 class,
//   similar to what you've done for Matrix3!

/************************************************************/
template <typename T>
void
printTestResult (const std::string& test,
     const T& expected,
     const T& actual);

template <typename T>
void
printTestResult (const std::string& test,
     const T& expected,
     const T& actual,
     float tolerance);

bool
equalsTolerance (float s1, float s2,
     float tolerance);

bool
equalsTolerance (const Vector3 &v1, const Vector3& v2,
     float tolerance);

bool
equalsTolerance (const Matrix3& m1, const Matrix3& m2,
     float tolerance);

/************************************************************/

int
main ()
{
  // Since Print Precision is 2
  const float TOLERANCE_TEST = 0.01f;
  const float theta = 45.0f;
  const float cos_theta = glm::cos( glm::radians( theta ));
  const float sin_theta = glm::sin( glm::radians( theta ));
  
  // Tested at the beginning to show that flags are maintained
  std::cout << 0.0001f << std::endl;
  std::cout << Matrix3(1,4,7,2,5,8,3,6,9);
  std::cout << 0.0001f << std::endl;

  const Matrix3 identity;
  Matrix3 identityExp (1, 0, 0,    0, 1, 0,    0, 0, 1);
  printTestResult ("Default ctor", identityExp, identity, TOLERANCE_TEST);

  Matrix3 set    (1, 2, 3,    4, 5, 6,    7, 8, 9);
  Matrix3 setExp (1, 2, 3,    4, 5, 6,    7, 8, 9);
  printTestResult ("Set ctor", setExp, set, TOLERANCE_TEST);

  Matrix3 setVector(Vector3(10, 11, 12), Vector3(10, 11, 12), Vector3(10, 11, 12));
  Matrix3 setVectorExp     (10, 11, 12,          10, 11, 12,          10, 11, 12);
  printTestResult ("Set Vector ctor", setVectorExp, setVector, TOLERANCE_TEST);

  Matrix3 setCross(Vector3(1,2,3), Vector3(4,5,6));
  Matrix3 setCrossExp(1,2,3,4,5,6,-3,6,-3);
  printTestResult ("Set Vector Cross ctor", setCrossExp, setCross, TOLERANCE_TEST);

  Matrix3 setOrtho(Vector3(2,0,0), Vector3(0,2,0), true);
  Matrix3 setOrthoExp;
  printTestResult ("Set Vector Cross ctor", setOrthoExp, setOrtho, TOLERANCE_TEST);

  set.setToIdentity();
  printTestResult ("setToIdentity", identity, set, TOLERANCE_TEST);

  set.setToZero();
  Matrix3 zero(0,0,0,0,0,0,0,0,0);
  printTestResult ("setToZero", zero, set, TOLERANCE_TEST);

  printTestResult("data", set.getRight().x, *set.data());
  printTestResult("const data", identity.getRight().x, *identity.data());

  Matrix3 actualMatrix;
  actualMatrix.setRight(Vector3(1,2,3));
  Matrix3 expectedMatrix(1,2,3,0,1,0,0,0,1);
  printTestResult("setRight", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  printTestResult("getRight", Vector3(1,2,3), 
    actualMatrix.getRight(), TOLERANCE_TEST);

  actualMatrix.setUp(Vector3(4,5,6));
  expectedMatrix = Matrix3(1,2,3,4,5,6,0,0,1);
  printTestResult("setUp", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  printTestResult("getUp", Vector3(4,5,6), actualMatrix.getUp(), 
    TOLERANCE_TEST);

  actualMatrix.setBack(Vector3(7,8,9));
  expectedMatrix = Matrix3(1,2,3,4,5,6,7,8,9);
  printTestResult("setBack", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  printTestResult("getBack", Vector3(7,8,9), actualMatrix.getBack(), 
    TOLERANCE_TEST);

  actualMatrix.setForward(Vector3(7,8,9));
  expectedMatrix = Matrix3(1,2,3,4,5,6,-7,-8,-9);
  printTestResult("setForward", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  printTestResult("getForward", Vector3(7,8,9), actualMatrix.getForward(), 
    TOLERANCE_TEST);

  actualMatrix.setToRotationX( theta );
  expectedMatrix = Matrix3(1,0,0,0,cos_theta,-sin_theta,0,sin_theta,cos_theta);
  actualMatrix.invertRotation();
  printTestResult("invertRotation", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  actualMatrix = Matrix3(3,2,0,0,0,1,2,-2,1);
  actualMatrix.invert();
  expectedMatrix = Matrix3(0.2f,-0.2f,0.2f,0.2f,0.3f,-0.3f,0,1,0);
  printTestResult("invert", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  actualMatrix = Matrix3(3,2,0,0,0,1,2,-2,1);
  printTestResult("determinant", 10.0f, actualMatrix.determinant(), TOLERANCE_TEST);

  actualMatrix = Matrix3(1,2,3,4,5,6,7,8,9);
  actualMatrix.transpose();
  expectedMatrix = Matrix3(1,4,7,2,5,8,3,6,9);
  printTestResult("transpose", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  actualMatrix = Matrix3(0,0,0,0,1,0,0.6f,0.8f,0);
  actualMatrix.orthonormalize();
  expectedMatrix = Matrix3(0,0,-1,-0.8f,0.6f,0,0.6f,0.8f,0);
  printTestResult("orthonormalize", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  actualMatrix.setToScale(5);
  expectedMatrix = Matrix3(5,0,0,0,5,0,0,0,5);
  printTestResult("setToScale", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  actualMatrix.setToScale(5,6,7);
  expectedMatrix = Matrix3(5,0,0,0,6,0,0,0,7);
  printTestResult("setToScale Sx Sy Sz", expectedMatrix, actualMatrix, 
    TOLERANCE_TEST);

  actualMatrix.setToShearXByYz(5,6);
  expectedMatrix = Matrix3(1,0,0,5,1,0,6,0,1);
  printTestResult("setToShearXByYz", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  actualMatrix.setToShearYByXz(5,6);
  expectedMatrix = Matrix3(1,5,0,0,1,0,0,6,1);
  printTestResult("setToShearYByXz", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  actualMatrix.setToShearZByXy(5,6);
  expectedMatrix = Matrix3(1,0,5,0,1,6,0,0,1);
  printTestResult("setToShearZByXy", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  actualMatrix.setToRotationX(theta);
  expectedMatrix = Matrix3(1,0,0,0,cos_theta,sin_theta,0,-sin_theta,cos_theta);
  printTestResult("setToRotationX", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  actualMatrix.setToRotationY(theta);
  expectedMatrix = Matrix3(cos_theta,0,-sin_theta,0,1,0,sin_theta,0,cos_theta);
  printTestResult("setToRotationY", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  actualMatrix.setToRotationZ(theta);
  expectedMatrix = Matrix3(cos_theta,sin_theta,0,-sin_theta,cos_theta,0,0,0,1);
  printTestResult("setToRotationZ", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  actualMatrix.setFromAngleAxis(theta, Vector3(1,0,0));
  expectedMatrix.setToRotationX(theta);
  printTestResult("setFromAngleAxis", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  actualMatrix.setFromAngleAxis(theta, Vector3(0,1,0));
  expectedMatrix.setToRotationY(theta);
  printTestResult("setFromAngleAxis", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  actualMatrix.setFromAngleAxis(theta, Vector3(0,0,1));
  expectedMatrix.setToRotationZ(theta);
  printTestResult("setFromAngleAxis", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  actualMatrix.setToIdentity();
  actualMatrix.negate();
  expectedMatrix = Matrix3(-1,0,0,0,-1,0,0,0,-1);
  printTestResult("negate", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  actualMatrix.setToShearXByYz(5,6);
  printTestResult("transform", Vector3(12,1,1), 
    actualMatrix.transform(Vector3(1,1,1)), TOLERANCE_TEST);

  actualMatrix.setToIdentity();
  actualMatrix += Matrix3(0,0,0,5,0,0,6,0,0);
  expectedMatrix.setToShearXByYz(5,6);
  printTestResult("operator+=", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  expectedMatrix.setToIdentity();
  actualMatrix -= Matrix3(0,0,0,5,0,0,6,0,0);
  printTestResult("operator-=", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  expectedMatrix.setToScale(5);
  actualMatrix *= 5;
  printTestResult("operator*= Scalar", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  actualMatrix = Matrix3(1,4,7,2,5,8,3,6,9);
  actualMatrix *= Matrix3(1,2,3,-1,-2,-3,1,1,1);
  expectedMatrix = Matrix3(14,32,50,-14,-32,-50,6,15,24);
  printTestResult("operator*=", expectedMatrix, actualMatrix, TOLERANCE_TEST);

  actualMatrix = Matrix3(1,2,3,4,5,6,7,8,9);
  expectedMatrix = Matrix3(2,3,4,5,6,7,8,9,10);
  printTestResult("operator+", expectedMatrix, 
    actualMatrix + Matrix3(1,1,1,1,1,1,1,1,1), TOLERANCE_TEST);

  expectedMatrix = Matrix3(0,1,2,3,4,5,6,7,8);
  printTestResult("operator-", expectedMatrix, 
    actualMatrix - Matrix3(1,1,1,1,1,1,1,1,1), TOLERANCE_TEST);

  actualMatrix = Matrix3(1,2,3,-1,-2,-3,1,1,1);
  expectedMatrix = Matrix3(-1,-2,-3,1,2,3,-1,-1,-1);
  printTestResult("Unary operator-", expectedMatrix, -actualMatrix, TOLERANCE_TEST);

  expectedMatrix.setToScale(5);
  actualMatrix.setToIdentity();
  printTestResult("Scalar operator*", expectedMatrix, 5 * actualMatrix, 
    TOLERANCE_TEST);

  printTestResult("operator* Scalar", expectedMatrix, actualMatrix * 5, 
    TOLERANCE_TEST);

  actualMatrix = Matrix3(1,4,7,2,5,8,3,6,9);
  expectedMatrix = Matrix3(14,32,50,-14,-32,-50,6,15,24);
  printTestResult("operator*", expectedMatrix, 
    actualMatrix * Matrix3(1,2,3,-1,-2,-3,1,1,1), TOLERANCE_TEST);

  printTestResult("operator*", Vector3(6,15,24), 
    actualMatrix * Vector3(1,1,1), TOLERANCE_TEST);

  return 0;
}

/************************************************************/

template <typename T>
void
printTestResult (const std::string& test,
     const T& expected,
     const T& actual)
{
  std::cout << "Test: " << test << std::endl;
  std::cout << "==========================" << std::endl;
  std::cout << "Expected: " << expected << std::endl;
  std::cout << "Actual  : " << actual << std::endl;
  std::cout << "==========================" << std::endl << std::endl;

  // Ensure the two results are the same.
  // Do NOT comment this out!
  assert (expected == actual);
}

/************************************************************/

template <typename T>
void
printTestResult (const std::string& test,
     const T& expected,
     const T& actual,
     float tolerance)
{
  std::cout << "Test: " << test << std::endl;
  std::cout << "==========================" << std::endl;
  std::cout << "Expected: " << expected << std::endl;
  std::cout << "Actual  : " << actual << std::endl;
  std::cout << "==========================" << std::endl << std::endl;

  // Ensure the two results are the same.
  // Do NOT comment this out!
  assert (equalsTolerance (expected, actual, tolerance));
}

/************************************************************/

bool
equalsTolerance (float s1, float s2,
     float tolerance)
{
  float delta = std::abs (s1 - s2);
  return delta <= tolerance;
}

/************************************************************/

bool
equalsTolerance (const Vector3 &v1, const Vector3& v2,
     float tolerance)
{
  return equalsTolerance (v1.x, v2.x, tolerance)
    && equalsTolerance (v1.y, v2.y, tolerance)
    && equalsTolerance (v1.z, v2.z, tolerance);
}

/************************************************************/

bool
equalsTolerance (const Matrix3& m1, const Matrix3& m2,
     float tolerance)
{
  return equalsTolerance (m1.getRight (), m2.getRight (),
        tolerance)
    && equalsTolerance (m1.getUp (), m2.getUp (),
      tolerance)
    && equalsTolerance (m1.getBack (), m2.getBack (),
      tolerance);
}
