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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "links.h"

uint64_t branchs;
uint64_t solutions_found;

void cover(_links *c) {
    _links *i, *j;
    c->R->L = c->L;  // Line 15
    c->L->R = c->R;  // Line 15

    branchs++;

    for (i = c->D; i != c; i = i->D) {      // Line 16
        for (j = i->R; j != i; j = j->R) {  // Line 17
            j->D->U = j->U;                 // Line 18
            j->U->D = j->D;                 // Line 18
            j->C->size -= 1;                // Line 19
        }
    }

    return;
}

void uncover(_links *c) {
    _links *i, *j;

    for (i = c->U; i != c; i = i->U) {      // Line 20
        for (j = i->L; j != i; j = j->L) {  // Line 21
            j->C->size += 1;                // Line 22
            j->D->U = j;                    // Line 23
            j->U->D = j;                    // Line 23
        }
    }
    c->R->L = c;  // Line 24
    c->L->R = c;  // Line 24

    return;
}

void dancing_links(_links *h, int k, _ans *ans, int n) {
    _links *c;
    _links *j;
    _links *r;
    int     s;

    if (h->R == h) {  // Line 1
        solutions_found++;
        first_solution_found = 1;

        if (quiet) {
            return;
        }

        printf("Solved. Took %lu steps\n", branchs);  // Line 1
        printf("Found %lu solutions\n", solutions_found);

        int     w;
        _ans *  ans_tmp;
        _links *p;
        for (ans_tmp = ans->next; ans_tmp->next != NULL; ans_tmp = ans_tmp->next) {
            for (p = ans_tmp->O, w = 0; (p != ans_tmp->O || w == 0) && p->C->n > n; p = p->R, w++) {
            }
            c = p;
            for (w = 0; p != c || w == 0; p = p->R, w++) {
                printf("%2.d ", p->C->n > n ? p->C->n - n : p->C->n);
            }
            puts("");
        }

        if (ans_tmp->next == NULL) {
            for (p = ans_tmp->O, w = 0; (p != ans_tmp->O || w == 0) && p->C->n > n; p = p->R, w++) {
            }
            c = p;
            for (w = 0; p != c || w == 0; p = p->R, w++) {
                printf("%2.d ", p->C->n > n ? p->C->n - n : p->C->n);
            }
            puts("");
        }

        puts("--------------------");

        return;  // Line 1
    }            // Line 1

    c = h->R;  // Chose a colum object           // Line 2
    s = c->size;

#ifdef __USE_HEURISTIC
    for (j = h->R; j != h; j = j->R) {  // Line 13
        if (j->size < s) {              // Line 14
            c = j;                      // Line 14
            s = j->size;                // Line 14
        }                               // Line 14
    }                                   // Line 13
#endif

    cover(c);  // Line 3

    _ans *tt  = (_ans *)malloc(sizeof(_ans));  // Storing the anserws
    _ans *aux = ans;                           //
    while (aux->next != NULL)
        aux = aux->next;  //
    aux->next = tt;       //
    tt->next  = NULL;     //
    tt->O     = NULL;     //

    for (r = c->D; r != c; r = r->D) {  // Line 4
        tt->O = r;                      // Line 5

        for (j = r->R; j != r; j = j->R) {  // Line 6
            cover(j->C);                    // Line 7
        }

        dancing_links(h, k + 1, ans, n);  // Line 8

        r = tt->O;  // Line 9
        c = r->C;   // Line 9

        for (j = r->L; j != r; j = j->L) {  // Line 10
            uncover(j->C);                  // Line 11
        }

        if (single_solution && first_solution_found)
            return;
    }

    uncover(c);  // Line 12

    aux = ans;
    while (aux->next != NULL && aux->next->next != NULL) {
        aux = aux->next;
    }

    aux->next = NULL;
    free(tt);

    return;
}

_links *init_torus() {
    _links *p = (_links *)malloc(sizeof(_links));

    p->L    = p;
    p->R    = p;
    p->U    = p;
    p->D    = p;
    p->C    = p;
    p->size = 0;
    p->n    = 0;
    p->name = NULL;

    return p;
}

void build_links_for_dancing(_links *h, int **m, int x, int y) {
    int     i, j;
    _links *a;
    _links *first;
    _links *t;

    for (j = 0; j < x; j++) {
        for (i = 0, a = h->R, first = NULL; i < y; i++, a = a->R) {
            if (m[i][j] == 1) {
                for (t = a->D; t != a; t = t->D) {
                }

                _links *new = (_links *)malloc(sizeof(_links));

                _links *tt = t->D;
                t->D       = new;
                new->D     = tt;
                tt->U      = new;
                new->U     = t;
                new->R     = t;
                new->C     = a;
                new->n     = i;

                if (first == NULL) {
                    new->R = new;
                    new->L = new;
                    first  = new;
                } else {
                    tt       = first->L;
                    first->L = new;
                    new->L   = tt;
                    tt->R    = new;
                    new->R   = first;
                }
            }
        }
    }

    return;
}

void insert_col_header(_links *h) {
    _links *new = (_links *)malloc(sizeof(_links));
    _links *a;

    a         = h->L;
    h->L      = new;
    a->R      = new;
    new->L    = a;
    new->R    = h;
    new->D    = new;
    new->U    = new;
    new->C    = h;
    new->size = 0;
    new->n    = a->n + 1;
    new->name = NULL;

    return;
}
