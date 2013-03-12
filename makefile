#globals
default: all
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
git-push:
	git push origin master

#groups
all: locals assets
locals:
assets: \
	assets/bitstring.o \
	assets/entity.o
commands:
tests:
resources:

#locals

#assets
assets/entity.o: \
		assets/debug.h \
		assets/entity.h \
		assets/entity.cpp
	g++ -c -o assets/entity.o \
		assets/entity.cpp
assets/bitstring.o: \
		assets/debug.h \
		assets/bitstring.h \
		assets/bitstring.cpp
	g++ -c -o assets/bitstring.o \
		assets/bitstring.cpp

#tests
test-entity: tests/testEntity.out
	tests/testEntity.out
tests/testEntity.out: \
		tests/testEntity.o \
		assets/entity.o
	g++ -o tests/testEntity.out \
		tests/testEntity.o \
		assets/entity.o
tests/testEntity.o: \
		tests/testEntity.cpp \
		assets/debug.h \
		assets/entity.h
	g++ -c -o tests/testEntity.o \
		tests/testEntity.cpp

test-bitstring: tests/testBitstring.out
	tests/testBitstring.out
tests/testBitstring.out: \
		tests/testBitstring.o \
		assets/bitstring.o
	g++ -o tests/testBitstring.out \
		tests/testBitstring.o \
		assets/bitstring.o
tests/testBitstring.o: \
		tests/testBitstring.cpp \
		assets/debug.h \
		assets/bitstring.h
	g++ -c -o tests/testBitstring.o \
		tests/testBitstring.cpp