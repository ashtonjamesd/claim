#include "../claim.h"

describe("expect and refute")

should ("test the truth") {
    expect(true);
}

should ("test another truth") {
    refute(false);
}

int main() {
    return test_results();
}