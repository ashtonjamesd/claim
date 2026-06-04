#include "../claim.h"

describe("expect and refute")

should (test_the_truth) {
    expect(true);
}

should (test_another_truth) {
    refute(false);
}

int main() {
    return test_results();
}