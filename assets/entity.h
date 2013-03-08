#ifndef entity_h
#define entity_h

#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "../debug.h"

/** @class Entity
 * @brief This class represents a candidate solution to the N-Queens problem.
 * 
 * The class implements all of the following functionality:
 * - encoding and decoding of the chromosome
 * - evaluation of the fitness function
 * - multiple mutation and crossover evolutionary operators
 * 
 * The following mutation operators are implemented:
 * 
 * The following crossover operators are implemented.
 **/
class Entity {
public:
	int problem_size;
	std::vector<bool> chromosome;
	
	Entity( int problem_size);
	
	int* extract_permutation( int* dest = NULL);
	int* extract_grid( int* dest = NULL);
	void draw_grid();

	int fitness();
	Entity& mutate();
	Entity& cross( const Entity& other);
private:
	int bitsNeeded( int chromosome);
	int* permutation_toGrid( int* permutation, int* dest);
};

#endif