#ifndef assets_entity_h
#define assets_entity_h

//library includes
#include <cstddef>
#include <vector>
//local includes
#include "debug.h"

/** @class Entity
 * @brief Represents a candidate solution to the N-Queens problem
 * 
 * The class implements all of the following functionality:
 * - encoding and decoding of the chromosome
 * - evaluation of the fitness function
 * - multiple mutation and crossover evolutionary operators
 * 
 * The following mutation operators are implemented:
 * - Flip a random bit
 * 
 * The following crossover operators are implemented.
 * - Copy bits after some random n
 **/
class Entity {
public:
	//Fields
	int problem_size;
	std::vector<int> chromosome;

	//Constructors and Destructor
	Entity( int problem_size);
	Entity( const Entity& other);
	~Entity();

	//Operators
	Entity& operator=( const Entity& other);
	bool operator==( const Entity& other) const;
	bool operator!=( const Entity& other) const;
	
	//Encoding and Decoding
	void encode_permutation( int* permutation);
	int* extract_permutation( int* dest = NULL) const;
	int* extract_grid( int* dest = NULL) const;
	//Encoding and Decoding Minor
	int* permutation_toGrid( int* permutation, int* dest) const;
	int bitsNeeded( int data) const;

	//Evaluation and Evolution
	int fitness();
	Entity& mutate();
	Entity& cross( const Entity& other);
	Entity& newRandomPermutation();
	//Evaluation and Evolution Minor
	int* randomPermutation( int* dest = NULL);

	//Display
	void draw_grid() const;
	void print_permutation() const;
	void print_grid() const;

	//Maintainance
	void fix();
	bool isValid() const;
private:
};

#endif