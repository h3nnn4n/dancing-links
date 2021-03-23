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

#include <assert.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "dlx_solver.h"
#include "generators/sudoku.h"
#include "links.h"
#include "parsers/sudoku.h"

struct option long_options[] = {{"quiet", no_argument, &quiet, 1},
                                {"single-solution", no_argument, &single_solution, 1},
                                {"multiple-solutions", no_argument, &single_solution, 0},
                                {"file", required_argument, 0, 'f'},
                                {"sudoku-gen", required_argument, 0, 's'},
                                {"sudoku-parse", required_argument, 0, 't'},
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

            case 's': {
                assert(optarg != NULL);
                size_t arg_len      = strlen(optarg) + 2;
                char * sudoku_input = malloc(sizeof(char) * arg_len);
                // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
                memcpy(sudoku_input, optarg, sizeof(char) * (strlen(optarg) + 1));

                sudoku_generator(sudoku_input);

                free(sudoku_input);
            }
                return EXIT_SUCCESS;

            case 't': {
                assert(optarg != NULL);
                size_t arg_len      = strlen(optarg) + 2;
                char * sudoku_input = malloc(sizeof(char) * arg_len);
                // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
                memcpy(sudoku_input, optarg, sizeof(char) * (strlen(optarg) + 1));

                sudoku_parse(sudoku_input);

                free(sudoku_input);
            }
                return EXIT_SUCCESS;
            case '?':
                return EXIT_FAILURE;
                /* getopt_long already printed an error message. */
                break;

            default: abort();
        }
    }

    dlx_solver();

    return EXIT_SUCCESS;
}
