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
	nGenerations = 500;
	datafile = new char[ 128];
	char datafile_default[] = "results/default.csv";
	strcpy( datafile, datafile_default);
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
					problem_size = newField;}
			else if( 0 == key.compare("N")){
				int newField;
				if( valueStream >> newField)
					N = newField;}
			else if( 0 == key.compare("mutation_chance")){
				double newField;
				if( valueStream >> newField)
					mutation_chance = newField;}
			else if( 0 == key.compare("cross_chance")){
				double newField;
				if( valueStream >> newField)
					cross_chance = newField;}
			else if( 0 == key.compare("removeTheStrong")){
				bool newField;
				if( valueStream >> newField)
					removeTheStrong = newField;}
			else if( 0 == key.compare("nGenerations")){
				int newField;
				if( valueStream >> newField)
					nGenerations = newField;}
			else if( 0 == key.compare("datafile")){
				strcpy( datafile, value.c_str());}}
		//done
		file.close();}}

Configuration::~Configuration(){
	delete[] datafile;}
