//libarary includes
#include <fstream>
//override include
#include "reporter.h"

Reporter::Reporter( const Configuration& conf){
	datafile.open( conf.datafile, std::ofstream::trunc);}

Reporter::~Reporter(){
	datafile.close();}

void Reporter::capture( Population population, int i){}