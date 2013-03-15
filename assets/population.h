#ifndef assets_population_h
#define assets_population_h

//library includes
#include <vector>
//local includes
#include "entity.h"

/** @class Population
 * @brief This class represents a group of entities.
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
	Population( int n, int p_size);
	Population( int n, int p_size, double m_chance, double c_chance);
	Population( const Population&);
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
	void rouletteSelect();

	//Statistics Functions
	int* getStats();
	double getAverage( int* stats = NULL);
	double getStandardDeviation( double average);
private:
};

#endif