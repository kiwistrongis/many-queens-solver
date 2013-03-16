//library includes
#include <cstdio>
#include <cstdlib>
#include <ctime>
//local includes
#include "../assets/population.h"

int main(){
	srand( time( NULL));
	Population p;

	clock_t t = clock();
	for( int i = 0; i < 500; i ++)
		p.evolve();
	printf("evolution took %f seconds\n", ((float)(clock()-t))/(CLOCKS_PER_SEC));

	printf("prefiltered solutions size: %d\n", p.solutions.size());
	t = clock();
	p.removeDuplicateSolutions();
	printf("filtering took %f seconds\n", ((float)(clock()-t))/(CLOCKS_PER_SEC));
	
	printf("filtered solutions size: %d\n", p.solutions.size());
	if( p.solutions.size() > 0){
		printf("first solution:\n");
		p.solutions[0].draw_grid();}
}