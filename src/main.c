/************************************************************************************
 *                                                                                  *
 *     Copyright (C) 2015  Renan S. Silva                                           *
 *                                                                                  *
 *     This program is free software: you can redistribute it and/or modify         *
 *     it under the terms of the GNU General Public License as published by         *
 *     the Free Software Foundation, either version 3 of the License, or            *
 *     (at your option) any later version.                                          *
 *                                                                                  *
 *     This program is distributed in the hope that it will be useful,              *
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of               *
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                *
 *     GNU General Public License for more details.                                 *
 *                                                                                  *
 *     You should have received a copy of the GNU General Public License            *
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.        *
 *                                                                                  *
 ***********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "links.h"
#include "config.h"

struct option long_options[] = {
    {"quiet", no_argument, &quiet, 1},
    {"single-solution", no_argument, &single_solution, 1},
    {"multiple-solutions", no_argument, &single_solution, 0},
    {"file", required_argument, 0, 'f'},
    {0, 0, 0, 0}};

int main(int argc, char **argv){

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
                // TODO: Read from file
                break;

            case '?':
                /* getopt_long already printed an error message. */
                break;

            default: abort();
        }
    }

    _links *m;
    int **set;
    int x, y, i, j, n;

    branchs = 0;
    solutions_found = 0;

    fscanf(stdin, "%d", &y);
    fscanf(stdin, "%d", &x);
    fscanf(stdin, "%d", &n);

    set = (int**) malloc ( sizeof(int*) * y );

    m = init_torus();

    for ( i = 0 ; i < y ; i++){
        insert_col_header(m);
        set[i] = (int*) malloc ( sizeof(int) * x );
    }

    for ( i = 0 ; i < x ; i++){
        for ( j = 0 ; j < y ; j++){
            fscanf(stdin, "%d", &set[j][i]);
        }
    }

    if (!quiet) puts("--------------------");

    if (!quiet) printf("Building in-memory model\n");
    build_links_for_dancing(m, set, x, y);

    if (!quiet) puts("--------------------");
    if (!quiet) printf("Starting solve process\n");
    if (!quiet) puts("--------------------");

    _ans *O = (_ans*) malloc ( sizeof(_ans) );
    dancing_links(m, 0, O, n);

    if (!quiet) puts("--------------------");

    return EXIT_SUCCESS;
}
