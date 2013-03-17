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
	solutionsfile_path = new char[128];
	strcpy( solutionsfile_path, conf.solutionsfile);
	plotfile_base = new char[128];
	strcpy( plotfile_base, conf.plotfile_base);
	plotscript_logfile = new char[128];
	strcpy( plotscript_logfile, conf.plotscript_logfile);}

Reporter::~Reporter(){
	datafile.close();
	//call the script to dray the plot
	char* buffer = new char[256];
	sprintf( buffer, "scripts/makeplot.m %s %s &> %s",
		datafile_path, plotfile_base, plotscript_logfile);
	if( debug_reporter) printf("running: '%s'\n", buffer);
	system( buffer);
	//clean up
	delete[] buffer;
	delete[] datafile_path;
	delete[] solutionsfile_path;
	delete[] plotfile_base;
	delete[] plotscript_logfile;}

void Reporter::capture( Population& population,
		const int& i){
	//assure we can read
	if( ! datafile.good()){
		fail = true;
		return;}
	//setup
	int* stats = population.getStats();
	int stats_size = 1 + population.worstPossibleFitness();
	population.removeDuplicateSolutions();
	int nSols = population.solutions.size();
	char* buffer = new char[50];
	//write the first part
	sprintf( buffer, "%d, %d, %d", i, nSols, stats[0]);
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

void Reporter::writeSolutions( Population& population){
	//setup
	population.removeDuplicateSolutions();
	int* grid;
	int n_solutions = population.solutions.size();
	std::ofstream out(solutionsfile_path);
	char* buffer = new char[50];
	//write
	for( int i = 0; i < n_solutions; i++){
		grid = population.solutions[i].extract_grid();
		sprintf( buffer, "( %d", grid[0]);
		out<<buffer;
		for( int j = 1; j < population.problem_size; j++){
			sprintf( buffer, ", %d", grid[j]);
			out<<buffer;}
		sprintf( buffer, " )\n");
		out<<buffer;
		delete[] grid;}
	delete[] buffer;
	out.close();}