#include <stdio.h>
#include <string.h>

// Regole di transizione: matrice booleana per le regole
int regole[4][4] = {
        // z  r  t  s
        {1, 1, 0, 0}, // z: z → z, r
        {0, 0, 1, 1}, // r: r → t, s
        {1, 1, 0, 0}, // t: t → z, r
        {0, 0, 1, 1}  // s: s → t, s
};

// Indici per rappresentare i tipi di pietre
#define ZAFFIRO 0
#define RUBINO  1
#define TOPAZIO 2
#define SMERALDO 3

// Variabili globali per la soluzione ottimale
int miglior_lunghezza = 0;
char miglior_collana[1000];

// Funzione ricorsiva per esplorare tutte le collane valide
void esplora(int z, int r, int t, int s, char* collana, int lunghezza, int ultima) {
    // Aggiorna la soluzione migliore se necessario
    if (lunghezza > miglior_lunghezza) {
        miglior_lunghezza = lunghezza;
        strcpy(miglior_collana, collana);
    }

    // Prova ad aggiungere ogni pietra possibile
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

int main() {
    // Input: numero di pietre disponibili
    int z, r, t, s;
    printf("Inserisci il numero di Zaffiri, Rubini, Topazi e Smeraldi: ");
    scanf("%d %d %d %d", &z, &r, &t, &s);

    // Avvia l'esplorazione ricorsiva
    char collana_iniziale[1000] = "";
    esplora(z, r, t, s, collana_iniziale, 0, -1);

    // Stampa la soluzione ottimale
    printf("Lunghezza massima: %d\n", miglior_lunghezza);
    printf("Collana: %s\n", miglior_collana);

    return 0;
}
