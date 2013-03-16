//library includes
#include <cstdio>
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
	Population p( conf);
	Reporter r( conf);
	if( debug_messages) printf("Done loading configuration\n");

	int G = conf.nGenerations;
	int P = 10; //conf.report_period;

	if( debug_messages) printf("Starting evolution\n");
	clock_t start = clock();
	for( int i = 0; i < G; i++){
		if( !(i % P) ){
			if( debug_messages)
				printf("Generation %d/%d\r", i, G);
			r.capture( p, i);}
		p.evolve();}
	float t = (float) (clock() - start) / ( CLOCKS_PER_SEC);
	if( debug_messages) printf("Generation %d/%d\n", G, G);

	printf("Time taken: %f\n", t);

	return 0;}