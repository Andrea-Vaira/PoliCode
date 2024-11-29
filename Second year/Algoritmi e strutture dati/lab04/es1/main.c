#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICI 20
typedef struct {
    int u;
    int v;
} arco;

void leggi_grafo(const char *filename, int *N, int *E, arco archi[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Errore nell'apertura del file");
        return;
    }

    fscanf(file, "%d %d", N, E);

    for (int i = 0; i < *E; i++) {
        fscanf(file, "%d %d", &archi[i].u, &archi[i].v);
    }

    fclose(file);
}

int is_vertex_cover(int N, arco archi[], int E, int subset) {
    for (int i = 0; i < E; i++) {
        int u = archi[i].u;
        int v = archi[i].v;

        // Verifica che almeno uno dei vertici dell'arco sia nel subset
        if (!((subset & (1 << u)) || (subset & (1 << v)))) {
            return 0;
        }
    }
    return 1;
}

void stampa_vertex_cover(int subset, int N) {
    printf("{ ");
    for (int i = 0; i < N; i++) {
        if (subset & (1 << i)) {
            printf("%d ", i);
        }
    }
    printf("}\n");
}

void trova_vertex_covers(int N, arco archi[], int E) {
    int totale_subset = 1 << N;


    printf("Tutti i vertex cover:\n");
    for (int subset = 1; subset < totale_subset; subset++) {
        if (is_vertex_cover(N, archi, E, subset)) {
            stampa_vertex_cover(subset, N);
        }
    }
}

int main() {
    int N, E;
    arco archi[MAX_VERTICI];

    leggi_grafo("grafo.txt", &N, &E, archi);

    trova_vertex_covers(N, archi, E);
    return 0;
}
