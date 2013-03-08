#include "entity.h"

// Constructor
Entity::Entity( int problem_size){
	this-> problem_size = problem_size;
	int* permutation;
	permutation = new int[ problem_size];
	//generate the permutation and write it into the bitstring
	for( int i = 0; i < problem_size; i++){
		int max = problem_size - i - 1;
		permutation[i] = rand() % ( max + 1);
		//encode the generated step in the permuation
		int nbits = bitsNeeded( max);
		if( debug_entity) printf("max: %d, bitsN: %d, value: %d, string: ", max, nbits, permutation[i]);
		for(int j = nbits - 1; j >= 0; j--){
			chromosome.push_back( (permutation[i] >> j)%2);
			if( debug_entity) printf("%d", (permutation[i] >> j)%2);}
		if( debug_entity) printf("\n");}}

// Encoding and Decoding
int* Entity::extract_permutation( int* dest){
	if( dest==NULL) //remember to delete later!!
		dest = new int[ problem_size];
	int chromosome_i = 0;
	if( debug_entity) printf("permutation: ( ");
	//reconstruct the permutation and write it into 'dest'
	for( int i = 0; i < problem_size; i++){
		int max = problem_size - i - 1;
		int permutation_currentStep = 0;
		//decode the step in the permuation
		int nbits = bitsNeeded( max);
		for(int j = nbits - 1; j >= 0; j--)
			permutation_currentStep += chromosome[ chromosome_i++] << j;
		if( debug_entity) printf( "%d, ",permutation_currentStep);
		dest[i] = permutation_currentStep;}
	if( debug_entity) printf(")\n");
	return dest;}

int* Entity::extract_grid( int* dest ){
	if( dest==NULL) //remember to delete later!!
		dest = new int[ problem_size];
	int* permutation = this->extract_permutation();
	permutation_toGrid( permutation, dest);
	delete permutation;
	return dest;}

int Entity::bitsNeeded( int data){
	int result = 1;
	while( data>>=1)
		result++;
	return result;}

int* Entity::permutation_toGrid( int* permutation, int* dest){
	std::vector<int> permutation_vector;
	for( int i = 0; i < problem_size; i++)
		permutation_vector.push_back(i);
	if( debug_entity) printf("grid: ( ");
	for( int i = 0; i < problem_size; i++){
		dest[i] = permutation_vector[ permutation[i]];
		if( debug_entity) printf("%d, ", dest[i]);
		permutation_vector.erase(
			permutation_vector.begin() + permutation[i]);}
	if( debug_entity) printf(")\n");
	return dest;}

// Evaluation and Evolution
int Entity::fitness(){
	int result = 0;
	int* grid = this->extract_grid();
	for(int i = 0; i < problem_size; i++){
		if( debug_entity) printf("%d, [",i);
		for(int j = i + 1; j < problem_size; j++){
			int dist = j - i;
			if( debug_entity) printf(" %d-%d,", grid[i], grid[j]);
			result +=
				grid[i] - dist == grid[j] ||
				grid[i] + dist == grid[j];}
		if( debug_entity) printf("]\n");}
	delete grid;
	return result;}

Entity& Entity::mutate(){
	chromosome[ rand() % chromosome.size()].flip();
	return *this;}

Entity& Entity::cross( const Entity& other){
	assert( problem_size == other.problem_size);
	for( int i = rand() % chromosome.size(); i < chromosome.size(); i++)
		if( chromosome[i] != other.chromosome[i])
			chromosome[i].flip();//chromosome[i] = other.chromosome[i] not working
	return *this;}

// Debugging
void Entity::draw_grid(){
	int* grid = this->extract_grid();
	for(int i = 0; i < problem_size; i++){
		printf("[%c", (0 == grid[i]) ?
				'Q' : '_');
		for( int j = 1; j < problem_size; j++)
			printf("|%c", (j == grid[i]) ?
				'Q' : '_');
		printf("]\n");}
	delete grid;}