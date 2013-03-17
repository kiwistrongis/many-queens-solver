#ifndef assets_reporter_h
#define assets_reporter_h

//library includes
#include <fstream>
//local includes
#include "configuration.h"
#include "population.h"

/** @class Reporter
 * @brief Handles the storage of relevant data
 * 
 * This class opens the file indicated by the configuration object passed to it
 **/
class Reporter {
public:
	//Fields
	std::ofstream datafile;
	bool fail;
	char* datafile_path;
	char* solutionsfile_path;
	char* plotfile_base;
	char* plotscript_logfile;

	//Constructor and Destructor
	Reporter( const Configuration& conf);
	~Reporter();

	//Functions
	void capture( Population& population, const int& i);
	void writeSolutions( Population& population);
};

#endif