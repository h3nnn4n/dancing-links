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

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "links.h"

struct option long_options[] = {{"quiet", no_argument, &quiet, 1},
                                {"single-solution", no_argument, &single_solution, 1},
                                {"multiple-solutions", no_argument, &single_solution, 0},
                                {"file", required_argument, 0, 'f'},
                                {0, 0, 0, 0}};

int main(int argc, char **argv) {
    while (1) {
        int c;
        int option_index = 0;

        c = getopt_long(argc, argv, "abc:d:f:", long_options, &option_index);

        if (c == -1)
            break;

        switch (c) {
            case 0:
                if (long_options[option_index].flag != 0)
                    break;

                printf("option %s", long_options[option_index].name);
                if (optarg)
                    printf(" with arg %s", optarg);

                printf("\n");
                break;

            case 'f':
                // TODO(h3nnn4n): Read from file
                break;

            case '?':
                /* getopt_long already printed an error message. */
                break;

            default: abort();
        }
    }

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

    return EXIT_SUCCESS;
}
