//libarary includes
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
//override include
#include "reporter.h"

Reporter::Reporter( const Configuration& conf){
	datafile.open( conf.datafile, std::ofstream::trunc);
	fail = ! datafile.good();
	datafile_path = new char[128];
	strcpy( datafile_path, conf.datafile);
	chartfile = new char[128];
	strcpy( chartfile, conf.chartfile);
	plotscript_logfile = new char[128];
	strcpy( plotscript_logfile, conf.plotscript_logfile);}

Reporter::~Reporter(){
	datafile.close();
	//call the script to dray the plot
	char* buffer = new char[256];
	sprintf( buffer, "scripts/makeplot.m %s %s &> %s",
		datafile_path, chartfile, plotscript_logfile);
	if( debug_reporter) printf("running: '%s'\n", buffer);
	system( buffer);
	//clean up
	delete[] buffer;
	delete[] datafile_path;
	delete[] chartfile;
	delete[] plotscript_logfile;}

void Reporter::capture( const Population& population,
		const int& i){
	//assure we can read
	if( ! datafile.good()){
		fail = true;
		return;}
	//setup
	int* stats = population.getStats();
	int stats_size = 1 + population.worstPossibleFitness();
	char* buffer = new char[50];
	//write the first part
	sprintf( buffer, "%d, %d", i, stats[0]);
	datafile << buffer;
	//write the rest
	for( int i = 1; i < stats_size; i++){
		sprintf( buffer, ", %d", stats[i]);
		datafile << buffer;}
	//done, clean up
	datafile << std::endl;
	datafile.flush();
	delete[] stats;
	delete[] buffer;}