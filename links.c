#include <stdio.h>
#include <stdlib.h>

#include "links.h"

void cover(_links *c){
    _links *i, *j;
    c->R->L = c->L;                                          // Line 15
    c->L->R = c->R;                                          // Line 15

    for ( i = c->D ; i != c ; i = i->D ){                    // Line 16
        for ( j = i->R ; j != i ; j = j->R){                 // Line 17
            j->D->U = j->U;                                  // Line 18
            j->U->D = j->D;                                  // Line 18
            j->C->size -= 1;                                 // Line 19
        }
    }

    return;
}

void uncover(_links *c){
    _links *i, *j;

    for ( i = c->U ; i != c ; i = i->U ) {        // Line 20
        for ( j = i->L ; j != i ; j = j->L ){     // Line 21
            j->C->size += 1;                      // Line 22
            j->D->U = j;                          // Line 23
            j->U->D = j;                          // Line 23
        }
    }
    c->R->L = c;                                  // Line 24
    c->L->R = c;                                  // Line 24

    return;
}

void knuths_magic(_links *h, int k, _ans *O){
    _links *c;
    _links *j;
    _links *r;

    if ( k != 666) {
        _links *zz = h->R;
        while ( zz != h ){
            zz = zz->R;
        }

    }

    if ( h->R == h ) {                          // Line 1
        printf("Solved\n");                     // Line 1

        return;                                 // Line 1
    }                                           // Line 1

    c = h->R; // Chose a colum object           // Line 2

    cover(c);                                   // Line 3

    _ans *tt = (_ans*) malloc ( sizeof(_ans) ); // Storing the anserws
    _ans *aux = O;                              //
    while (aux->next != NULL) aux = aux->next;  //
    aux->next = tt;                             //
    tt ->next = NULL;                           //
    tt ->O    = NULL;                           //

    for ( r = c->D ; r != c ; r = r->D ){       // Line 4
        tt->O = r;                              // Line 5

        for( j = r->R ; j != r ; j = j->R){     // Line 6
            cover(j->C);                        // Line 7
        }

        knuths_magic(h, k + 1, O);              // Line 8

        r = tt->O;                              // Line 9
        c =  r->C;                              // Line 9

        for (j = r->L ; j != r ; j = j->L){     // Line 10
            uncover(j->C);                      // Line 11
        }
    }

    uncover(c);                                 // Line 12

    aux = O;
    while (aux->next->next != NULL && aux->next != NULL){
        aux = aux->next;
    }

    aux->next = NULL;
    free(tt);

    return;
}

_links *init_torus(){
    _links *p = (_links*) malloc ( sizeof(_links) );

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

void build_links_for_dancing(_links *h, int *m, int x, int y){
    int i, j;
    _links *a;
    _links *first;
    _links *t;

    for ( j = 0 ; j < y ; j++ ){
        for ( i = 0, a = h->R, first = NULL ; i < x ; i++, a = a->R){
            if ( m[i + j*x] == 1){
                for ( t = a->D; t != a; t = t->D );

                _links *new = (_links*) malloc ( sizeof(_links) );

                _links *tt = t->D;
                t->D   = new;
                new->D = tt;
                tt->U  = new;
                new->U = t;
                new->R = t;
                new->C = a;
                new->n = i;

                if ( first == NULL ){
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

void insert_col_header(_links *h){
    _links *new = (_links*) malloc ( sizeof(_links) );
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

void insert_row_header(_links *h){
    _links *new = (_links*) malloc ( sizeof(_links) );
    _links *a;

    a         = h->U;
    h->U      = new;
    a->D      = new;
    new->L    = NULL;
    new->R    = NULL;
    new->D    = h;
    new->U    = a;
    new->C    = h;
    new->size = 0;
    new->n    = a->n + 1;
    new->name = NULL;

    return;
}

