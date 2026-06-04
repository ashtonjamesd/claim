#ifndef claim_h
#define claim_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BOLD_RED "\033[1;31m"
#define RESET "\033[0m"

static bool claim_eq_int(int a, int b) { return a == b; }
static bool claim_eq_unsigned_int(unsigned int a, unsigned int b) { return a == b; }
static bool claim_eq_long(long a, long b) { return a == b; }
static bool claim_eq_unsigned_long(unsigned long a, unsigned long b) { return a == b; }
static bool claim_eq_long_long(long long a, long long b) { return a == b; }
static bool claim_eq_unsigned_long_long(unsigned long long a, unsigned long long b) { return a == b; }
static bool claim_eq_short(short a, short b) { return a == b; }
static bool claim_eq_unsigned_short(unsigned short a, unsigned short b) { return a == b; }
static bool claim_eq_char(char a, char b) { return a == b; }
static bool claim_eq_unsigned_char(unsigned char a, unsigned char b) { return a == b; }
static bool claim_eq_float(float a, float b) { return a == b; }
static bool claim_eq_double(double a, double b) { return a == b; }
static bool claim_eq_bool(bool a, bool b) { return a == b; }

static bool claim_eq_str(char *a, char *b) { 
    if (!a && !b) return true;
    if (!a || !b) return false;

    return strcmp(a, b) == 0;
}

static bool claim_eq_const_str(const char *a, const char *b) { 
    if (!a && !b) return true;
    if (!a || !b) return false;

    return strcmp(a, b) == 0;
}

#define FORMAT_TEST_VALUE(x) _Generic((x), \
    int: "%d", \
    unsigned int: "%u", \
    long: "%ld", \
    unsigned long: "%lu", \
    long long: "%lld", \
    unsigned long long: "%llu", \
    short: "%d", \
    unsigned short: "%u", \
    char: "%c", \
    unsigned char: "%u", \
    float: "%g", \
    double: "%g", \
    bool: "%d", \
    char *: "\"%s\"", \
    const char *: "\"%s\"" \
)

#define CLAIM_EQ_FN(x) _Generic((x), \
    int: claim_eq_int, \
    unsigned int: claim_eq_unsigned_int, \
    long: claim_eq_long, \
    unsigned long: claim_eq_unsigned_long, \
    long long: claim_eq_long_long, \
    unsigned long long: claim_eq_unsigned_long_long, \
    short: claim_eq_short, \
    unsigned short: claim_eq_unsigned_short, \
    char: claim_eq_char, \
    unsigned char: claim_eq_unsigned_char, \
    float: claim_eq_float, \
    double: claim_eq_double, \
    bool: claim_eq_bool, \
    char *: claim_eq_str, \
    const char *: claim_eq_const_str \
)

#define expect_eq(a, b) do { \
    runner.assertions += 1; \
    if (!CLAIM_EQ_FN(a)((a), (b))) { \
        runner.assertions_failed += 1; \
        printf(ASSERTION_FAILED " (%s:%d): expected '%s' to equal '%s' (got ", __FILE__, __LINE__, #a, #b); \
        printf(FORMAT_TEST_VALUE(a), (a)); \
        printf(", expected "); \
        printf(FORMAT_TEST_VALUE(b), (b)); \
        printf(")\n"); \
    } \
} while (0)

#define expect_not_eq(a, b) do { \
    runner.assertions += 1; \
    if (CLAIM_EQ_FN(a)((a), (b))) { \
        runner.assertions_failed += 1; \
        printf(ASSERTION_FAILED " (%s:%d): expected '%s' to not equal '%s' (both are ", __FILE__, __LINE__, #a, #b); \
        printf(FORMAT_TEST_VALUE(a), (a)); \
        printf(")\n"); \
    } \
} while (0)

typedef void (*TestFunc)(void);

static const char *current_describe = NULL;

static const char *registered_group = NULL;
static TestFunc registered_setup = NULL;
static TestFunc registered_teardown = NULL;

typedef struct {
    const char *test_name;
    const char *group;

    TestFunc fn;
    TestFunc setup;
    TestFunc teardown;
} registered_test;

#define _CONCAT2(a, b) a##b
#define _CONCAT(a, b) _CONCAT2(a, b)
#define _UNIQUE(prefix) _CONCAT(prefix, __COUNTER__)

#define MAX_TESTS 1024

static struct {
    size_t tests_ran;
    size_t tests_failed;

    size_t assertions;
    size_t assertions_failed;

    size_t tests_pending;
    size_t tests_skipped;

    double suite_ms;

    registered_test registry[MAX_TESTS];
    size_t registry_count;
} runner;

#define pending() do { \
    runner.tests_pending += 1; \
    return; \
} while (0)

#define skip(msg) do { \
    runner.tests_skipped += 1; \
    printf("    '%s'\n", msg); \
    return; \
} while (0)

#define should(name) \
    void name(void); \
    __attribute__((constructor)) void register_##name(void) { \
        if (runner.registry_count >= MAX_TESTS) { \
            fprintf(stderr, BOLD_RED "error" RESET ": MAX_TESTS (%d) exceeded\n", MAX_TESTS); \
            exit(1); \
        } \
        runner.registry[runner.registry_count].test_name = #name; \
        runner.registry[runner.registry_count].group = registered_group; \
        runner.registry[runner.registry_count].fn = name; \
        runner.registry[runner.registry_count].setup = registered_setup; \
        runner.registry[runner.registry_count].teardown = registered_teardown; \
        runner.registry_count++; \
    } \
    void name(void)

#define describe(name) \
    __attribute__((constructor)) void _UNIQUE(_set_group_)(void) { \
        registered_group = name; \
        registered_setup = NULL; \
        registered_teardown = NULL; \
    }

#define before(name) \
    void name(); \
    __attribute__((constructor)) void _UNIQUE(_setup)(void) { \
        registered_setup = name; \
    } \
    void name()

#define after(name) \
    void name(); \
    __attribute__((constructor)) void _UNIQUE(_setup)(void) { \
        registered_teardown = name; \
    } \
    void name()

#define ASSERTION_FAILED "    " BOLD_RED "assertion failed" RESET

#define refute(expr) do { \
    runner.assertions += 1; \
    if (expr) { \
        runner.assertions_failed += 1; \
        printf(ASSERTION_FAILED " (%s:%d): '%s'\n", __FILE__, __LINE__, #expr); \
    } \
} while (0)

#define expect(expr) do { \
    runner.assertions += 1; \
    if (!(expr)) { \
        runner.assertions_failed += 1; \
        printf(ASSERTION_FAILED " (%s:%d): '%s'\n", __FILE__, __LINE__, #expr); \
    } \
} while (0)

#define expect_null(expr) do { \
    const void *_val = (expr); \
    runner.assertions += 1; \
    if (_val != NULL) { \
        runner.assertions_failed += 1; \
        printf(ASSERTION_FAILED " (%s:%d): expected '%s' to be NULL\n", __FILE__, __LINE__, #expr); \
    } \
} while (0)

#define expect_not_null(expr) do { \
    const void *_val = (expr); \
    runner.assertions += 1; \
    if (_val == NULL) { \
        runner.assertions_failed += 1; \
        printf(ASSERTION_FAILED " (%s:%d): expected '%s' to not be NULL\n", __FILE__, __LINE__, #expr); \
    } \
} while (0)

static void claim_print_result(const char *label, const char *group, const char *name, const char *color, double ms) {
    if (group) {
        printf("%s  %s " RESET "'%s'%s > " RESET "'%s' (%.1fms)\n\n", color, label, group, color, name, ms);
    } else {
        printf("%s  %s " RESET "'%s' (%.1fms)\n\n", color, label, name, ms);
    }
}

static double claim_elapsed_ms(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000.0
         + (end.tv_nsec - start.tv_nsec) / 1000000.0;
}

static void run_all_tests() {
    struct timespec suite_start, suite_end;
    clock_gettime(CLOCK_MONOTONIC, &suite_start);

    for (size_t i = 0; i < runner.registry_count; i++) {
        current_describe = runner.registry[i].group;
        runner.tests_ran += 1;

        fflush(stdout);

        struct timespec test_start, test_end;
        clock_gettime(CLOCK_MONOTONIC, &test_start);
        pid_t pid = fork();

        if (pid == 0) {
            if (runner.registry[i].setup) runner.registry[i].setup();
            runner.registry[i].fn();
            if (runner.registry[i].teardown) runner.registry[i].teardown();
            
            if (runner.tests_pending > 0) _exit(2);
            if (runner.tests_skipped > 0) _exit(3);
            if (runner.assertions_failed > 0) _exit(1);

            _exit(0);
        }
        
        int status;
        waitpid(pid, &status, 0);
        clock_gettime(CLOCK_MONOTONIC, &test_end);
        double test_ms = claim_elapsed_ms(test_start, test_end);

        const char *group = current_describe;
        const char *name = runner.registry[i].test_name;

        if (WIFSIGNALED(status)) {
            int sig = WTERMSIG(status);
            const char *sig_name = "unknown signal";
            if (sig == SIGSEGV) {
                sig_name = "SIGSEGV (segmentation fault)";
            } else if (sig == SIGABRT) {
                sig_name = "SIGABRT (abort)";
            } else if (sig == SIGFPE) {
                sig_name = "SIGFPE (floating point exception)";
            } else if (sig == SIGBUS) {
                sig_name = "SIGBUS (bus error)";
            }

            runner.tests_failed += 1;
            printf("    " BOLD_RED "crashed" RESET " (%s)\n", sig_name);
            claim_print_result("test crashed", group, name, BOLD_RED, test_ms);
        } else if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);

            if (code == 1) {
                runner.tests_failed += 1;
                claim_print_result("test failed", group, name, RED, test_ms);
            } else if (code == 2) {
                runner.tests_pending += 1;
                claim_print_result("test pending", group, name, YELLOW, test_ms);
            } else if (code == 3) {
                runner.tests_skipped += 1;
                claim_print_result("test skipped", group, name, YELLOW, test_ms);
            }
        }
    }
    current_describe = NULL;

    clock_gettime(CLOCK_MONOTONIC, &suite_end);
    runner.suite_ms = claim_elapsed_ms(suite_start, suite_end);
}

static int test_results() {
    run_all_tests();

    size_t tests_passed = runner.tests_ran - runner.tests_failed - runner.tests_pending - runner.tests_skipped;
    size_t tests_ran = runner.tests_ran - runner.tests_pending - runner.tests_skipped;

    const char *color = (runner.tests_failed > 0) ? RED : GREEN;

    printf(
        "\n%s%zu tests, %zu passed, %zu failed (%zu pending, %zu skipped) in %.1fms" RESET "\n",
        color, tests_ran, tests_passed, runner.tests_failed, runner.tests_pending, runner.tests_skipped, runner.suite_ms
    );

    return (runner.tests_failed > 0)? 1 : 0;
}

#endif