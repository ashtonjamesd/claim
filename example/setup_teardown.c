#include "../claim.h"
#include <stdlib.h>

typedef struct {
    int *items;
    size_t len;
    size_t cap;
} int_vec;

static int_vec *vec;

describe("int_vec")


before (alloc_vec) {
    vec = malloc(sizeof(int_vec));
    vec->items = malloc(sizeof(int) * 8);
    vec->len = 0;
    vec->cap = 8;
}

after (free_vec) {
    free(vec->items);
    free(vec);
    vec = NULL;
}

should ("start empty") {
    expect_eq((int)vec->len, 0);
    expect_not_null(vec->items);
}

should ("push items") {
    vec->items[vec->len++] = 10;
    vec->items[vec->len++] = 20;

    expect_eq((int)vec->len, 2);
    expect_eq(vec->items[0], 10);
    expect_eq(vec->items[1], 20);
}

should ("not leak between tests") {
    expect_eq((int)vec->len, 0);
}

int main() {
    return test_results();
}