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
    int **set;
    int x, y, i, j, n;

    extern unsigned long int branchs;
    extern unsigned long int solutions_found;

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

    puts("--------------------");

    build_links_for_dancing(m, set, x, y);

    puts("--------------------");
    _ans *O = (_ans*) malloc ( sizeof(_ans) );
    dancing_links(m, 0, O, n);
    puts("--------------------");

    return EXIT_SUCCESS;
}
