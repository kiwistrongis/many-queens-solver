//library includes
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
//local includes
#include "globals.h"
#include "configuration.h"
//override include
#include "population.h"

// Constructors and Destructor
Population::Population( const Population& other){
	*this = other;}

Population::Population( const Configuration& conf){
	//fields
	problem_size = conf.problem_size;
	N = conf.N;
	mutation_chance = conf.mutation_chance;
	cross_chance = conf.cross_chance;
	removeTheStrong = conf.removeTheStrong;

	//create all the entities
	Entity* newEntity;
	while( entities.size() < N)
		entities.push_back( Entity( problem_size));}

Population::~Population(){
	entities.clear();
	solutions.clear();}

// Operators
Population& Population::operator=( const Population& other){
	if( this == &other)
		return *this;
	//shallow fields
	N = other.N;
	problem_size = other.problem_size;
	mutation_chance = other.mutation_chance;
	cross_chance = other.cross_chance;
	//deep fields
	entities.clear();
	solutions.clear();
	for( int i = 0; i < N; i++)
		entities.push_back( other.entities[i]);
	for( int i = 0; i < other.solutions.size(); i++)
		solutions.push_back( other.solutions[i]);
	return *this;}

// Evolution
void Population::evolve(){
	int* stats = getStats();
	double average = getAverage( stats);
	double standardDeviation =
		getStandardDeviation( average, stats);
	delete[] stats;
	saveTheStrong();
	cullTheWeak( average, standardDeviation);
	mutate_each();
	cross_each();}
	
void Population::mutate_each(){
	for( int i = 0; i < N; i++)
		if( randDouble() < mutation_chance)
			entities[i].mutate();}
		
void Population::cross_each(){
	for( int i = 0; i < N; i++)
		if( randDouble() < cross_chance)
			entities[i].cross( entities[ rand() % N]);}

// Evolution Minor
void Population::save( Entity entity){
	if( debug_showSolsWhenFound){
		printf("Found Sol:");
		entity.print_grid();}
	solutions.push_back( entity);}

void Population::saveTheStrong(){
	for( int i = 0; i < N; i++)
		if( entities[i].fitness() == 0){
			save( entities[i]);
			if( removeTheStrong)
				entities[i].newRandomPermutation();}}

void Population::cullTheWeak( double average, double standardDeviation){
	for( int i = 0; i < N; i++)
		if( entities[i].fitness() - average > 0)
			entities[i].newRandomPermutation();}

void Population::cullTheVeryWeak( double average, double standardDeviation){
	for( int i = 0; i < N; i++)
		if( entities[i].fitness() - average > standardDeviation)
			entities[i].newRandomPermutation();}

void Population::rouletteSelect(){
	double* chances = new double[N];
	delete[] chances;}

// Statistics
int* Population::getStats() const{
	int worstFitness = worstPossibleFitness();
	int* count = new int[worstFitness + 1];
	for( int i = 0; i <= worstFitness; i++)
		count[i] = 0;
	for( int i = 0; i < N; i++)
		count[ entities[i].fitness()]++;
	return count;}

int Population::worstPossibleFitness() const{
	return (problem_size - 1)*(problem_size)/2;}

double Population::getAverage( int* stats) const{
	int worstFitness = worstPossibleFitness();
	double average = 0.0;
	for( int i = 0; i <= worstFitness; i++)
		average += (double) i*stats[i] / N;
	return average;}

double Population::getStandardDeviation( double average, int* stats) const{
	int worstFitness = worstPossibleFitness();
	double standardDeviation = 0.0;
	for( int i = 0; i <= worstFitness; i++)
		standardDeviation +=
			pow( i - average, 2.0) * ( (double) stats[i] / N);
	return sqrt( standardDeviation);}

// Results
void Population::removeDuplicateSolutions(){
	for( int i = 0; i < solutions.size(); i++)
		for( int j = 0; j < i; j++)
			if( solutions[i] == solutions[j]){
				solutions.erase( solutions.begin()+j);
				i--;
				break;}}

void Population::print_solutions() const{
	int solutions_size = solutions.size();
	for( int i = 0; i < solutions_size; i++)
		solutions[i].print_grid();}

// Display
void Population::print_stats() const{
	//get the stats
	int* stats = getStats();
	double average = getAverage( stats);
	double stddev = getStandardDeviation( average, stats);
	int worstFitness = worstPossibleFitness();
	//print the stats
	printf("Average: %f\n", average);
	printf("StdDev : %f\n", stddev);
	//labels
	printf("%2d", 0);
	for( int i = 1; i <= worstFitness; i++)
		printf("|%2d", i);
	printf("\n");
	//values
	printf("%2d", stats[0]);
	for( int i = 1; i <= worstFitness; i++)
		printf("|%2d", stats[i]);
	printf("\n");
	//clean up
	delete[] stats;}