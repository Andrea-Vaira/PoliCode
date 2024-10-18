#include <stdio.h>
#include <stdlib.h>

int** malloc2dR(int nr, int nc) {
    int **mat = (int**) malloc(nr * sizeof(int*));
    for (int i = 0; i < nr; i++) {
        mat[i] = (int*) malloc(nc * sizeof(int));
    }
    return mat;
}

void malloc2dP(int ***mat, int nr, int nc) {
    *mat = (int**) malloc(nr * sizeof(int*));
    for (int i = 0; i < nr; i++) {
        (*mat)[i] = (int*) malloc(nc * sizeof(int));
    }
}

void separa(int **mat, int nr, int nc, int **bianchi, int **neri, int *nBianchi, int *nNeri) {
    *nBianchi = 0;
    *nNeri = 0;

    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            if ((i + j) % 2 == 0) {
                (*nBianchi)++;
            } else {
                (*nNeri)++;
            }
        }
    }

    *bianchi = (int*) malloc((*nBianchi) * sizeof(int));
    *neri = (int*) malloc((*nNeri) * sizeof(int));

    int indiceBianchi = 0, indiceNeri = 0;

    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            if ((i + j) % 2 == 0) {
                (*bianchi)[indiceBianchi] = mat[i][j];
                indiceBianchi++;
            } else {
                (*neri)[indiceNeri] = mat[i][j];
                indiceNeri++;
            }
        }
    }
}

int main() {
    FILE *file = fopen("mat.txt", "r");
    int nr, nc;
    fscanf(file, "%d %d", &nr, &nc);

    int **mat = malloc2dR(nr, nc);

    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            fscanf(file, "%d", &mat[i][j]);
        }
    }
    fclose(file);

    int *bianchi, *neri;
    int nBianchi, nNeri;

    separa(mat, nr, nc, &bianchi, &neri, &nBianchi, &nNeri);

    printf("Celle bianche:\n");
    for (int i = 0; i < nBianchi; i++) {
        printf("%d ", bianchi[i]);
    }
    printf("\n");

    printf("Celle nere:\n");
    for (int i = 0; i < nNeri; i++) {
        printf("%d ", neri[i]);
    }
    printf("\n");

    for (int i = 0; i < nr; i++) {
        free(mat[i]);
    }
    free(mat);

    free(bianchi);
    free(neri);

    return 0;
}
