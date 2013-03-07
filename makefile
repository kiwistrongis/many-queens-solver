#globals
default: all
clean:
	tools/cleandir .
	tools/cleandir assets
	tools/cleandir tests
	tools/cleandir tools

#git
git-prepare: clean
	git add -u
	git add *
git-push:
	git push origin master

#groups
all: locals assets
locals:
assets:
commands:
tests:
resources:

#locals


#assets


#tests
