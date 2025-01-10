#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"

Inventario* caricaInventario(const char *file) {
    FILE *fp = fopen(file, "r");
    if (!fp) {
        perror("Errore nell'apertura del file inventario");
        return NULL;
    }

    Inventario *inv = malloc(sizeof(Inventario));
    fscanf(fp, "%d", &inv->num_oggetti);

    inv->oggetti = malloc(inv->num_oggetti * sizeof(Oggetto));

    for (int i = 0; i < inv->num_oggetti; i++) {
        fscanf(fp, "%s %s %d %d %d %d %d %d",
               inv->oggetti[i].nome, inv->oggetti[i].tipo,
               &inv->oggetti[i].modificatori.hp, &inv->oggetti[i].modificatori.mp,
               &inv->oggetti[i].modificatori.atk, &inv->oggetti[i].modificatori.def,
               &inv->oggetti[i].modificatori.mag, &inv->oggetti[i].modificatori.spr);
    }

    fclose(fp);
    return inv;
}

int cercaOggetto(Inventario *inv, const char *nome) {
    for (int i = 0; i < inv->num_oggetti; i++) {
        if (strcmp(inv->oggetti[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1; // Oggetto non trovato
}

void stampaOggetto(Inventario *inv, int indice) {
    if (indice < 0 || indice >= inv->num_oggetti) {
        printf("Oggetto non valido.\n");
        return;
    }
    Oggetto *ogg = &inv->oggetti[indice];
    printf("Nome: %s, Tipo: %s, Modificatori: ", ogg->nome, ogg->tipo);
    stampaStatistiche(&ogg->modificatori);
}

void liberaInventario(Inventario *inv) {
    if (inv) {
        free(inv->oggetti);
        free(inv);
    }
}
