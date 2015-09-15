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
    new->L    = new;
    new->R    = new;
    new->D    = h;
    new->U    = a;
    new->C    = h;
    new->size = 0;
    new->n    = a->n + 1;
    new->name = NULL;

    return;
}

