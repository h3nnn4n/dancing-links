/*
 * Copyright (C) 2015,2021  h3nnn4n, aka Renan S. Silva
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
