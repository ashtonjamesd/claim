.PHONY: test showcase

all:
	mkdir -p build
	gcc claim.c -o build/claim

test:
	mkdir -p build
	gcc test/test.c -o build/test
	./build/test

showcase:
	mkdir -p build
	gcc example/showcase.c -o build/showcase
	./build/showcase

skip:
	mkdir -p build
	gcc example/skipped_and_pending.c -o build/skipped_and_pending
	./build/skipped_and_pending