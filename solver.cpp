//library includes
#include <cstdio>
#include <cstring>
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
	if( debug_messages) printf("Loading configuration from %s\n",
		configurationFile);
	Configuration conf ( configurationFile);
	Population p( conf);
	if( debug_messages) printf("Done loading configuration\n");

	clock_t start = clock();
	for( int i = 0; i < conf.nGenerations; i++)
		p.evolve();
	float t = (float) (clock() - start) / ( CLOCKS_PER_SEC);

	printf("%f\n",t);

	delete[] configurationFile;
	return 0;}