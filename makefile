.PHONY: test

all:
	mkdir -p build
	gcc claim.c -o build/claim

test:
	mkdir -p build
	gcc test/test.c -o build/test
	./build/test