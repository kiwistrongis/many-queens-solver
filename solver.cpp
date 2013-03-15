//library includes
#include <cstdio>
#include <cstring>
#include <iostream>
//local includes
#include "queens-lib.h"

char defaultFilename[] = "default.ini";

int main( int argc, char** argv){
	char* filename = new char[256];
	if( argc > 1)
		strcpy( filename, argv[1]);
	else
		strcpy( filename, defaultFilename);

	printf("Filename: %s\n", filename);
	delete[] filename;}