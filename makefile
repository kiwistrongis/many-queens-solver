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
	assets/entity.o
commands:
tests:
resources:

#locals

#assets
assets/entity.o: \
		debug.h \
		assets/entity.h \
		assets/entity.cpp
	g++ -c -o assets/entity.o \
		assets/entity.cpp

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
		debug.h \
		assets/entity.h
	g++ -c -o tests/testEntity.o \
		tests/testEntity.cpp