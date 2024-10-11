#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CORSE 1000
#define MAX_STR 30

typedef struct {
    char codice_tratta[MAX_STR];
    char partenza[MAX_STR];
    char destinazione[MAX_STR];
    char data[MAX_STR];
    char ora_partenza[MAX_STR];
    char ora_arrivo[MAX_STR];
    int ritardo;
} Corsa;

typedef enum { r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine } enumComando;

enumComando leggiComando();
void selezionaDati(Corsa corse[], int n, enumComando comando);
void elencaCorsePerData(Corsa corse[], int n, char *data_inizio, char *data_fine);
void elencaCorsePerPartenza(Corsa corse[], int n, char *fermata);
void elencaCorsePerCapolinea(Corsa corse[], int n, char *fermata);
void elencaCorseInRitardo(Corsa corse[], int n, char *data_inizio, char *data_fine);
void calcolaRitardoTotale(Corsa corse[], int n, char *codice_tratta);

int main() {
    FILE *fp;
    Corsa corse[MAX_CORSE];
    int n, i;
    enumComando comando;

    if ((fp = fopen("corse.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file corse.txt\n");
        return 1;
    }

    fscanf(fp, "%d", &n);

    for (i = 0; i < n; i++) {
        fscanf(fp, "%s %s %s %s %s %s %d", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione,
               corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, &corse[i].ritardo);
    }

    fclose(fp);

    do {
        comando = leggiComando();
        selezionaDati(corse, n, comando);
    } while (comando != r_fine);

    return 0;
}

enumComando leggiComando() {
    char comando_str[MAX_STR];
    printf("Inserire comando (date, partenza, capolinea, ritardo, ritardo_tot, fine): ");
    scanf("%s", comando_str);

    if (strcmp(comando_str, "date") == 0) return r_date;
    if (strcmp(comando_str, "partenza") == 0) return r_partenza;
    if (strcmp(comando_str, "capolinea") == 0) return r_capolinea;
    if (strcmp(comando_str, "ritardo") == 0) return r_ritardo;
    if (strcmp(comando_str, "ritardo_tot") == 0) return r_ritardo_tot;
    if (strcmp(comando_str, "fine") == 0) return r_fine;

    return r_fine;
}

void selezionaDati(Corsa corse[], int n, enumComando comando) {
    char data_inizio[MAX_STR], data_fine[MAX_STR], fermata[MAX_STR], codice_tratta[MAX_STR];

    switch (comando) {
        case r_date:
            printf("Inserire data inizio (aaaa-mm-gg): ");
            scanf("%s", data_inizio);
            printf("Inserire data fine (aaaa-mm-gg): ");
            scanf("%s", data_fine);
            elencaCorsePerData(corse, n, data_inizio, data_fine);
            break;

        case r_partenza:
            printf("Inserire fermata di partenza: ");
            scanf("%s", fermata);
            elencaCorsePerPartenza(corse, n, fermata);
            break;

        case r_capolinea:
            printf("Inserire fermata di capolinea: ");
            scanf("%s", fermata);
            elencaCorsePerCapolinea(corse, n, fermata);
            break;

        case r_ritardo:
            printf("Inserire data inizio (aaaa-mm-gg): ");
            scanf("%s", data_inizio);
            printf("Inserire data fine (aaaa-mm-gg): ");
            scanf("%s", data_fine);
            elencaCorseInRitardo(corse, n, data_inizio, data_fine);
            break;

        case r_ritardo_tot:
            printf("Inserire codice tratta: ");
            scanf("%s", codice_tratta);
            calcolaRitardoTotale(corse, n, codice_tratta);
            break;

        case r_fine:
            printf("Programma terminato.\n");
            break;
    }
}

void elencaCorsePerData(Corsa corse[], int n, char *data_inizio, char *data_fine) {
    for (int i = 0; i < n; i++) {
        if (strcmp(corse[i].data, data_inizio) >= 0 && strcmp(corse[i].data, data_fine) <= 0) {
            printf("%s %s %s %s %s %s %d\n", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione,
                   corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, corse[i].ritardo);
        }
    }
}

void elencaCorsePerPartenza(Corsa corse[], int n, char *fermata) {
    for (int i = 0; i < n; i++) {
        if (strcmp(corse[i].partenza, fermata) == 0) {
            printf("%s %s %s %s %s %s %d\n", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione,
                   corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, corse[i].ritardo);
        }
    }
}

void elencaCorsePerCapolinea(Corsa corse[], int n, char *fermata) {
    for (int i = 0; i < n; i++) {
        if (strcmp(corse[i].destinazione, fermata) == 0) {
            printf("%s %s %s %s %s %s %d\n", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione,
                   corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, corse[i].ritardo);
        }
    }
}

void elencaCorseInRitardo(Corsa corse[], int n, char *data_inizio, char *data_fine) {
    for (int i = 0; i < n; i++) {
        if (strcmp(corse[i].data, data_inizio) >= 0 && strcmp(corse[i].data, data_fine) <= 0 && corse[i].ritardo > 0) {
            printf("%s %s %s %s %s %s %d\n", corse[i].codice_tratta, corse[i].partenza, corse[i].destinazione,
                   corse[i].data, corse[i].ora_partenza, corse[i].ora_arrivo, corse[i].ritardo);
        }
    }
}

void calcolaRitardoTotale(Corsa corse[], int n, char *codice_tratta) {
    int ritardo_totale = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(corse[i].codice_tratta, codice_tratta) == 0) {
            ritardo_totale += corse[i].ritardo;
        }
    }
    printf("Ritardo totale per la tratta %s: %d minuti\n", codice_tratta, ritardo_totale);
}
