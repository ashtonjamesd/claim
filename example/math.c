#include "../claim.h"

describe("math")

should (add) {
    expect(2 + 2 == 4);
}

should (subtract) {
    expect(10 - 5 == 5);
}

int main() {
    return test_results();
}