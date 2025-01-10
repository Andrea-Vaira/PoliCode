#include <stdio.h>
#include <string.h>

#define ZAFFIRO 0
#define RUBINO  1
#define TOPAZIO 2
#define SMERALDO 3

int regole[4][4] = {
        // z  r  t  s
        {1, 1, 0, 0}, // z: z → z, r
        {0, 0, 1, 1}, // r: r → t, s
        {1, 1, 0, 0}, // t: t → z, r
        {0, 0, 1, 1}  // s: s → t, s
};

int miglior_lunghezza = 0;
char miglior_collana[1000];

void esplora(int z, int r, int t, int s, char* collana, int lunghezza, int ultima);

int main() {
    int z, r, t, s;
    printf("Inserisci il numero di Zaffiri, Rubini, Topazi e Smeraldi: ");
    scanf("%d %d %d %d", &z, &r, &t, &s);

    char collana_iniziale[1000] = "";
    esplora(z, r, t, s, collana_iniziale, 0, -1);

    printf("Lunghezza massima: %d\n", miglior_lunghezza);
    printf("Collana: %s\n", miglior_collana);

    return 0;
}

void esplora(int z, int r, int t, int s, char* collana, int lunghezza, int ultima) {
    if (lunghezza > miglior_lunghezza) {
        miglior_lunghezza = lunghezza;
        strcpy(miglior_collana, collana);
    }

    if (z > 0 && (ultima == -1 || regole[ultima][ZAFFIRO])) {
        char nuova_collana[1000];
        sprintf(nuova_collana, "%sZ", collana);
        esplora(z - 1, r, t, s, nuova_collana, lunghezza + 1, ZAFFIRO);
    }
    if (r > 0 && (ultima == -1 || regole[ultima][RUBINO])) {
        char nuova_collana[1000];
        sprintf(nuova_collana, "%sR", collana);
        esplora(z, r - 1, t, s, nuova_collana, lunghezza + 1, RUBINO);
    }
    if (t > 0 && (ultima == -1 || regole[ultima][TOPAZIO])) {
        char nuova_collana[1000];
        sprintf(nuova_collana, "%sT", collana);
        esplora(z, r, t - 1, s, nuova_collana, lunghezza + 1, TOPAZIO);
    }
    if (s > 0 && (ultima == -1 || regole[ultima][SMERALDO])) {
        char nuova_collana[1000];
        sprintf(nuova_collana, "%sS", collana);
        esplora(z, r, t, s - 1, nuova_collana, lunghezza + 1, SMERALDO);
    }
}