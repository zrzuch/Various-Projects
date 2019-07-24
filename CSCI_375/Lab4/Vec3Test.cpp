#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>

#include <glm/gtc/matrix_transform.hpp>

#include "Vector3.h"

void
printVector(const Vector3&, const std::string&, const std::string&);

void
printValue(float x, const std::string&, const std::string&);

int
main (int argc, char* argv[])
{
  Vector3 vec;
  Vector3 vec2( 8 );
  Vector3 vec3( 1, 2, 3 );

  printVector( vec, "Default Constructor", "( 0, 0, 0 )");
  printVector( vec2, "One Value Constructor", "( 8, 8, 8 )");
  printVector( vec3, "Each Value Constructor", "( 1, 2, 3 )");

  vec.set(4);
  vec2.set(5,6,7);
  vec3.negate();

  printVector( vec, "Set All Values", "( 4, 4, 4 )");
  printVector( vec2, "Set Each Value", "( 5, 6, 7 )");
  printVector( vec3, "Negate Vector", "( -1, -2, -3 )");

  printValue( vec3.dot(vec2), "Vec3 DOT Vec2", "-38");
  printValue( vec3.angleBetween(vec2), "Angle Between Vec3 and Vec2",
    "165.534906374");

  printVector( vec3.cross(vec), "Vec3 x Vec", "( 4, -8, 4 )");

  printValue( vec3.length(), "Vec3 Length", "3.741657387");

  vec2.normalize();

  printVector( vec2, "Vec2 Normal", "( 0.4767, 0.5721, 0.6674 )");
  
  vec2 += vec;
  vec3 -= vec;
  vec *= 8;

  printVector( vec, "vec *= 8", "( 32, 32, 32 )");
  printVector( vec2, "vec2 += vec", "( 4.4767, 4.5721, 4.6674 )");
  printVector( vec3, "vec3 -= vec", "( -5, -6, -7 )");

  vec /= 8;
  printVector( vec, "vec /= 8", "( 4, 4, 4 )");

  printVector( vec + vec2, "vec + vec2", "( 8.4767, 8.5721, 8.6674 )");
  printVector( vec - vec3, "vec - vec3", "( 9, 10, 11 )");
  printVector( vec3 * -4.0f, "operator*", "( 20, 24, 28 )");
  printVector( -4.0f * vec3, "*operator", "( 20, 24, 28 )");
  printVector( vec3 / 2.0f , "operator/", "( -2.5, -3, -3.5 )");

  return EXIT_SUCCESS;
}

void
printVector( const Vector3& v, const std::string& test_value, 
  const std::string& expected_value )
{
  std::cout << "\n" << test_value << "\n" 
    << "( X, Y, Z ) = ( " << v.x << ", "
    << v.y << ", " << v.z << " )" << "\n" 
    << "Expected Value = " << expected_value << std::endl;
}

void
printValue( float x, const std::string& test_value, 
  const std::string& expected_value )
{
  std::cout << "\n" << test_value << " = " << x << "\n" 
    << "Expected Value = " << expected_value << std::endl;
}