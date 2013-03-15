#globals
default: all
freshen: clean all
clean: clean-special
	tools/cleandir .
	tools/cleandir assets
	tools/cleandir tests
	tools/cleandir tools
clean-special:
	rm -rf documentation
docs: doxyfile
	doxygen
docs-view: docs
	chromium-browser documentation/html/index.html

#git
git-prepare: clean
	git add -u
	git add *

#groups
all: locals assets
locals: \
	queens-lib.a \
	queens-solver.o \
	queens-solver
assets: \
	assets/entity.o \
	assets/population.o
commands:
tests: \
	tests/testEntity.out \
	tests/testPopulation.out
resources: \
	data/run.csv \
	data/plot.png

#locals
queens-lib.a: \
		assets/entity.o \
		assets/functions.o \
		assets/population.o \
		assets/configuration.o
	ar rc queens-lib.a \
		assets/entity.o \
		assets/functions.o \
		assets/population.o \
		assets/configuration.o
	ranlib queens-lib.a

queens-solver.o: \
		queens-solver.cpp \
		queens-lib.h \
		assets/debug.h \
		assets/entity.h \
		assets/globals.h \
		assets/population.h \
		assets/configuration.h
	g++ -c -o queens-solver.o \
		queens-solver.cpp
queens-solver: \
		queens-solver.o \
		queens-lib.h
	g++ -o queens-solver \
		queens-solver.o \
		queens-lib.a

#assets
assets/entity.o: \
		assets/debug.h \
		assets/entity.h \
		assets/entity.cpp
	g++ -c -o assets/entity.o \
		assets/entity.cpp
assets/population.o: \
		assets/debug.h \
		assets/entity.o \
		assets/population.h \
		assets/population.cpp
	g++ -c -o assets/population.o \
		assets/population.cpp
assets/functions.o: \
		assets/globals.h \
		assets/functions.cpp
	g++ -c -o assets/functions.o \
		assets/functions.cpp
assets/configuration.o: \
		assets/configuration.h
	g++ -c -o assets/configuration.o \
		assets/configuration.cpp

#tests
test-e: test-entity
test-entity: tests/testEntity.out
	tests/testEntity.out
tests/testEntity.out: \
		tests/testEntity.o \
		queens-lib.a
	g++ -o tests/testEntity.out \
		tests/testEntity.o \
		queens-lib.a
tests/testEntity.o: \
		tests/testEntity.cpp \
		assets/debug.h \
		assets/entity.h
	g++ -c -o tests/testEntity.o \
		tests/testEntity.cpp

test-p: test-population
test-population: tests/testPopulation.out
	tests/testPopulation.out
tests/testPopulation.out: \
		tests/testPopulation.o \
		queens-lib.a
	g++ -o tests/testPopulation.out \
		tests/testPopulation.o \
		queens-lib.a
tests/testPopulation.o: \
		tests/testPopulation.cpp \
		assets/debug.h \
		assets/entity.h
	g++ -c -o tests/testPopulation.o \
		tests/testPopulation.cpp
