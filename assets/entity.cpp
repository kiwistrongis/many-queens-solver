//library includes
#include <cassert>
#include <cstdio>
#include <cstdlib>
//override include
#include "entity.h"

// Constructor and Destructor
Entity::Entity( int problem_size){
	this->problem_size = problem_size;
	//encode a randomly generated permutation
	int* permutation = this->randomPermutation();
	this->newRandomPermutation();}

Entity::Entity( const Entity& other){
	*this = other;}

Entity::~Entity(){
	chromosome.clear();}

// Operators
Entity& Entity::operator=( const Entity& other){
	//check for self assignment
	if( this == &other)
		return *this;
	//shallow fields
	if( !other.problem_size){
		printf("error!\n");
		exit(1);}
	problem_size = other.problem_size;
	//deep fields
	int* other_permutation = other.extract_permutation();
	this->encode_permutation( other_permutation);
	delete[] other_permutation;
	//done
	return *this;}

bool Entity::operator==( const Entity& other) const{
	//compare problem sizes
	if( this->problem_size != other.problem_size)
		return false;
	//get the permutations
	int* permutation = this->extract_permutation();
	int* other_permutation = other.extract_permutation();
	//compare the permutations
	for( int i = 0; i < problem_size; i++)
		if( permutation[i] != other_permutation[i]){
			delete[] permutation;
			delete[] other_permutation;
			return false;}
	//done
	delete[] permutation;
	delete[] other_permutation;
	return true;}

bool Entity::operator!=( const Entity& other) const{
	return !(*this==other);}

// Encoding and Decoding
void Entity::encode_permutation( int* permutation){
	//remove previous chromosome
	chromosome.clear();
	//encode new chromosome
	for( int i = 0; i < problem_size - 1; i++){
		//determine how many bits we need
		int nbits = bitsNeeded( problem_size - i - 1);
		//append the integer (as a bit string) to the chromosome
		for(int j = nbits - 1; j >= 0; j--)
			chromosome.push_back( (permutation[i] >> j)%2);}}

int* Entity::extract_permutation( int* dest) const{
	//setup
	if( dest==NULL) //remember to delete later!!
		dest = new int[ problem_size];
	int chromosome_i = 0;
	if( debug_entity) printf("permut: ( ");
	//reconstruct the permutation and write it into 'dest'
	for( int i = 0; i < problem_size - 1; i++){
		//determine how many bits we need
		int max = problem_size - i - 1;
		int nbits = bitsNeeded( max);
		//decode the step in the permutation
		int permutation_currentStep = 0;
		for(int j = nbits - 1; j >= 0; j--)
			permutation_currentStep += chromosome[ chromosome_i++] << j;
		if( debug_entity) printf( "%d, ", permutation_currentStep);
		//write the decoded value to dest
		dest[i] = permutation_currentStep;}
	//add the last item
	dest[ problem_size - 1] = 0;
	if( debug_entity) printf( "%d)\n", dest[ problem_size - 1]);
	//done
	return dest;}

int* Entity::extract_grid( int* dest) const{
	//ensure dest exists
	if( dest==NULL) //remember to delete later!!
		dest = new int[ problem_size];
	//get the permutation
	int* permutation = this->extract_permutation();
	//convert the permutation into a grid
	permutation_toGrid( permutation, dest);
	//done
	delete[] permutation;
	return dest;}

// Encoding and Decoding Minor
int* Entity::permutation_toGrid( int* permutation, int* dest) const{
	//setup
	// permutation_vector represents the initial set we select a permutation from
	std::vector<int> permutation_vector;
	for( int i = 0; i < problem_size; i++)
		permutation_vector.push_back(i);
	//remove elements from permutation_vector and push them into grid
	if( debug_entity) printf("grid: ( ");
	for( int i = 0; i < problem_size; i++){
		//copy the ith element as indicated by permutation[i]
		dest[i] = permutation_vector[ permutation[i]];
		if( debug_entity) printf("%d, ", dest[i]);
		//remove the ith element from permutation_vector
		permutation_vector.erase(
			permutation_vector.begin() + permutation[i]);}
	if( debug_entity) printf(")\n");
	//done
	return dest;}

int Entity::bitsNeeded( int data) const{
	int result = 1;
	while( data>>=1) result++;
	return result;}

// Evaluation and Evolution
int Entity::fitness() const{
	//setup
	int result = 0;
	int* grid = this->extract_grid();
	//for each row a
	for(int i = 0; i < problem_size; i++){
		if( debug_entity) printf("%d, [",i);
		//check each row b below it
		for(int j = i + 1; j < problem_size; j++){
			int dist = j - i;
			if( debug_entity) printf(" %d-%d,", grid[i], grid[j]);
			//add one if the queens intersect diagonally
			result +=
				grid[i] - dist == grid[j] ||
				grid[i] + dist == grid[j];}
		if( debug_entity) printf("]\n");}
	//done
	delete[] grid;
	return result;}

Entity& Entity::mutate(){
	//select a bit
	int loc = rand() % chromosome.size();
	//flip the bit
	chromosome[ loc] ^=1;
	//repair the possible broken chromosome
	this->fix();
	//done
	return *this;}

Entity& Entity::cross( const Entity& other){
	//ensure we can cross with other safely
	if( problem_size != other.problem_size)
		return *this;
	//for each bit after some random n
	for( int i = rand() % chromosome.size(); i < chromosome.size(); i++)
		//copy the ith bit from the other
		chromosome[i] = other.chromosome[i];
	//repair the possibly broken chromosome
	this->fix();
	//done
	return *this;}

Entity& Entity::newRandomPermutation(){
	//create a random permutation and encode it
	int* permutation = this->randomPermutation();
	this->encode_permutation( permutation);
	//done
	delete[] permutation;
	return *this;}

// Evaluation and Evolution Minor
int* Entity::randomPermutation( int* dest) const{
	if( dest == NULL)
		dest = new int[problem_size];
	//generate the permutation
	for( int i = 0; i < problem_size-1; i++){
		int max = problem_size - i - 1;
		dest[i] = rand() % ( max + 1);}
	dest[problem_size - 1] = 0;
	return dest;}

// Display
void Entity::draw_grid() const{
	int* grid = this->extract_grid();
	for(int i = 0; i < problem_size; i++){
		printf("[%c", (0 == grid[i]) ?
				'Q' : '_');
		for( int j = 1; j < problem_size; j++)
			printf("|%c", (j == grid[i]) ?
				'Q' : '_');
		printf("]\n");}
	delete[] grid;}

void Entity::print_permutation() const{
	int* permutation = this->extract_permutation();
	printf("permutation: %d", permutation[0]);
	for( int i = 1; i < problem_size; i++)
		printf(", %d", permutation[i]);
	printf("\n");
	delete[] permutation;}

void Entity::print_grid() const{
	int* grid = this->extract_grid();
	printf("grid: %d", grid[0]);
	for( int i = 1; i < problem_size; i++)
		printf(", %d", grid[i]);
	printf("\n");
	delete[] grid;}

// Maintainance
bool Entity::isValid() const{
	int* permutation = this->extract_permutation();
	for( int i = 0; i < problem_size; i++)
		if( permutation[i] > problem_size - 1 - i)
			return false;
	return true;}

void Entity::fix(){
	int* permutation = this->extract_permutation();
	for( int i = 0; i < problem_size; i++){
		int max = problem_size - i - 1;
		if( permutation[i] > max)
			permutation[i] = rand() % max;}
	this->encode_permutation( permutation);
	delete[] permutation;}