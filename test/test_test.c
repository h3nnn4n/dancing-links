#include <unity.h>

void test_test() { TEST_PASS(); }

void setUp() {}
void tearDown() {}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_test);

    return UNITY_END();
}
