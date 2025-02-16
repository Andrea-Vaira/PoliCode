#include <stdlib.h>
#include <string.h>
#include "tabellaSimboli.h"

struct tabellaSimboli {char **a; int maxN; int N;};


ST STinit(int maxN) {
    ST st;
    st = malloc(sizeof (*st));
    st->a = calloc(maxN, sizeof(char *));
    st->maxN = maxN;
    st->N = 0;
    return st;
}

void STfree(ST st) {
    int i;
    if (st==NULL)
        return;
    for (i=0; i<st->N; i++)
        if (st->a[i] != NULL)
            free(st->a[i]);
    free(st->a);
    free(st);
}

int STsize(ST st) {
    return st->N;
}

void STinsert(ST st, char *str, int i) {
    if (i >= st->maxN) {
        st->a = realloc(st->a, (2*st->maxN)*sizeof(char *));
        if (st->a == NULL)
            return;
        st->maxN = 2*st->maxN;
    }
    st->a[i] = strdup(str);
    st->N++;
}

int STsearch(ST st, char *str) {
    int i;
    for (i = 0; i  < st->N; i++)
        if (st->a[i]!=NULL && strcmp(str, st->a[i])==0)
            return i;
    return -1;
}

char *STsearchByIndex(ST st, int i){
    if (i < 0 || i >= st->N)
        return NULL;
    return (st->a[i]);
}