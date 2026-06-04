# claim

Single-header unit testing for c

- `expect` and `refute` / `expect_not` for boolean assertions
- automatic test runner, no need to run tests individually
- type-generic assertions with expected/actual values printed on failure
- test grouping with `describe` and `should` / `it`
- setup and teardown hooks with `before` and `after`
- `skip`, `pending`, and `only` for test control flow
- crash recovery, segfaults and aborts don't kill the runner
- configurable test output verbosity levels
- tracks time taken to run tests
- no dependencies, just copy the header file
- simple and intuitive user api

## Why?

A lot of C testing frameworks feel like C, perhaps verbose, boilerplate-heavy, or too low-level.

`claim` is inspired by Ruby's RSpec and Minitest, bringing constructs like `describe`, `should`, `before`, and `after` to C. The goal is a testing framework that reads like English while also providing a useful collection of tools.

<br/>

> **Notice:** claim is a new project and may contain bugs or stability issues. Use with caution.


## Usage

Copy `claim.h` into your project and include it.

```c
#include "claim.h"

describe("math")

should ("add") {
    expect(1 + 1 == 2);
    expect(0 + 0 == 0);
}

should ("subtract") {
    expect(5 - 3 == 2);
    refute(10 - 1 == 0);
}

int main() {
    return test_results(CLAIM_VERBOSE);
}
```

outputs:

```bash
  math
    ~ add (0.3ms)
    ~ subtract (0.3ms)

2 tests, 2 passed, 0 failed (0 pending, 0 skipped) in 0.7ms
```

Tests register themselves. Just write them and they run.

## Declaring Tests

All test functions are declared with `should` or `it`. They're interchangeable so use whichever you prefer.

```c
should ("add two numbers") {
    expect_eq(1 + 1, 2);
}

it ("subtracts two numbers") {
    expect_eq(5 - 3, 2);
}
```


## Assertions

```c
expect(x == 1)               // asserts any expression
refute(x == 0)               // fails if expression is true (alias: expect_not)
expect_eq(a, b)              // type-generic equality (int, float, char *, etc.)
expect_not_eq(a, b)          // type-generic inequality
expect_null(ptr)             // ptr == NULL
expect_not_null(ptr)         // ptr != NULL
```

## Grouping

`describe` groups tests. Test failures show which group they belong to. It applies to all tests below the `describe` until another is declared.

```c
describe("parser")

should ("parse int") {
    int result = parse("42");
    expect_eq(result, 42);
}

should ("reject empty") {
    int result = parse("");
    expect_eq(result, -1);
}
```

Failure output:

```bash
  parser
    x parse int (0.4ms)
        assertion failed (test.c:5): expected 'result' to equal '42' (got -1, expected 42)
```

## Pending

Mark tests as 'work-in-progress' or 'todo' with `pending()`. They won't run and are tracked separately.

```c
should ("not ready yet") {
    pending();
    // nothing below here runs
}
```

```bash
  pending tests
    - not ready yet (0.1ms)

2 tests, 2 passed, 0 failed (1 pending, 0 skipped) in 0.8ms
```

## Skip

Skip a test at runtime with `skip()`. Use it when the test is valid but can't run right now, like with a broken external service, a known bug waiting to be fixed, or a platform-specific test.

```c
describe("storage")

should ("read from cache") {
    skip("currently blocked by ticket #12 — cache returns stale entries");
    expect_eq(cache_get("key"), "xxx");
}
```

```bash
  storage
    - read from cache (0.2ms)
        'currently blocked by ticket #12 — cache returns stale entries'

3 tests, 2 passed, 0 failed (0 pending, 1 skipped) in 1.2ms
```

## Only

Focus on specific tests with `only`. All other tests are skipped.

```c
should ("not do this") {
    expect(true);
}

only ("do this") {
    expect_eq(1 + 1, 2);
}

should ("not do this either") {
    expect(true);
}
```

You can have multiple tests declared with `only`.

```bash
1 tests, 1 passed, 0 failed (0 pending, 2 skipped) in 0.5ms
```

## Setup and Teardown

`before` runs before every test in a group. `after` runs after. You might use them to allocate and free shared state.

```c
static int *counter;

describe("counter")

before ("setup") {
    counter = malloc(sizeof(int));
    *counter = 0;
}

after ("cleanup") {
    free(counter);
    counter = NULL;
}

should ("start at zero") {
    expect_eq(*counter, 0);
}

should ("increment") {
    *counter = 42;
    expect_eq(*counter, 42);
}

should ("reset between tests") {
    expect_eq(*counter, 0);
}
```

In this case, each test gets a new allocation. `before` and `after` callbacks  are scoped to the current `describe`. Declaring a new `describe` clears them.


## Output

all passing:

```bash
  math
    ~ add (0.3ms)
    ~ subtract (0.2ms)

2 tests, 2 passed, 0 failed (0 pending, 0 skipped) in 0.8ms
```

with failures:

```bash
  math
    ~ subtract (0.2ms)
    x add (0.4ms)
        assertion failed (test.c:6): expected 'a' to equal 'b' (got 3, expected 5)

2 tests, 1 passed, 1 failed (0 pending, 0 skipped) in 1.0ms
```

`test_results` returns `1` on failure and `0` on success.

## Crash Recovery

Each test runs in a forked process. If a test segfaults, aborts, or crashes, the runner catches it and keeps going.

```bash
  parser
    x parse null (0.3ms)
        crashed (SIGSEGV (segmentation fault))

3 tests, 2 passed, 1 failed (0 pending, 0 skipped) in 1.8ms
```

Handles `SIGSEGV`, `SIGABRT`, `SIGFPE`, and `SIGBUS`.

## Verbosity

Control how much output `test_results` produces by passing a verbosity level.

```c
test_results(CLAIM_VERBOSE)  // full output (default)
test_results(CLAIM_QUIET)    // failures and crashes only
test_results(CLAIM_SUMMARY)  // summary line only
test_results(CLAIM_SILENT)   // no output, just the exit code
```

## Building

Run the tests with:

```bash
make test
```

Build project with:

```bash
make
```
