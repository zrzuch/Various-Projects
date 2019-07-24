/*
	Filename	: SquareArea.c
	Author		: Zachary Zuch
	Course		: CSCI 370
	Assignment	: Lab 2
	Description	: This program calculates the area of a room
	                  in yards.
*/

/************************************************************/
// System includes

#include <stdio.h>
#include <stdlib.h>

/************************************************************/
// Function prototypes/global vars/typedefs

float
convertFeetAndInchesToYards (int feet, int inches);

float
findArea(int feetLength, int inchesLength, int feetWidth, int inchesWidth);

/************************************************************/

int
main (int argc, char* argv[])
{
  int feetLength;
  printf ("Feet for the length   ==> ");
  scanf ("%d", &feetLength);
  
  int inchesLength;
  printf ("Inches for the length ==> ");
  scanf ("%d", &inchesLength);
  
  int feetWidth;
  printf ("Feet for the width    ==> ");
  scanf ("%d", &feetWidth);
  
  int inchesWidth;
  printf ("Inches for the width  ==> ");
  scanf ("%d", &inchesWidth);
  
  printf ("\nFor a room that is %d feet %d inches by %d feet %d inches,\n",
	  feetLength, inchesLength, feetWidth, inchesWidth);
  printf ("  you will need %.1f square yards of carpet.\n",
	  findArea(feetLength, inchesLength, feetWidth, inchesWidth));

  return EXIT_SUCCESS;
}

/************************************************************/

float
convertFeetAndInchesToYards (int feet, int inches)
{
  return (feet + (inches / 12.0)) / 3.0;
}

/************************************************************/

float
findArea(int feetLength, int inchesLength, int feetWidth, int inchesWidth)
{
  return convertFeetAndInchesToYards (feetLength, inchesLength)
    * convertFeetAndInchesToYards (feetWidth, inchesWidth);
}

/************************************************************/
