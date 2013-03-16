//library includes
#include <cstdio>
//local includes
#include "../assets/configuration.h"

int main(){
	char filename[] = "default.ini";
	Configuration conf( filename);
	printf("N: %d\n", conf.N);
	printf("problem_size: %d\n", conf.problem_size);
	printf("mutation_chance: %f\n", conf.mutation_chance);
	printf("cross_chance: %f\n", conf.cross_chance);
	printf("removeTheStrong: %d\n", conf.removeTheStrong);
	printf("nGenerations: %d\n", conf.nGenerations);}