/*
	FileName		: ReductionsOMP.cc
	Author		: Zachary Zuch
	Course		: CSCI 476
	Assignment 	: Lab 12
	Description	: OpenMP reduction example
*/

/************************************************************/
// System includes

#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

#include <omp.h>

/************************************************************/
// Local includes

#include "Timer.hpp"						

/************************************************************/
// Using declarations

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::uniform_int_distribution;
using std::random_device;
using std::mt19937;
using std::generate_n;

/************************************************************/
// Function prototypes

vector<int> 
createVector( int p );

int 
sum_vector_omp( vector<int> &vec );

/************************************************************/

int
main(int argc, char* argv[])
{
	cout << "N ==> ";
	int N;
	cin >> N;
	cout << endl;

	vector<int> randVector = createVector( N );
	Timer< > t;
	int sum = sum_vector_omp ( randVector );
	t.stop();
	double time = t.getElapsedMs();
	cout << endl << "Sum:  " << sum << endl;
	cout << "Time: " << time << endl << endl;

	return EXIT_SUCCESS;
}

/************************************************************/

vector<int> 
createVector( int N )
{
	vector<int> vec( N );
  	random_device rd;
    	mt19937 gen( rd( ) );
    	gen.seed( 0 );
  	uniform_int_distribution<int> dist( 0, 4 );

  	generate_n (vec.begin (), N, [&gen, &dist] () { return dist (gen); });

	return vec;
}

/************************************************************/

int 
sum_vector_omp( vector<int> &vec )
{
	int sum = 0;

	#pragma omp parallel for reduction( +: sum )
	#pragma SIMD
	for ( unsigned i = 0; i < vec.size(); ++i )
	{
		sum += vec[ i ];
	}

	return sum;
}

/************************************************************/
