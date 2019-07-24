/*
  FileName    : KeyBuffer.h
  Author      : Zachary Zuch
  Course      : CSCI 375
  Assignment  : Lab 4
  Description : Key Buffer Interface
*/

#ifndef KEYBUFFER_H
#define KEYBUFFER_H

#define IS_KEY_DOWN_ARRAY_SIZE 349

#include <boost/dynamic_bitset.hpp>

class KeyBuffer
{
public:

	KeyBuffer ();

	void
	setKeyDown (int key);

	void
	reset ();

	void
	setKeyUp (int key);

	bool
	isKeyDown (int key) const;

	bool
	operator[] (int index) const;

private:

	boost::dynamic_bitset<> m_isKeyDownArray;
};

#endif