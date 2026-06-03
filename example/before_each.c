#include "../claim.h"

static int counter;

describe("counter")

before(reset_counter) {
    counter = 0;
}

should(start_at_zero) {
    expect_eq(counter, 0);
}

should(increment) {
    counter += 5;
    expect_eq(counter, 5);
}

should(still_starts_at_zero) {
    expect_eq(counter, 0);
}

int main() {
    return test_results();
}