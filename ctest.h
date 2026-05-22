#ifndef test_h
#define test_h

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static struct {
    size_t tests_ran;
    size_t tests_failed;

    size_t assertions;
    size_t assertions_failed;
} runner = {
    .tests_failed = 0,
    .tests_ran = 0,
};

int conclude_test_runner() {
    printf("\ntest summary:\n");

    printf("  %zu tests ran\n", runner.tests_ran);
    printf("  %zu tests failed\n", runner.tests_failed);
    printf("  %zu assertions ran\n", runner.assertions);
    printf("  %zu assertions failed\n", runner.assertions_failed);

    return (runner.tests_failed > 0)? 1 : 0;
}

#define should(name) void name()

#define run_test(fn) do { \
    size_t prev_assertions_failed = runner.assertions_failed; \
    fn(); \
    runner.tests_ran += 1; \
    \
    if (prev_assertions_failed != runner.assertions_failed) { \
        runner.tests_failed += 1; \
        printf("test failed '%s'\n\n", #fn); \
    } \
} while (0); 

#define expect(expr) if (!(expr)) { \
    runner.assertions += 1; \
    runner.assertions_failed += 1; \
    printf("assertion failed (%s:%d): '%s'\n", __FILE__, __LINE__, #expr); \
} else { runner.assertions += 1; }

#define expect_null(expr) expect((expr) == NULL)
#define expect_not_null(expr) expect((expr) != NULL)
#define expect_str_eq(a, b) expect(strcmp((a), (b)) == 0)

#endif