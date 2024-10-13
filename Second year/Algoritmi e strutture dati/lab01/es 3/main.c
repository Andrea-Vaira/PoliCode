#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRATTE 1000
#define MAX_STR 31

typedef struct {
    char codice_tratta[MAX_STR];
    char partenza[MAX_STR];
    char destinazione[MAX_STR];
    char data[MAX_STR];       // Formato: YYYY-MM-DD
    char ora_partenza[MAX_STR]; // Formato: HH:MM
    char ora_arrivo[MAX_STR];   // Formato: HH:MM
    int ritardo;          // Minuti di ritardo
} Corsa;

int leggiCorse(const char *filename, Corsa corse[]) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Errore nell'apertura del file.\n");
        return 0;
    }

    int n;
    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%s %s %s %s %s %s %d", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione,
               corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, &corse[i].ritardo);
    }

    fclose(fp);
    return n;
}

// Funzione per stampare le corse su file o video
void stampaCorse(Corsa corse[], int n, const char *filename) {
    FILE *fp = stdout;
    if (filename != NULL) {
        fp = fopen(filename, "w");
        if (fp == NULL) {
            printf("Errore nell'apertura del file.\n");
            return;
        }
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%s %s %s %s %s %s %d\n", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione,
                corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, corse[i].ritardo);
    }

    if (fp != stdout) {
        fclose(fp);
    }
}

// Funzione di confronto per ordinamento per data e ora
int confrontaDataOra(const void *a, const void *b) {
    Corsa *c1 = (Corsa *)a;
    Corsa *c2 = (Corsa *)b;

    int cmp = strcmp(c1->data, c2->data);
    if (cmp == 0) {
        cmp = strcmp(c1->ora_partenza, c2->ora_partenza);
        return cmp;
    }
    return cmp;
}

// Funzione di confronto per ordinamento per codice di tratta
int confrontaCodiceTratta(const void *a, const void *b) {
    return strcmp(((Corsa *)a)->codice_tratta, ((Corsa *)b)->codice_tratta);
}

// Funzione di confronto per ordinamento per stazione di partenza
int confrontaPartenza(const void *a, const void *b) {
    return strcmp(((Corsa *)a)->partenza, ((Corsa *)b)->partenza);
}

// Funzione di confronto per ordinamento per stazione di arrivo
int confrontaDestinazione(const void *a, const void *b) {
    return strcmp(((Corsa *)a)->destinazione, ((Corsa *)b)->destinazione);
}

// Funzione per la ricerca lineare per stazione di partenza (con prefisso)
void ricercaLineare(Corsa corse[], int n, const char *partenza) {
    for (int i = 0; i < n; i++) {
        if (strncmp(corse[i].partenza, partenza, strlen(partenza)) == 0) {
            printf("%s %s %s %s %s %s %d\n", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione,
                   corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, corse[i].ritardo);
        }
    }
}

// Funzione per la ricerca dicotomica per stazione di partenza (con prefisso)
void ricercaDicotomica(Corsa corse[], int n, const char *partenza) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        int cmp = strncmp(corse[m].partenza, partenza, strlen(partenza));
        if (cmp == 0) {
            // Stampa tutte le corse con il prefisso
            int i = m;
            while (i >= 0 && strncmp(corse[i].partenza, partenza, strlen(partenza)) == 0) i--;
            i++;
            while (i < n && strncmp(corse[i].partenza, partenza, strlen(partenza)) == 0) {
                printf("%s %s %s %s %s %s %d\n", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione,
                       corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, corse[i].ritardo);
                i++;
            }
            return;
        } else if (cmp < 0) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    printf("Nessuna corsa trovata.\n");
}

// Funzione main con menu
int main() {
    Corsa corse[MAX_TRATTE];
    int n = leggiCorse("corse.txt", corse);

    int scelta;
    do {
        printf("\nMenu:\n");
        printf("1. Stampa corse\n");
        printf("2. Ordina per data e ora\n");
        printf("3. Ordina per codice di tratta\n");
        printf("4. Ordina per partenza\n");
        printf("5. Ordina per destinazione\n");
        printf("6. Ricerca lineare per partenza\n");
        printf("7. Ricerca dicotomica per partenza\n");
        printf("8. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);

        char partenza[MAX_STR];
        char filename[MAX_STR];
        switch (scelta) {
            case 1:
                printf("Inserire il nome del file o 'V' pre mostrare a video: ");
                scanf("%s", filename);
                if(strcmp(filename, "V")!=0) stampaCorse(corse, n, filename);
                else stampaCorse(corse, n, NULL);
                break;
            case 2:
                qsort(corse, n, sizeof(Corsa), confrontaDataOra);
                printf("Corse ordinate per data e ora di partenza.\n");
                break;
            case 3:
                qsort(corse, n, sizeof(Corsa), confrontaCodiceTratta);
                printf("Corse ordinate per codice di tratta.\n");
                break;
            case 4:
                qsort(corse, n, sizeof(Corsa), confrontaPartenza);
                printf("Corse ordinate per stazione di partenza.\n");
                break;
            case 5:
                qsort(corse, n, sizeof(Corsa), confrontaDestinazione);
                printf("Corse ordinate per stazione di destinazione.\n");
                break;
            case 6:
                printf("Inserisci stazione di partenza (prefisso) ricerca lineare: ");
                scanf("%s", partenza);
                ricercaLineare(corse, n, partenza);
                break;
            case 7:
                printf("Inserisci stazione di partenza (prefisso) ricerca dicotomica: ");
                scanf("%s", partenza);
                qsort(corse, n, sizeof(Corsa), confrontaPartenza);
                ricercaDicotomica(corse, n, partenza);
                break;
            case 8:
                printf("Uscita dal programma.\n");
                break;
            default:
                printf("Scelta non valida.\n");
        }
    } while (scelta != 8);

    return 0;
}
