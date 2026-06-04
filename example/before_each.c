#include "../claim.h"

static int counter;

describe("counter")

before (reset_counter) {
    counter = 0;
}

should ("start at zero") {
    expect_eq(counter, 0);
}

should ("increment") {
    counter += 5;
    expect_eq(counter, 5);
}

should ("still starts at zero") {
    expect_eq(counter, 0);
}

int main() {
    return test_results();
}