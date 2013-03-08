#include <ctime>
#include "../debug.h"
#include "../assets/entity.h"

int main( ){
	srand( time( NULL));
	Entity a( 8);
	printf(" A:\n");
	a.draw_grid();
	//printf(" fitness: %d\n", e.fitness());
	printf(" A mutated:\n");
	Entity(a).mutate().draw_grid();
	printf(" B:\n");
	Entity b( 8);
	b.draw_grid();
	printf(" A cross B:\n");
	Entity(a).cross(b).draw_grid();
	printf(" B cross A:\n");
	Entity(b).cross(a).draw_grid();
}