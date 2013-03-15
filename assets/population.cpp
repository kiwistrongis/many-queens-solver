//library includes
#include <cmath>
#include <cstdio>
#include <cstdlib>
//local includes
#include "globals.h"
//override include
#include "population.h"

// Constructors and Destructor
Population::Population( int n, int p_size){
	N = n;
	problem_size = p_size;
	mutation_chance = 0.1;//randDouble();
	cross_chance = 0.7;//randDouble();
	removeTheStrong = true;

	Entity* newEntity;
	while( entities.size() < N){
		newEntity = new Entity( p_size);
		entities.push_back( *newEntity);
		delete newEntity;}}

Population::Population( int n, int p_size, double m_chance, double c_chance){
	N = n;
	mutation_chance = m_chance;
	cross_chance = c_chance;
	removeTheStrong = true;

	Entity* newEntity;
	while( entities.size() < N){
		newEntity = new Entity( p_size);
		entities.push_back( *newEntity);
		delete newEntity;}}

Population::Population( const Population& other){
	*this = other;}

Population::~Population(){
	while( entities.size())
		entities.erase( entities.begin());
	while( solutions.size())
		solutions.erase( solutions.begin());}

// Operators
Population& Population::operator=( const Population& other){
	//shallow fields
	N = other.N;
	problem_size = other.problem_size;
	mutation_chance = other.mutation_chance;
	cross_chance = other.cross_chance;
	//deep fields
	while( entities.size())
		entities.erase( entities.begin());
	for( int i = 0; i < N; i++)
		entities.push_back( other.entities[i]);
	while( solutions.size())
		solutions.erase( solutions.begin());
	for( int i = 0; i < other.solutions.size(); i++)
		solutions.push_back( other.solutions[i]);}

// Evolution
void Population::evolve(){
	int* stats = getStats();
	double average = getAverage( stats);
	double standardDeviation = getStandardDeviation( average);
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
	printf("Found Solution:\n");
	entity.draw_grid();
	solutions.push_back( entity);}

void Population::saveTheStrong(){
	for( int i = 0; i < N; i++)
		if( entities[i].fitness() == 0){
			save( entities[i]);
			if( removeTheStrong)
				entities[i].newRandomPermutation();}}

void Population::cullTheWeak( double average, double standardDeviation){
	for( int i = 0; i < N; i++)
		if( entities[i].fitness() - average > standardDeviation)
			entities[i].newRandomPermutation();}

void Population::rouletteSelect(){
	double* chances = new double[N];
	delete[] chances;}

// Statistics
int* Population::getStats(){
	int worstFitness = (problem_size + 1)*(problem_size)/2;
	int* count = new int[worstFitness + 1];
	for( int i = 0; i < N; i++)
		count[ entities[i].fitness()]++;
	return count;}
double Population::getAverage( int* stats){
	bool statsWasNULL = ( NULL == stats );
	if( statsWasNULL)
		int* stats = getStats();
	int worstFitness = (problem_size + 1)*(problem_size)/2;
	double average = 0.0;
	for( int i = 1; i <= worstFitness; i++)
		average += (double)i/N;
	if( statsWasNULL)
		delete stats;
	return average;}
double Population::getStandardDeviation( double average){
	double standardDeviation = 0.0;
	for( int i = 0; i < N; i++)
		standardDeviation += pow( entities[i].fitness() - average, 2.0);
	return sqrt( standardDeviation);}
