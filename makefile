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
	rm -f solver
	rm -r results/*
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
	solver
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
		assets/configuration.o \
		assets/entity.o \
		assets/functions.o \
		assets/population.o \
		assets/reporter.o
	ar rc queens-lib.a \
		assets/configuration.o \
		assets/entity.o \
		assets/functions.o \
		assets/population.o \
		assets/reporter.o
	ranlib queens-lib.a

solver.o: \
		solver.cpp \
		queens-lib.h \
		assets/configuration.h \
		assets/debug.h \
		assets/entity.h \
		assets/globals.h \
		assets/population.h \
		assets/reporter.h
	g++ -c -o solver.o \
		solver.cpp
solver: \
		solver.o \
		queens-lib.a
	g++ -o solver \
		solver.o \
		queens-lib.a

#assets
assets/configuration.o: \
		assets/configuration.h \
		assets/configuration.cpp
	g++ -c -o assets/configuration.o \
		assets/configuration.cpp
assets/entity.o: \
		assets/debug.h \
		assets/entity.h \
		assets/entity.cpp
	g++ -c -o assets/entity.o \
		assets/entity.cpp
assets/functions.o: \
		assets/globals.h \
		assets/functions.cpp
	g++ -c -o assets/functions.o \
		assets/functions.cpp
assets/population.o: \
		assets/debug.h \
		assets/entity.o \
		assets/population.h \
		assets/population.cpp
	g++ -c -o assets/population.o \
		assets/population.cpp
assets/reporter.o: \
		assets/debug.h \
		assets/entity.o \
		assets/population.o \
		assets/reporter.h \
		assets/reporter.cpp
	g++ -c -o assets/reporter.o \
		assets/reporter.cpp

#tests
test-s: test-solver
test-solver: solver
	./solver

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

test-c: test-configuration
test-configuration: tests/testConfiguration.out
	tests/testConfiguration.out
tests/testConfiguration.out: \
		tests/testConfiguration.o \
		queens-lib.a
	g++ -o tests/testConfiguration.out \
		tests/testConfiguration.o \
		queens-lib.a
tests/testConfiguration.o: \
		tests/testConfiguration.cpp \
		assets/debug.h \
		assets/entity.h
	g++ -c -o tests/testConfiguration.o \
		tests/testConfiguration.cpp
