#include <stdio.h>
#include <stdlib.h>
#include <unity.h>

#include <generators/sudoku.h>

void test_gen() {
    // The actual testing is made using built in assertions in the function
    FILE *devnull        = fopen("/dev/null", "wt");
    char  sudoku_input[] = "000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    sudoku_generator(devnull, sudoku_input);
    fclose(devnull);
}

void setUp() {}
void tearDown() {}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_gen);

    return UNITY_END();
}
