#include <stdio.h>
#include <stdlib.h>

#define FILENAME "att.txt"

typedef struct {
    int start;
    int end;
} att;

int durata(att a);
int compare(void *a, void *b);
void attSelRec(int index, int N, att *v, int *currentSet, int currentDurata, int *bestSet, int *bestDurata, int *bestSize, int currentSize);
void attSel(int N, att *v);
void leggiDaFile(att **v, int *N);

int main() {
    att *v;
    int N;

    leggiDaFile(&v, &N);
    attSel(N, v);
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

void attSel(int N, att *v) {
    qsort(v, N, sizeof(att), compare);

    int *currentSet = (int *)malloc(N * sizeof(int));
    int *bestSet = (int *)malloc(N * sizeof(int));
    int bestDurata = 0, bestSize = 0;

    attSelRec(0, N, v, currentSet, 0, bestSet, &bestDurata, &bestSize, 0);

    printf("Sottoinsieme massimo di attività compatibili:\n");
    for (int i = 0; i < bestSize; i++) {
        printf("(%d, %d) ", v[bestSet[i]].start, v[bestSet[i]].end);
    }
    printf("\nSomma delle durate: %d\n", bestDurata);

    free(currentSet);
    free(bestSet);
}

void attSelRec(int index, int N, att *v, int *currentSet, int currentDurata, int *bestSet, int *bestDurata, int *bestSize, int currentSize) {
    if (index == N) {
        if (currentDurata > *bestDurata) {
            *bestDurata = currentDurata;
            *bestSize = currentSize;
            for (int i = 0; i < currentSize; i++) {
                bestSet[i] = currentSet[i];
            }
        }
        return;
    }

    if (currentSize == 0 || v[currentSet[currentSize - 1]].end <= v[index].start) {
        currentSet[currentSize] = index;
        attSelRec(index + 1, N, v, currentSet, currentDurata + durata(v[index]), bestSet, bestDurata, bestSize, currentSize + 1);
    }

    attSelRec(index + 1, N, v, currentSet, currentDurata, bestSet, bestDurata, bestSize, currentSize);
}

int compare(void *a, void *b) {
    att *att1 = (att *)a;
    att *att2 = (att *)b;
    return att1->end - att2->end;
}

int durata(att a) {
    return a.end - a.start;
}