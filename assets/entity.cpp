#include "entity.h"

// Constructor
Entity::Entity( int problem_size){
	this-> problem_size = problem_size;
		//encode the generated step in the permuation
	int* permutation = this->randomPermutation();
	this->newRandomPermutation();}

// Encoding and Decoding
void Entity::encode_permutation( int* permutation){
	while( chromosome.size())
		chromosome.pop_back();
	for( int i = 0; i < problem_size - 1; i++){
		int nbits = bitsNeeded( problem_size - i - 1);
		for(int j = nbits - 1; j >= 0; j--)
			chromosome.push_back( (permutation[i] >> j)%2);}}
int* Entity::extract_permutation( int* dest){
	if( dest==NULL) //remember to delete later!!
		dest = new int[ problem_size];
	int chromosome_i = 0;
	//if( debug_entity) printf("max   : ( 7, 6, 5, 4, 3, 2, 1, 0)\n");
	if( debug_entity) printf("permut: ( ");
	//reconstruct the permutation and write it into 'dest'
	for( int i = 0; i < problem_size - 1; i++){
		int max = problem_size - i - 1;
		int nbits = bitsNeeded( max);
		//decode the step in the permuation
		int permutation_currentStep = 0;
		for(int j = nbits - 1; j >= 0; j--)
			permutation_currentStep += chromosome[ chromosome_i++] << j;
		if( debug_entity) printf( "%d, ", permutation_currentStep);
		//write the decoded value to dest
		dest[i] = permutation_currentStep;}
	//add the last item
	dest[ problem_size - 1] = 0;
	if( debug_entity) printf( "%d)\n", dest[ problem_size - 1]);
	return dest;}

int* Entity::extract_grid( int* dest){
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
	int loc = rand() % chromosome.size();
	chromosome[ loc] ^=1;
	if( ! this->isValid())
		this->newRandomPermutation();
	return *this;}

Entity& Entity::cross( const Entity& other){
	assert( problem_size == other.problem_size);
	for( int i = rand() % chromosome.size(); i < chromosome.size(); i++)
		chromosome[i] = other.chromosome[i];
	if( ! this->isValid())
		this->newRandomPermutation();
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
void Entity::newRandomPermutation(){
		int* permutation = this->randomPermutation();
		this->encode_permutation( permutation);
		delete permutation;}
int* Entity::randomPermutation( int* dest){
	if( dest == NULL)
		dest = new int[problem_size];
	//generate the permutation
	for( int i = 0; i < problem_size-1; i++){
		int max = problem_size - i - 1;
		dest[i] = rand() % ( max + 1);}
	dest[problem_size - 1] = 0;
	return dest;}
bool Entity::isValid(){
	int* permutation = this->extract_permutation();
	for( int i = 0; i < problem_size; i++)
		if( permutation[i] > problem_size - 1 - i)
			return false;
	return true;}