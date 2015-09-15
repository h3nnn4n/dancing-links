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

_links *init_torus();
void    insert_col_header(_links *);
void    insert_row_header(_links *);
void    build_links_for_dancing(_links *h, int *m, int x, int y);

#endif
