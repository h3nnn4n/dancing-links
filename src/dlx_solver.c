#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "links.h"

void dlx_solver() {
    _links *m;
    int     x = 0;
    int     y = 0;
    int     n = 0;

    branchs         = 0;
    solutions_found = 0;

    fscanf(stdin, "%d", &y);  // NOLINT(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
    fscanf(stdin, "%d", &x);  // NOLINT(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
    fscanf(stdin, "%d", &n);  // NOLINT(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)

    int **set = (int **)malloc(sizeof(int *) * y);

    m = init_torus();

    for (int i = 0; i < y; i++) {
        insert_col_header(m);
        set[i] = (int *)malloc(sizeof(int) * x);
    }

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
            fscanf(stdin, "%d", &set[j][i]);
        }
    }

    if (!quiet) {
        puts("--------------------");
        printf("Building in-memory model\n");
    }

    build_links_for_dancing(m, set, x, y);

    if (!quiet) {
        puts("--------------------");
        printf("Starting solve process\n");
        puts("--------------------");
    }

    _ans *O = (_ans *)malloc(sizeof(_ans));
    dancing_links(m, 0, O, n);

    if (!quiet) {
        puts("--------------------");
    }

    free_set(set, y);
    free_ans(O);
    free_links(m);
}
