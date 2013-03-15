#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "../assets/debug.h"
#include "../assets/entity.h"

int main( ){
	srand( time( NULL));

	printf(" Entity A:\n");
	Entity a( 8);
	a.print_permutation();

	printf(" Entity C:\n");
	Entity c( a);
	c.print_permutation();
	printf("c==a; %d\n", c==a);
	c.newRandomPermutation();
	printf(" Entity C Randomized:\n");
	c.print_permutation();
	printf("c==a; %d\n", c==a);
	//c.print_permutation();
	//c.print_grid();

	/*printf(" Entity D:\n");
	int asdf[] = { 0,0,0,0,0,0,0,0};
	c.encode_permutation( asdf);
	c.print_permutation();
	c.draw_grid();
	printf(" Fitness: %d\n", c.fitness());

	printf(" Entity A mutated:\n");
	Entity a2(a);
	a2.mutate();
	a2.print_grid();

	printf(" Entity B:\n");
	Entity b( 8);
	b.print_grid();

	printf(" Entity A cross B:\n");
	Entity a3(a);
	a3.cross(b);
	a3.print_grid();
	printf(" Entity B cross A:\n");
	Entity b2(b);
	b2.cross(a);
	b2.print_grid();*/
}