#ifndef __DANCING_LINKS
#define __DANCING_LINKS

// If __USE_HEURISTIC is set an heristic will be used to select which column to
// explore first. Otherwise it will use the leftmost uncovered column. The
// heuristic consists of exploring first the node that lead to the fewest
// branchs. This process is explained on Knuth's paper at page 6.
#define __USE_HEURISTIC

typedef struct __links {
    struct __links *L;
    struct __links *R;
    struct __links *U;
    struct __links *D;
    struct __links *C;

    int   n;
    int   size;
    char *name;
} _links;

typedef struct __ans {
    struct __ans *  next;
    struct __links *O;
} _ans;

extern unsigned long branchs;
extern unsigned long solutions_found;

// Initializes and empty structure
_links *init_torus();

// Inserts a column header into the Doubly linked circular list of columns
void insert_col_header(_links *);

// Reads an matrix m and builds the structure that Knuth's described in his
// paper (Dancing Links)
void build_links_for_dancing(_links *h, int **m, int x, int y);

// Knuth's dancing links(DLX) implementation. See Knuth's paper on page 5
void dancing_links(_links *, int, _ans *, int n);

// Covers a column. This process is described on Knuth's paper page 6.
void cover(_links *c);

// Uncovers a column. This process is described on Knuth's paper page 6.
void uncover(_links *c);

#endif
