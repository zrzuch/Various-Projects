/*
  FileName    : KeyBuffer.cpp
  Author      : Zachary Zuch
  Course      : CSCI 375
  Assignment  : Lab 4
  Description : Key Buffer Implementation
*/
#include "KeyBuffer.h"

// Initialize the buffer with all keys set to up
// The size of the buffer should be "GLFW_KEY_LAST + 1" = 349
KeyBuffer::KeyBuffer ()
	: m_isKeyDownArray(IS_KEY_DOWN_ARRAY_SIZE, false)
{ }

// Record that "key" is down
void
KeyBuffer::setKeyDown (int key)
{
	m_isKeyDownArray[ key ] = true;
}

// Record that all keys are up
void
KeyBuffer::reset ()
{
	m_isKeyDownArray.reset();
}

// Record that "key" is up
void
KeyBuffer::setKeyUp (int key)
{
	m_isKeyDownArray[ key ] = false;
}

// Return true if "key" is down, false o/w
bool
KeyBuffer::isKeyDown (int key) const
{
	return m_isKeyDownArray[ key ];
}

bool
KeyBuffer::operator[] (int index) const
{
	return isKeyDown(index);
}