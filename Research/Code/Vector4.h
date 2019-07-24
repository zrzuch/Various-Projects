// Vector4 class for representing 4-vectors.
// Author: Gary M. Zoppetti, Ph.D.

#ifndef VECTOR4_H
#define VECTOR4_H

#include <iostream>

class Vector4
{
public:
  // Initialize to zero vector.
  Vector4 ();

  // Initialize each component from "xyzw". 
  explicit
  Vector4 (float xyzw);

  // Initialize with corresponding parameter. 
  Vector4 (float x, float y, float z, float w);

  // Return a const pointer to the first element. 
  const float*
  data () const;

  // Assign each data member "xyzw". 
  void
  set (float xyzw);

  // Assign each data member from corresponding parameter. 
  void
  set (float x, float y, float z, float w);

  // Compute this dot "v". 
  float
  dot (const Vector4& v) const;

  float
  dot (float x, float y, float z, float w) const;

  // Compute length of this. 
  float
  length () const;

  // Normalize this. 
  void
  normalize ();

  // Negate this. 
  void
  negate ();

  // Operators
  Vector4&
  operator+= (const Vector4& v);

  Vector4&
  operator-= (const Vector4& v);

  Vector4&
  operator*= (const Vector4& v);

  Vector4&
  operator*= (float scalar);

  Vector4&
  operator/= (float scalar);

public:
  float x, y, z, w;
};
  
// These free operators MUST call the corresponding member functions. 
Vector4
operator+ (const Vector4& v1, const Vector4& v2);

Vector4
operator- (const Vector4& v1, const Vector4& v2);

// Unary negation. Calls member "negate". 
Vector4
operator- (const Vector4& v);

Vector4
operator* (const Vector4& v1, const Vector4& v2);

Vector4
operator* (const Vector4& v, float scalar);

Vector4
operator* (float scalar, const Vector4& v);

Vector4
operator/ (const Vector4& v, float scalar);

// Output "v" using TWO digits of precision and a
//   field width of 10 for each component. 
std::ostream&
operator<< (std::ostream& out, const Vector4& v);

#endif
