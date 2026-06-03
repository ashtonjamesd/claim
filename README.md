# claim

Single-header unit testing for c

## Usage

Copy `claim.h` into your project and include it.

```c
#include "claim.h"

describe("math")

should(add) {
    expect(1 + 1 == 2);
    expect(0 + 0 == 0);
}

should(subtract) {
    expect(5 - 3 == 2);
    refute(10 - 1 == 0);
}

int main() {
    return test_results();
}
```

Tests register themselves. Just write them and they run.

## Assertions

```c
expect(x == 1)               // asserts any expression
refute(x == 0)               // fails if expression is true
expect_null(ptr)             // ptr == NULL
expect_not_null(ptr)         // ptr != NULL
expect_eq(a, b)              // performs generic comparison on any primitive type
```

## Pending

Mark tests as 'work-in-progress' or 'todo' with `pending()`. They won't run and are tracked separately.

```c
should(not_ready_yet) {
    pending();
    // nothing below here runs
}
```

```bash
2 tests, 2 passed, 0 failed (1 pending)
```

## Skip

Skip a test at runtime with `skip()`. Use it when the test is valid but can't run right now, like with a broken external service, a known bug waiting to be fixed, or a platform-specific test.

```c
describe("storage")

should(read_from_cache) {
    skip("currently blocked by ticket #12 — cache returns stale entries");
    expect_eq(cache_get("key"), "xxx");
}
```

```bash
  test skipped 'storage' > 'read_from_cache'
    'blocked by ticket #12 — cache returns stale entries'

3 tests, 2 passed, 0 failed (0 pending, 1 skipped)
```

## Grouping

`describe` groups tests. Test failures show which group they belong to.

```c
describe("parser")

should(parse_int) {
    int result = parse("42");
    expect_eq(result, 42);
}

should(reject_empty) {
    int result = parse("");
    expect_eq(result, -1);
}
```

Failure output:

```bash
    assertion failed (test.c:5): expected 'result' to equal '42' (got -1, expected 42)
  test failed 'parser' > 'parse_int'
```


## Output

all passing:

```bash
2 tests, 2 passed, 0 failed (0 pending, 0 skipped)
```

with failures:

```bash
    assertion failed (test.c:12): expected 'a' to equal 'b' (got 3, expected 5)
  test failed 'math' > 'add'

3 tests, 2 passed, 1 failed (0 pending, 0 skipped)
```

`test_results` returns `1` on failure and `0` on success.
