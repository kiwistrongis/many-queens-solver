#ifndef assets_configuration_h
#define assets_configuration_h

//library includes
#include <cstddef>
#include <vector>
//local includes

/** @class Configuration
 * @brief Represents the initial configuration of a population
 * 
 * Configuration objects handle the loading of population parameters from files. This makes initialization easier for the population class.
 **/
class Configuration {
public:
	//Population Config Fields
	int problem_size;
	int N;
	double mutation_chance;
	double cross_chance;
	bool removeTheStrong;

	//Run Config Fields
	int nGenerations;

	//Report Config Fields
	char* datafile;
	char* chartfile;
	char* plotscript_logfile;
	int report_period;

	//Constructor
	Configuration( char* filename = NULL);
	~Configuration();
private:
};

#endif