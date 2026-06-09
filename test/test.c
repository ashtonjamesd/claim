#include "../claim.h"

describe("expect and refute")

it ("should expect and refute correctly") {
    expect(true);
    refute(false);

    expect(true);
    expect_not(false);
}

it ("should handle negation") {
    expect(!(1 == 2));
}


describe("null")

should ("detect null") {
    char *p = NULL;
    expect_null(p);

    char *q = "something";
    expect_not_null(q);
}


describe("expect_eq")

should ("compare nt") {
    int a = 42;
    int b = 42;

    expect_eq(a, b);
}

should ("compare unsigned int") {
    unsigned int a = 100u;
    unsigned int b = 100u;

    expect_eq(a, b);
}

should ("compare long") {
    long a = 100000L;
    long b = 100000L;

    expect_eq(a, b);
}

should ("compare unsigned long") {
    unsigned long a = 100000UL;
    unsigned long b = 100000UL;

    expect_eq(a, b);
}

should ("compare long long") {
    long long a = 9000000000LL;
    long long b = 9000000000LL;

    expect_eq(a, b);
}

should ("compare unsigned long long") {
    unsigned long long a = 9000000000ULL;
    unsigned long long b = 9000000000ULL;

    expect_eq(a, b);
}

should ("compare short") {
    short a = 10;
    short b = 10;

    expect_eq(a, b);
}

should ("compare unsigned short") {
    unsigned short a = 10;
    unsigned short b = 10;

    expect_eq(a, b);
}

should ("compare char") {
    char a = 'A';
    char b = 'A';

    expect_eq(a, b);
}

should ("compare unsigned char") {
    unsigned char a = 255;
    unsigned char b = 255;

    expect_eq(a, b);
}

should ("compare float") {
    float a = 3.14f;
    float b = 3.14f;

    expect_eq(a, b);
}

should ("compare double") {
    double a = 3.14159265358979;
    double b = 3.14159265358979;

    expect_eq(a, b);
}

should ("compare bool") {
    bool a = true;
    bool b = true;

    expect_eq(a, b);
}

should ("compare char ptr") {
    char *a = "hello";
    char *b = "hello";

    expect_eq(a, b);
}

should ("compare const char ptr") {
    const char *a = "world";
    const char *b = "world";

    expect_eq(a, b);
}


describe("expect_not_eq")

should ("not eq int") {
    int a = 1;
    int b = 2;

    expect_not_eq(a, b);
}

should ("not eq unsigned int") {
    unsigned int a = 1u;
    unsigned int b = 2u;

    expect_not_eq(a, b);
}

should ("not eq long") {
    long a = 100L;
    long b = 200L;

    expect_not_eq(a, b);
}

should ("not eq unsigned long") {
    unsigned long a = 100UL;
    unsigned long b = 200UL;

    expect_not_eq(a, b);
}

should ("not eq long long") {
    long long a = 9000000000LL;
    long long b = 9000000001LL;

    expect_not_eq(a, b);
}

should ("not eq unsigned long long") {
    unsigned long long a = 9000000000ULL;
    unsigned long long b = 9000000001ULL;

    expect_not_eq(a, b);
}

should ("not eq short") {
    short a = 10;
    short b = 20;

    expect_not_eq(a, b);
}

should ("not eq unsigned short") {
    unsigned short a = 10;
    unsigned short b = 20;

    expect_not_eq(a, b);
}

should ("not eq char") {
    char a = 'A';
    char b = 'B';

    expect_not_eq(a, b);
}

should ("not eq unsigned char") {
    unsigned char a = 100;
    unsigned char b = 200;

    expect_not_eq(a, b);
}

should ("not eq float") {
    float a = 1.0f;
    float b = 2.0f;

    expect_not_eq(a, b);
}

should ("not eq double") {
    double a = 1.0;
    double b = 2.0;

    expect_not_eq(a, b);
}

should ("not eq bool") {
    bool a = true;
    bool b = false;

    expect_not_eq(a, b);
}

should ("not eq char ptr") {
    char *a = "hello";
    char *b = "world";

    expect_not_eq(a, b);
}

should ("not eq const char ptr") {
    const char *a = "foo";
    const char *b = "bar";

    expect_not_eq(a, b);
}


describe("null string safety")

should ("both null char ptr") {
    char *a = NULL;
    char *b = NULL;
    expect_eq(a, b);
}

should ("left null char ptr") {
    char *a = NULL;
    char *b = "hello";
    expect_not_eq(a, b);
}

should ("right null char ptr") {
    char *a = "hello";
    char *b = NULL;
    expect_not_eq(a, b);
}

should ("both null const char ptr") {
    const char *a = NULL;
    const char *b = NULL;
    expect_eq(a, b);
}

should ("left null const char ptr") {
    const char *a = NULL;
    const char *b = "hello";
    expect_not_eq(a, b);
}

should ("right null const char ptr") {
    const char *a = "hello";
    const char *b = NULL;
    expect_not_eq(a, b);
}

int main() {
    return test_results(CLAIM_QUIET);
}