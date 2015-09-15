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

#include "links.h"

int main(){
    _links *m;
    int set[42] = { 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1};

    m = init_torus();

    insert_col_header(m);
    insert_col_header(m);
    insert_col_header(m);
    insert_col_header(m);
    insert_col_header(m);
    insert_col_header(m);

    insert_row_header(m);
    insert_row_header(m);
    insert_row_header(m);
    insert_row_header(m);
    insert_row_header(m);
    insert_row_header(m);
    insert_row_header(m);

    build_links_for_dancing(m, set, 7, 6);

    puts("--------------------");

    _links *t;

    t = m->R;

    while ( t != m ) {
        printf("%p -> %p = %d\n", t, t->R, t->n);
        t = t->R;
    }

    puts("--------------------");

    t = m->D;

    while ( t != m ) {
        printf("%p -> %p = %d\n", t, t->D, t->n);
        t = t->D;
    }

    puts("--------------------");

    _links *a, *b;

    a = m->R;

    while ( a != m ){
        b = a->D;
        while ( b != a ){
            printf("%d ", 1);
            b = b->D;
        }
        a = a->R;
        puts("");
    }


    return EXIT_SUCCESS;
}
