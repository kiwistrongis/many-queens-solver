#ifndef assets_reporter_h
#define assets_reporter_h

//library includes
#include <fstream>
//local includes
#include "configuration.h"
#include "population.h"

class Reporter {
public:
	//Fields
	std::ofstream datafile;

	//Constructor and Destructor
	Reporter( const Configuration& conf);
	~Reporter();

	//Functions
	void capture( Population population, int i);
};

#endif