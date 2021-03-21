#include <unity.h>
#include <stdio.h>
#include <stdlib.h>

#include <config.h>
#include <links.h>

void test_single_solution_solve() {
  _links *m;
  int **set;
  int x, y, i, j, n;

  single_solution = 1;

  branchs = 0;
  solutions_found = 0;

  FILE *f = fopen("./samples/5x5_5_pentoI.dat", "rt");

  fscanf(f, "%d", &y);
  fscanf(f, "%d", &x);
  fscanf(f, "%d", &n);

  set = (int **)malloc(sizeof(int *) * y);

  m = init_torus();

  for (i = 0; i < y; i++) {
    insert_col_header(m);
    set[i] = (int *)malloc(sizeof(int) * x);
  }

  TEST_MESSAGE("loadstart");

  for (i = 0; i < x; i++) {
    for (j = 0; j < y; j++) {
      fscanf(f, "%d", &set[j][i]);
    }
  }

  TEST_MESSAGE("load completed");

  fclose(f);

  TEST_MESSAGE("build_links_for_dancing");

  build_links_for_dancing(m, set, x, y);

  TEST_MESSAGE("dancing_links");

  _ans *O = (_ans *)malloc(sizeof(_ans));
  dancing_links(m, 0, O, n);

  TEST_ASSERT_EQUAL(solutions_found, 1);
}

void test_multiple_solutions_solve() {
  _links *m;
  int **set;
  int x, y, i, j, n;

  single_solution = 0;

  branchs = 0;
  solutions_found = 0;

  FILE *f = fopen("./samples/5x5_5_pentoI.dat", "rt");

  fscanf(f, "%d", &y);
  fscanf(f, "%d", &x);
  fscanf(f, "%d", &n);

  set = (int **)malloc(sizeof(int *) * y);

  m = init_torus();

  for (i = 0; i < y; i++) {
    insert_col_header(m);
    set[i] = (int *)malloc(sizeof(int) * x);
  }

  TEST_MESSAGE("loadstart");

  for (i = 0; i < x; i++) {
    for (j = 0; j < y; j++) {
      fscanf(f, "%d", &set[j][i]);
    }
  }

  TEST_MESSAGE("load completed");

  fclose(f);

  TEST_MESSAGE("build_links_for_dancing");

  build_links_for_dancing(m, set, x, y);

  TEST_MESSAGE("dancing_links");

  _ans *O = (_ans *)malloc(sizeof(_ans));
  dancing_links(m, 0, O, n);

  TEST_ASSERT_EQUAL(solutions_found, 240);
}

void setUp() {}
void tearDown() {}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_single_solution_solve);
  RUN_TEST(test_multiple_solutions_solve);

  return UNITY_END();
}
