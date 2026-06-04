#include "../claim.h"
#include <stdlib.h>


describe("expect and refute")

should ("pass with expect") {
    expect(1 + 1 == 2);
}

should ("pass with refute") {
    refute(1 == 2);
}

should ("pass with expect_not") {
    expect_not(1 == 2);
}

should ("fail with expect") {
    expect(1 == 2);
}

should ("fail with refute") {
    refute(1 == 1);
    refute(2 == 2);
}


describe("expect_eq")

should ("compare int") {
    expect_eq(42, 42);
}

should ("fail comparing int") {
    int a = 3;
    int b = 5;
    expect_eq(a, b);
}

should ("compare unsigned int") {
    unsigned int a = 100u;
    expect_eq(a, 100u);
}

should ("compare long") {
    long a = 100000L;
    expect_eq(a, 100000L);
}

should ("compare float") {
    float a = 3.14f;
    expect_eq(a, 3.14f);
}

should ("compare double") {
    double a = 2.718;
    expect_eq(a, 2.718);
}

should ("compare char") {
    char a = 'A';
    expect_eq(a, 'A');
}

should ("compare bool") {
    bool a = true;
    expect_eq(a, true);
}

should ("compare strings") {
    char *a = "hello";
    char *b = "hello";
    expect_eq(a, b);
}

should ("fail comparing strings") {
    const char *a = "hello";
    const char *b = "world";
    expect_eq(a, b);
}


describe("expect_not_eq")

should ("pass when different") {
    expect_not_eq(1, 2);
}

should ("fail when equal") {
    expect_not_eq(5, 5);
}


describe("null checks")

should ("detect null") {
    char *p = NULL;
    expect_null(p);
}

should ("detect not null") {
    char *p = "something";
    expect_not_null(p);
}

should ("null strings are equal") {
    char *a = NULL;
    char *b = NULL;
    expect_eq(a, b);
}


describe("pending tests")

should ("not ready yet") {
    pending();
    expect(false);
}


describe("skipped tests")

should ("skip this one") {
    skip("blocked by upstream bug");
    expect(false);
}


describe("setup and teardown")
    
static int *counter;

before (alloc_counter) {
    counter = malloc(sizeof(int));
    *counter = 0;
}

after (free_counter) {
    free(counter);
    counter = NULL;
}

should ("start at zero") {
    expect_eq(*counter, 0);
}

should ("mutate and reset") {
    *counter = 99;
    expect_eq(*counter, 99);
}

should ("reset between tests") {
    expect_eq(*counter, 0);
}


describe("crash recovery")

should ("survive a segfault") {
    volatile int *p = NULL;
    *p = 42;
}

should ("survive an abort") {
    abort();
}

should ("still run after crashes") {
    expect(true);
}


describe("it alias")

it ("works like should") {
    expect(true);
}

int main() {
    return test_results(CLAIM_QUIET);
}
