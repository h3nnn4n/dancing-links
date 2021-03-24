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
#include <string.h>
#include <unity.h>

#include <config.h>
#include <links.h>

void test_single_solution_solve() {
    _links *m;
    int **  set;
    int     x, y, i, j, n;

    single_solution = 1;

    branchs         = 0;
    solutions_found = 0;

    FILE *f = fopen("./samples/5x5_5_pentoI.dat", "rt");

    fscanf(f, "%d", &y);  // NOLINT(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
    fscanf(f, "%d", &x);  // NOLINT(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
    fscanf(f, "%d", &n);  // NOLINT(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)

    set = (int **)malloc(sizeof(int *) * y);

    m = init_torus();

    for (i = 0; i < y; i++) {
        insert_col_header(m);
        set[i] = (int *)malloc(sizeof(int) * x);
    }

    for (i = 0; i < x; i++) {
        for (j = 0; j < y; j++) {
            // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
            fscanf(f, "%d", &set[j][i]);
        }
    }

    fclose(f);

    build_links_for_dancing(m, set, x, y);

    _ans *O = (_ans *)malloc(sizeof(_ans));
    // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
    memset(O, 0, sizeof(_ans));
    dancing_links(m, 0, O, n);

    TEST_ASSERT_EQUAL(solutions_found, 1);
}

void test_multiple_solutions_solve() {
    _links *m;
    int **  set;
    int     x, y, i, j, n;

    single_solution = 0;

    branchs         = 0;
    solutions_found = 0;

    FILE *f = fopen("./samples/5x5_5_pentoI.dat", "rt");

    fscanf(f, "%d", &y);  // NOLINT(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
    fscanf(f, "%d", &x);  // NOLINT(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
    fscanf(f, "%d", &n);  // NOLINT(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)

    set = (int **)malloc(sizeof(int *) * y);

    m = init_torus();

    for (i = 0; i < y; i++) {
        insert_col_header(m);
        set[i] = (int *)malloc(sizeof(int) * x);
    }

    for (i = 0; i < x; i++) {
        for (j = 0; j < y; j++) {
            // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
            fscanf(f, "%d", &set[j][i]);
        }
    }

    fclose(f);

    build_links_for_dancing(m, set, x, y);

    _ans *O = (_ans *)malloc(sizeof(_ans));
    // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
    memset(O, 0, sizeof(_ans));
    dancing_links(m, 0, O, n);

    TEST_ASSERT_EQUAL(solutions_found, 240);
}

void setUp() { quiet = 1; }
void tearDown() {}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_single_solution_solve);
    RUN_TEST(test_multiple_solutions_solve);

    return UNITY_END();
}
