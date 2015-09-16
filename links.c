#include <stdio.h>
#include <stdlib.h>

#include "links.h"

void knuths_magic(_links *h, int k, _ans *O){
    _links *c;
    _links *i;
    _links *j;
    _links *ii;
    _links *jj;
    _links *r;

    /*printf("k = %d | \t %p -> %p -> %p\n", k, h, h->R, h->R->R);*/
    if ( k != 666) {
        _links *zz = h->R;
        printf("k = %d | \t %p -> ", k, h);
        while ( zz != h ){
            printf(" %p -> ", zz);
            zz = zz->R;
        }
        printf(" %p \n", zz);

    }

    if ( h->R == h ) {                      // Line 1
        printf("Solved\n");                 // Line 1
        return;                             // Line 1
    }                                       // Line 1

    c = h->R; // Chose a colum object       // Line 2

    // Cover column                         // Line 3
    c->R->L = c->L;                         // Line 15
    c->L->R = c->R;                         // Line 15

    i = c->D;                               // Line 16

    while ( i != c ){                       // Line 16
        j = i->R;                           // Line 17
        while ( j != i ){                   // Line 17
            j->D->U = j->U;                 // Line 18
            j->U->D = j->D;                 // Line 18
            j->C->size -= 1;                // Line 19

            j = j->R;                       // Line 17
        }
        i = i->D;                           // Line 16
    }
    // End column covering

    _ans *tt = (_ans*) malloc ( sizeof(_ans) ); // Storing the anserws
    _ans *aux = O;                              //
    while (aux->next != NULL) aux = aux->next;  //
    aux->next = tt;                             //
    tt ->next = NULL;                           //
    tt ->O    = NULL;                           //

    r = c->D;                               // Line 4
    while ( r != c ){                       // Line 4
        tt->O = r;                          // Line 5
        j = r->R;                           // Line 6
        while ( j != r ){                   // Line 6
            // Cover column                 // Line 7
            c->R->L = c->L;                 // Line 15
            c->L->R = c->R;                 // Line 15

            ii = c->D;                       // Line 16

            while ( ii != c ){               // Line 16
                jj = ii->R;                   // Line 17
                while ( jj != ii ){           // Line 17
                    jj->D->U = jj->U;         // Line 18
                    jj->U->D = jj->D;         // Line 18
                    jj->C->size -= 1;        // Line 19

                    jj = jj->R;               // Line 17
                }

                ii = ii->D;                   // Line 16
            }
            // End column covering
            j = j->R;
        }

        /*printf(" going to %d\n", c->C->n);*/
        knuths_magic(h, k + 1, O);      // Line 8

        r = tt->O;                      // Line 9
        c =  r->C;                      // Line 9

        j = r->L;                       // Line 10
        while ( j != r ){               // Line 10

            // Uncover                  // Line 11
            ii = c->U;                  // Line 20
            while ( ii != c ){          // Line 20
                jj = ii->L;             // Line 21
                while ( jj != ii ){     // Line 21
                        jj->C->size += 1;  // Line 22
                        jj->D->U = jj;     // Line 23
                        jj->U->D = jj;     // Line 23

                    jj = jj->L;         // Line 21
                }

                ii = ii->U;             // Line 20
            }
            c->R->L = c;                // Line 24
            c->L->R = c;                // Line 24
            // end uncoverig

            j = j->L;                   // Line 10
        }
        r = r->D;                           // Line 4
    }

    // Uncover                              // Line 11
    ii = c->U;                              // Line 20
    while ( ii != c ){                      // Line 20
        jj = ii->L;                         // Line 21
        while ( jj != ii ){                 // Line 21
            jj->C->size += 1;               // Line 22
            jj->D->U = jj;                  // Line 23
            jj->U->D = jj;                  // Line 23
            jj = jj->L;                     // Line 21
        }
        ii = ii->U;                         // Line 20
    }
    c->R->L = c;                            // Line 24
    c->L->R = c;                            // Line 24
    // end uncoverig

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
                new->L   = t2;
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

    b = h->D;

    while ( b != h ){
        b->L->R = b->R;
        b->R->L = b->L;
        b = b->D;
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

