#include <stdio.h>

// Funzione per contare le occorrenze di un elemento in un vettore
int conta_occorrenze(int *a, int N, int elem) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (a[i] == elem) {
            count++;
        }
    }
    return count;
}

// Funzione ricorsiva per trovare l'elemento maggioritario
int maggioritario_ric(int *a, int start, int end) {
    // Caso base: se il sottovettore ha un solo elemento
    if (start == end) {
        return a[start];
    }

    // Dividi il vettore a metà
    int mid = (start + end) / 2;

    // Trova l'elemento maggioritario nella prima metà
    int maggioritario_sx = maggioritario_ric(a, start, mid);
    // Trova l'elemento maggioritario nella seconda metà
    int maggioritario_dx = maggioritario_ric(a, mid + 1, end);

    // Se entrambi hanno lo stesso maggioritario, restituiscilo
    if (maggioritario_sx == maggioritario_dx) {
        return maggioritario_sx;
    }

    // Altrimenti conta le occorrenze di entrambi i maggioritari
    int count_sx = conta_occorrenze(a, end - start + 1, maggioritario_sx);
    int count_dx = conta_occorrenze(a, end - start + 1, maggioritario_dx);

    // Restituisci quello che ha più occorrenze, se è maggioritario
    int N = end - start + 1;
    if (count_sx > N / 2) {
        return maggioritario_sx;
    } else if (count_dx > N / 2) {
        return maggioritario_dx;
    } else {
        return -1; // Nessun elemento maggioritario
    }
}

// Funzione principale che restituisce l'elemento maggioritario
int majority(int *a, int N) {
    if (N == 0) {
        return -1;
    }
    return maggioritario_ric(a, 0, N - 1);
}

int main() {
    int vet1[] = {3, 3, 9, 4, 3, 5, 3};
    int N1 = 7;
    int result1 = majority(vet1, N1);
    printf("Maggioritario (vet1): %d\n", result1); // Output: 3

    int vet2[] = {0, 1, 0, 2, 3, 4, 0, 5};
    int N2 = 8;
    int result2 = majority(vet2, N2);
    printf("Maggioritario (vet2): %d\n", result2); // Output: -1

    return 0;
}
