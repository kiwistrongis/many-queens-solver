#ifndef entity_h
#define entity_h

//library includes
#include <cstddef>
#include <vector>
//local includes
#include "debug.h"

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
	std::vector<int> chromosome;
	
	Entity( int problem_size);
	Entity( const Entity& other);
	~Entity();

	Entity& operator=( const Entity& other);
	
	void encode_permutation( int* permutation);
	int* extract_permutation( int* dest = NULL);
	int* extract_grid( int* dest = NULL);
	void draw_grid();
	void print_permutation();
	void print_grid();

	int fitness();
	Entity& mutate();
	Entity& cross( const Entity& other);
	Entity& newRandomPermutation();
private:
	bool isValid();
	void fix();
	int bitsNeeded( int chromosome);
	int* permutation_toGrid( int* permutation, int* dest);
	int* randomPermutation( int* dest = NULL);
};

#endif