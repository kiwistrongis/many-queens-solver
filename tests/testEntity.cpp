#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "../assets/debug.h"
#include "../assets/entity.h"

int main( ){
	srand( time( NULL));
	Entity a( 8);

	printf(" Entity A:\n");
	a.print_grid();

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
	b2.print_grid();
}