#include "../claim.h"

it ("run a test outside of any describe") {
    expect(true);
}


describe("passing")

it ("pass") {
    expect(true);
    refute(false);
    expect_not(false);
    expect_null(NULL);
    expect_not_null("x");
    expect_eq(1, 1);
    expect_not_eq(1, 2);
}


describe("pending and skip")

it ("be pending") {
    pending();
}

it ("be skipped with a reason") {
    skip("blocked by ticket #12");
}


describe("basic assertions")

it ("fail expect") {
    expect(1 == 2);
}

it ("fail refute") {
    refute(1 == 1);
}

it ("fail expect_not") {
    expect_not(2 > 1);
}

it ("fail expect_null") {
    int x = 5;
    expect_null(&x);
}

it ("fail expect_not_null") {
    int *p = NULL;
    expect_not_null(p);
}

it ("fail several assertions in one test") {
    expect(1 == 2);
    refute(true);
    expect_eq(3, 4);
    expect_null("not null");
}


describe("expect_eq on every type")

it ("fail int") {
    int a = 1;
    int b = 2;
    expect_eq(a, b);
}

it ("fail unsigned int") {
    unsigned int a = 1;
    unsigned int b = 4000000000u;
    expect_eq(a, b);
}

it ("fail long") {
    long a = -100000;
    long b = 100000;
    expect_eq(a, b);
}

it ("fail unsigned long") {
    unsigned long a = 1;
    unsigned long b = 2;
    expect_eq(a, b);
}

it ("fail long long") {
    long long a = 9000000000LL;
    long long b = -9000000000LL;
    expect_eq(a, b);
}

it ("fail unsigned long long") {
    unsigned long long a = 1;
    unsigned long long b = 18000000000000000000ULL;
    expect_eq(a, b);
}

it ("fail short") {
    short a = -3;
    short b = 3;
    expect_eq(a, b);
}

it ("fail unsigned short") {
    unsigned short a = 1;
    unsigned short b = 65535;
    expect_eq(a, b);
}

it ("fail char") {
    char a = 'a';
    char b = 'z';
    expect_eq(a, b);
}

it ("fail unsigned char") {
    unsigned char a = 1;
    unsigned char b = 255;
    expect_eq(a, b);
}

it ("fail float") {
    float a = 1.5f;
    float b = 2.25f;
    expect_eq(a, b);
}

it ("fail double") {
    double a = 3.14159;
    double b = 2.71828;
    expect_eq(a, b);
}

it ("fail bool") {
    bool a = true;
    bool b = false;
    expect_eq(a, b);
}

it ("fail char *") {
    char *a = "hello";
    char *b = "world";
    expect_eq(a, b);
}

it ("fail const char *") {
    const char *a = "foo";
    const char *b = "bar";
    expect_eq(a, b);
}

it ("fail null vs string") {
    char *a = NULL;
    char *b = "hello";
    expect_eq(a, b);
}


describe("expect_not_eq on every type")

it ("fail int") {
    int a = 7;
    expect_not_eq(a, a);
}

it ("fail unsigned long long") {
    unsigned long long a = 18000000000000000000ULL;
    expect_not_eq(a, a);
}

it ("fail char") {
    char a = 'q';
    expect_not_eq(a, a);
}

it ("fail double") {
    double a = 0.5;
    expect_not_eq(a, a);
}

it ("fail bool") {
    bool a = false;
    expect_not_eq(a, a);
}

it ("fail char *") {
    char *a = "same";
    char *b = "same";
    expect_not_eq(a, b);
}

it ("fail both null") {
    char *a = NULL;
    char *b = NULL;
    expect_not_eq(a, b);
}


describe("setup and teardown")

static int counter = 0;

before ("reset counter") {
    counter = 0;
    expect_eq(counter, 1);
}

after ("check counter") {
    expect_eq(counter, 99);
}

it ("fail in before, test, and after") {
    counter = 5;
    expect_eq(counter, 6);
}


describe("crashes")

it ("segfault") {
    volatile int *p = NULL;
    *p = 1;
}

it ("abort") {
    abort();
}

it ("floating point exception") {
    raise(SIGFPE);
}

it ("bus error") {
    raise(SIGBUS);
}

it ("illegal instruction") {
    raise(SIGILL);
}

it ("be killed by another signal") {
    raise(SIGTERM);
}

it ("call exit with a non-zero code") {
    exit(7);
}

it ("fail assertions and then crash") {
    expect(false);
    expect_eq(1, 2);
    abort();
}


int main() {
    return test_results(CLAIM_VVV);
}
