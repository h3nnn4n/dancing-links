#include <stdio.h>
#include <stdlib.h>

#include "links.h"

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
    _links *a, *b;

    for ( j = 0, b = h->D ; j < x ; j++, b = b->D ){
        _links *ta, *tb;
        ta = NULL;
        for ( i = 0, a = h->R ; i < y ; i++, a = a->R ){
            if ( m[i * x + j] == 1){
                _links *t1, *t2;
                _links *new = (_links*) malloc ( sizeof(_links) );
                t1 = a;
                t2 = b;

                while ( t1->D != NULL ){
                    t1 = t1->D;
                } 

                while ( t2->R != NULL ){
                    t2 = t2->R;
                } 

                t1->D    = new;
                t2->R    = new;
                new->D   = NULL;
                new->R   = NULL;
                new->U   = t1;
                new->C   = a;
                new->n   = 1;
                ta       = new;
            }
        }
        tb = ta;
        while ( tb->L != NULL ){
            tb = tb->L;
        }
        tb->L = ta;
        ta->R = tb;
    }

    for ( i = 0, a = h->R ; i < y ; i++, a = a->R ){
        _links *t;
        t = a;

        while ( t->D != NULL ){
            t = t->D;
        }
        
        t->D = a;
        a->U = t;
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
    new->D    = NULL;
    new->U    = NULL;
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

