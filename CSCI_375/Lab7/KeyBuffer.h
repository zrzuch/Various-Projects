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

#include <vector>

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

private:

	std::vector<bool> m_isKeyDownArray;
};

#endif