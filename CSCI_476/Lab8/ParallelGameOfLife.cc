/*
	FileName		: ParallelGameOfLife.cc
	Author		: Zachary Zuch
	Course		: CSCI 476
	Assignment 	: Lab 8
	Description	: Parallel Game of Life Simulation
*/

/************************************************************/
// System includes

#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <thread>
#include <string>

#include <boost/thread/barrier.hpp>

/************************************************************/
// Local includes

#include "Timer.hpp"

/************************************************************/
// Using declarations

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::minstd_rand;

using boost::dynamic_bitset;

/************************************************************/
// Function prototypes/global vars/typedefs



/************************************************************/

int
main(int argc, char* argv[])
{
	cout << "Input file  ==> ";
	string file;
	cin >> file;

	if ( file == "n" )
	{
		cout << endl << "N           ==> ";
		unsigned N;
		cin >> N;

		cout << "Seed        ==> ";
		unsigned seed;
		cin >> p;
	}
	else
	{
		// Read from file and create bitset matrix
	}

	cout << "p           ==> ";
	unsigned p;
	cin >> p;

	cout << "Generations ==> ";
	unsigned generations;
	cin >> generations;
	cout << endl;
}

void
generations_helper ( vector< vector<bool> >& life_matrix, unsigned begin_pos,
		unsigned end_pos, unsigned generations, barrier& b )
{
	unsigned n = life_matrix.size() - 2;
	unsigned begin_i = ( begin_pos / n ) + 1;
	unsigned begin_j = ( begin_pos % n ) + 1;
	unsigned end_i = ( end_pos / n ) + 1;
	unsigned end_j = ( end_pos % n ) + 1;
	unsigned next_gen_pos = 0;
	vector<bool> next_gen( end_pos - begin_pos );
	for ( unsigned curr_gen = 0; curr_gen < generations; ++curr_gen )
	{
		for ( unsigned i = begin_i; i <= end_i; ++i )
		{
			unsigned end_value = ( i == end_i ? end_j : n ); 
			for ( unsigned j = ( i == begin_i ? begin_j : 1 );
				j <= end_value; ++j )
			{
				// Reads from curr life matrix 
				next_gen[ pos ] = check_if_alive( ... );
				++pos;
			}
		}

		b.wait(); // caller creates
		
		// write buffer to curr life
		next_gen_pos = 0;
		for ( unsigned i = begin_i; i <= end_i; ++i )
		{
			unsigned end_value = ( i == end_i ? end_j : n ); 
			for ( unsigned j = ( i == begin_i ? begin_j : 1 );
				j <= end_value; ++j )
			{
				life_matrix[ i ][ j ] = next_gen[ pos ];
				++pos;
			}
		}
	}
}