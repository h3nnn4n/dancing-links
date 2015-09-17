#ifndef __DANCING_LINKS
#define __DANCING_LINKS

typedef struct __links {
    struct __links *L;
    struct __links *R;
    struct __links *U;
    struct __links *D;
    struct __links *C;

    int  n;
    int  size;
    char *name;
} _links;

typedef struct __ans {
    struct __ans   *next;
    struct __links *O;
} _ans;

// Initializes and empty structure
_links *init_torus();

// Inserts a column header into the Doubly linked circular list of columns
void    insert_col_header(_links *);

// Reads an matrix m and builds the structure that Knuth's described in his paper (Dancing Links)
void    build_links_for_dancing(_links *h, int **m, int x, int y);

// Knuth's dancing links(DLX) implementation. See Knuth's paper on page 5
void    dancing_links(_links *, int, _ans *);

// Covers a column. This process is described on Knuth's paper page 6.
void    cover(_links *c);

// Uncovers a column. This process is described on Knuth's paper page 6.
void    uncover(_links *c);

#endif
