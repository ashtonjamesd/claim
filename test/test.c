#include "../claim.h"

describe("expect and refute")

should(should_expect_and_refute_correctly) {
    expect(true);
    refute(false);
}

should(should_handle_negation) {
    expect(!(1 == 2));
}


describe("null")

should(should_detect_null) {
    char *p = NULL;
    expect_null(p);

    char *q = "something";
    expect_not_null(q);
}


describe("expect_eq")

should(compare_int) {
    int a = 42;
    int b = 41;

    expect_eq(a, b);
}

should(compare_unsigned_int) {
    unsigned int a = 100u;
    unsigned int b = 100u;

    expect_eq(a, b);
}

should(compare_long) {
    long a = 100000L;
    long b = 100000L;

    expect_eq(a, b);
}

should(compare_unsigned_long) {
    unsigned long a = 100000UL;
    unsigned long b = 100000UL;

    expect_eq(a, b);
}

should(compare_long_long) {
    long long a = 9000000000LL;
    long long b = 9000000000LL;

    expect_eq(a, b);
}

should(compare_unsigned_long_long) {
    unsigned long long a = 9000000000ULL;
    unsigned long long b = 9000000000ULL;

    expect_eq(a, b);
}

should(compare_short) {
    short a = 10;
    short b = 10;

    expect_eq(a, b);
}

should(compare_unsigned_short) {
    unsigned short a = 10;
    unsigned short b = 10;

    expect_eq(a, b);
}

should(compare_char) {
    char a = 'A';
    char b = 'A';

    expect_eq(a, b);
}

should(compare_unsigned_char) {
    unsigned char a = 255;
    unsigned char b = 255;

    expect_eq(a, b);
}

should(compare_float) {
    float a = 3.14f;
    float b = 3.14f;

    expect_eq(a, b);
}

should(compare_double) {
    double a = 3.14159265358979;
    double b = 3.14159265358979;

    expect_eq(a, b);
}

should(compare_bool) {
    bool a = true;
    bool b = true;

    expect_eq(a, b);
}

should(compare_char_ptr) {
    char *a = "hello";
    char *b = "hello";

    expect_eq(a, b);
}

should(compare_const_char_ptr) {
    const char *a = "world";
    const char *b = "world";

    expect_eq(a, b);
}


describe("expect_not_eq")

should(not_eq_int) {
    int a = 1;
    int b = 2;

    expect_not_eq(a, b);
}

should(not_eq_unsigned_int) {
    unsigned int a = 1u;
    unsigned int b = 2u;

    expect_not_eq(a, b);
}

should(not_eq_long) {
    long a = 100L;
    long b = 200L;

    expect_not_eq(a, b);
}

should(not_eq_unsigned_long) {
    unsigned long a = 100UL;
    unsigned long b = 200UL;

    expect_not_eq(a, b);
}

should(not_eq_long_long) {
    long long a = 9000000000LL;
    long long b = 9000000001LL;

    expect_not_eq(a, b);
}

should(not_eq_unsigned_long_long) {
    unsigned long long a = 9000000000ULL;
    unsigned long long b = 9000000001ULL;

    expect_not_eq(a, b);
}

should(not_eq_short) {
    short a = 10;
    short b = 20;

    expect_not_eq(a, b);
}

should(not_eq_unsigned_short) {
    unsigned short a = 10;
    unsigned short b = 20;

    expect_not_eq(a, b);
}

should(not_eq_char) {
    char a = 'A';
    char b = 'B';

    expect_not_eq(a, b);
}

should(not_eq_unsigned_char) {
    unsigned char a = 100;
    unsigned char b = 200;

    expect_not_eq(a, b);
}

should(not_eq_float) {
    float a = 1.0f;
    float b = 2.0f;

    expect_not_eq(a, b);
}

should(not_eq_double) {
    double a = 1.0;
    double b = 2.0;

    expect_not_eq(a, b);
}

should(not_eq_bool) {
    bool a = true;
    bool b = false;

    expect_not_eq(a, b);
}

should(not_eq_char_ptr) {
    char *a = "hello";
    char *b = "world";

    expect_not_eq(a, b);
}

should(not_eq_const_char_ptr) {
    const char *a = "foo";
    const char *b = "bar";

    expect_not_eq(a, b);
}

int main() {
    return test_results();
}