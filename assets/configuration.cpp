//library includes
#include <cstddef>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
//override includes
#include "configuration.h"
#include "debug.h"

using namespace std;

Configuration::Configuration( char* filename){
	//set default values
	problem_size = 8;
	N = 200;
	mutation_chance = 0.1;
	cross_chance = 0.7;
	removeTheStrong = true;
	selection_method = 1;

	nGenerations = 500;

	report_period = 10;
	//datafile
	datafile = new char[ 128];
	char datafile_default[] = "results/default.csv";
	strcpy( datafile, datafile_default);
	//solutionsfile
	solutionsfile = new char[ 128];
	char solutionsfile_default[] = "results/default.sol";
	strcpy( solutionsfile, solutionsfile_default);
	//chart
	plotfile_base = new char[ 128];
	char plotfile_base_default[] = "results/default.png";
	strcpy( plotfile_base, plotfile_base_default);
	//plotscript_logfile
	plotscript_logfile = new char[ 128];
	char plotscript_logfile_default[] = "results/default.log2";
	strcpy( plotscript_logfile, plotscript_logfile_default);

	//try to load from file
	if( NULL != filename){
		string line;
		ifstream file( filename);
		while( file.good()){
			//get the key and value
			getline( file, line);
			int splitLoc = line.find('=');
			if( string::npos == splitLoc)
				continue;
			string key = line.substr( 0, splitLoc);
			string value = line.substr( splitLoc + 1);

			istringstream valueStream( value);
			//apply the value to the relevant key
			if( 0 == key.compare("problem_size")){
				int newField;
				if( valueStream >> newField)
					problem_size = newField;
				else
					printf("Reading field 'problem_size' failed.\n");}
			else if( 0 == key.compare("N")){
				int newField;
				if( valueStream >> newField)
					N = newField;
				else
					printf("Reading field 'N' failed.\n");}
			else if( 0 == key.compare("mutation_chance")){
				double newField;
				if( valueStream >> newField)
					mutation_chance = newField;
				else
					printf("Reading field 'mutation_chance' failed.\n");}
			else if( 0 == key.compare("cross_chance")){
				double newField;
				if( valueStream >> newField)
					cross_chance = newField;
				else
					printf("Reading field 'cross_chance' failed.\n");}
			else if( 0 == key.compare("removeTheStrong")){
				bool newField;
				if( valueStream >> newField)
					removeTheStrong = newField;
				else
					printf("Reading field 'removeTheStrong' failed.\n");}
			else if( 0 == key.compare("nGenerations")){
				int newField;
				if( valueStream >> newField)
					nGenerations = newField;
				else
					printf("Reading field 'nGenerations' failed.\n");}
			else if( 0 == key.compare("selection_method")){
				int newField;
				if( valueStream >> newField)
					selection_method = newField;
				else
					printf("Reading field 'selection_method' failed.\n");}
			else if( 0 == key.compare("datafile")){
				strcpy( datafile, value.c_str());}
			else if( 0 == key.compare("solutions")){
				strcpy( solutionsfile, value.c_str());}
			else if( 0 == key.compare("plotfile_base")){
				strcpy( plotfile_base, value.c_str());}
			else if( 0 == key.compare("plotscript_logfile")){
				strcpy( plotscript_logfile, value.c_str());}
			else if( 0 == key.compare("report_period")){
				int newField;
				if( valueStream >> newField)
					report_period = newField;
				else
					printf("Reading field 'report_period' failed.\n");}
			else
				printf("Failed to interpret key '%s'\n",key.c_str());}
		//done
		file.close();}}

Configuration::~Configuration(){
	delete[] datafile;
	delete[] solutionsfile;
	delete[] plotfile_base;
	delete[] plotscript_logfile;}
