#ifndef assets_population_h
#define assets_population_h

//library includes
#include <vector>
//local includes
#include "configuration.h"
#include "entity.h"

/** @class Population
 * @brief Represents a group of entities
 * 
 * The class contains multiple entities, and through evolving the group using some specific mutation and crossover operators
 **/
class Population{
public:
	//Fields
	std::vector<Entity> entities;
	std::vector<Entity> solutions;
	int N;
	int problem_size;
	double mutation_chance;
	double cross_chance;
	bool removeTheStrong;

	//Constructors and Destructor
	Population( const Population&);
	Population( const Configuration& conf = Configuration());
	~Population();

	//Operators
	Population& operator=( const Population&);

	//Evolution Functions
	void evolve();
	void mutate_each();
	void cross_each();
	//Minor Evolution Functions
	void save( Entity entity);
	void saveTheStrong();
	void cullTheWeak( double average, double standardDeviation);
	void cullTheVeryWeak( double average, double standardDeviation);
	void rouletteSelect();

	//Statistics Functions
	int* getStats() const;
	double getAverage( int* stats) const;
	int worstPossibleFitness() const;
	double getStandardDeviation( double average, int* stats) const;

	//Results
	void removeDuplicateSolutions();
	void print_solutions() const;

	//Display
	void print_stats() const;
private:
};

#endif