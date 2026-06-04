#include "../claim.h"

describe("skipped and pending tests")

should ("skip this") {
    skip("this test will be skipped");
}

should ("finish this later") {
    pending();
}

should ("also finish this later") {
    pending();
}

int main() {
    return test_results();
}