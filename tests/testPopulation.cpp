//library includes
#include <cstdio>
#include <cstdlib>
#include <ctime>
//local includes
#include "../assets/population.h"

int main(){
	srand( time( NULL));
	Population p ( 20, 8)	;

	p.entities[0].print_permutation();

	p.entities[0].newRandomPermutation();

	p.entities[0].print_permutation();
	//p.entities[0].print_grid();
}