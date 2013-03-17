//library includes
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
//local includes
#include "queens-lib.h"

char configurationFile_default[] = "default.ini";

int main( int argc, char** argv){
	char* configurationFile = new char[256];
	if( argc > 1)
		strcpy( configurationFile, argv[1]);
	else
		strcpy( configurationFile, configurationFile_default);
	if( debug_messages)
		printf("Loading configuration from '%s'\n",
			configurationFile);

	Configuration conf ( configurationFile);
	delete[] configurationFile;
	srand( time( NULL));
	Population p( conf);
	Reporter r( conf);
	if( debug_messages) printf("Done loading configuration\n");

	int G = conf.nGenerations;
	int P = conf.report_period;

	if( debug_messages) printf("Starting evolution\n");
	clock_t start = clock();
	for( int i = 0; i < G; i++){
		if( (i % P) == 0 ){
			if( debug_progress) printf("Generation %d/%d\r", i, G);
			r.capture( p, i);
			//handle failure
			if( r.fail){
				printf("Data write failure occured. Terminating.\n");
				break;}}
		p.evolve();}
	float t = (float) (clock() - start) / ( CLOCKS_PER_SEC);
	r.capture( p, G); //final capture
	if( debug_progress) printf("Generation %d/%d\n", G, G);

	printf("Time taken: %f\n", t);
	printf("Found %d solutions\n", p.solutions.size());
	r.writeSolutions(p);

	return 0;}