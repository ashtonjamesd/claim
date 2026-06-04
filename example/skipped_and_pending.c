#include "../claim.h"

describe("skipped and pending tests")

should (skip_this) {
    skip("this test will be skipped");
}

should (finish_this_later) {
    pending();
}

should (also_finish_this_later) {
    pending();
}

int main() {
    return test_results();
}