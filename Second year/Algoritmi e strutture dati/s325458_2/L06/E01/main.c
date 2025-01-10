#include <stdio.h>
#include <stdlib.h>

#define FILENAME "att.txt"

typedef struct {
    int start;
    int end;
} att;

int durata(att a);
int compare(void *a, void *b);
int trovaUltimaAttivitaCompatibile(att *v, int i);
void attSelDP(int N, att *v);
void leggiDaFile(att **v, int *N);

int main() {
    att *v;
    int N;

    leggiDaFile(&v, &N);
    attSelDP(N, v);

    return 0;
}

void leggiDaFile(att **v, int *N) {
    FILE *file = fopen(FILENAME, "r");
    fscanf(file, "%d", N); // Legge il numero di attività

    *v = (att *)malloc(*(N) * sizeof(att));
    for (int i = 0; i < *(N); i++) {
        fscanf(file, "%d %d", &(*v)[i].start, &(*v)[i].end);
    }

    fclose(file);
}
void attSelDP(int N, att *v) {
    qsort(v, N, sizeof(att), compare);

    int *dp = (int *)malloc(N * sizeof(int));
    int *prev = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        dp[i] = 0;
        prev[i] = -1;
    }

    // Calcolo della soluzione ottima usando programmazione dinamica
    for (int i = 0; i < N; i++) {
        int durataCorrente = durata(v[i]);
        int compatibile = trovaUltimaAttivitaCompatibile(v, i);

        // Calcolare dp[i]
        if (compatibile != -1) {
            dp[i] = durataCorrente + dp[compatibile];
        } else {
            dp[i] = durataCorrente;
        }

        // Aggiornare prev per tracciare la ricostruzione
        if (i > 0 && dp[i - 1] > dp[i]) {
            dp[i] = dp[i - 1];
            prev[i] = prev[i - 1];
        } else if (compatibile != -1) {
            prev[i] = compatibile;
        }
    }

    printf("Somma massima delle durate: %d\n", dp[N - 1]);

    printf("Sottoinsieme massimo di attività compatibili:\n");
    int i = N - 1;
    while (i >= 0) {
        if (prev[i] == -1 || dp[i] != dp[prev[i]]) {
            printf("(%d, %d) ", v[i].start, v[i].end);
        }
        i = prev[i];
    }
    printf("\n");

    free(dp);
    free(prev);
}
int trovaUltimaAttivitaCompatibile(att *v, int i) {
    for (int j = i - 1; j >= 0; j--) {
        if (v[j].end <= v[i].start) {
            return j;
        }
    }
    return -1;
}
int durata(att a) {
    return a.end - a.start;
}
int compare(void *a, void *b) {
    att *att1 = (att *)a;
    att *att2 = (att *)b;
    return att1->end - att2->end;
}