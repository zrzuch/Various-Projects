/*
  Filename   : ReplaceByte.c
  Author     : Zachary R. Zuch
  Course     : CSCI 370-02
  Assignment : Lab 5 - Replace Byte Function
  Description: This program is used to implement a function that replaces
                 a byte in a specific byte with a specific byte which is
		 all chosen by the user.
 */

/*************************************************/

// System Includes
#include <stdio.h>
#include <stdlib.h>

/*************************************************/

// Prototypes
unsigned
replace_byte (unsigned x, int i, unsigned char b);

/*************************************************/

int
main (int argc, char* argv[])
{
  printf ("x ==> ");
  unsigned x;
  scanf ("%x", &x);
  
  printf ("i ==> ");
  int i;
  scanf ("%d", &i);
  
  printf ("b ==> ");
  unsigned char b;
  scanf ("%hhx", &b);

  printf ("\nReplacing byte %d of 0x%x with 0x%x \n  results in 0x%x.\n",
	  i, x, b, replace_byte(x, i, b));

  return EXIT_SUCCESS;
}

/*************************************************/

unsigned
replace_byte (unsigned x, int i, unsigned char b)
{
  int shift = i << 3;
  int newHex = b << shift;
  int mask = 0xFF << shift;
  return (~mask & x) + newHex;
}

/*************************************************/
