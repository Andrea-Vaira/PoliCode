#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personaggio.h"

ListaPersonaggi* caricaPersonaggi(const char *file) {
    FILE *fp = fopen(file, "r");
    if (!fp) {
        perror("Errore nell'apertura del file personaggi");
        return NULL;
    }

    ListaPersonaggi *lista = malloc(sizeof(ListaPersonaggi));
    lista->head = NULL;

    char codice[10], nome[51], classe[51];
    int hp, mp, atk, def, mag, spr;

    while (fscanf(fp, "%s %s %s %d %d %d %d %d %d",
                  codice, nome, classe, &hp, &mp, &atk, &def, &mag, &spr) == 9) {
        Personaggio pg;
        strcpy(pg.codice, codice);
        strcpy(pg.nome, nome);
        strcpy(pg.classe, classe);
        pg.base = (Statistiche){hp, mp, atk, def, mag, spr};
        pg.num_equip = 0;

        NodoPg *nuovoNodo = malloc(sizeof(NodoPg));
        nuovoNodo->pg = pg;
        nuovoNodo->next = lista->head;
        lista->head = nuovoNodo;
    }

    fclose(fp);
    return lista;
}

void aggiungiPersonaggio(ListaPersonaggi *lista, Personaggio pg) {
    NodoPg *nuovoNodo = malloc(sizeof(NodoPg));
    nuovoNodo->pg = pg;
    nuovoNodo->next = lista->head;
    lista->head = nuovoNodo;
}

void rimuoviPersonaggio(ListaPersonaggi *lista, const char *codice) {
    NodoPg *curr = lista->head, *prev = NULL;

    while (curr && strcmp(curr->pg.codice, codice) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        printf("Personaggio non trovato.\n");
        return;
    }

    if (prev) {
        prev->next = curr->next;
    } else {
        lista->head = curr->next;
    }

    free(curr);
}

NodoPg* cercaPersonaggio(ListaPersonaggi *lista, const char *codice) {
    NodoPg *curr = lista->head;
    while (curr) {
        if (strcmp(curr->pg.codice, codice) == 0) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void modificaEquipaggiamento(Personaggio *pg, Inventario *inv, const char *nome, int aggiungi) {
    int indice = cercaOggetto(inv, nome);

    if (indice == -1) {
        printf("Oggetto non trovato.\n");
        return;
    }

    if (aggiungi) {
        if (pg->num_equip >= MAX_EQUIP) {
            printf("Equipaggiamento pieno.\n");
            return;
        }
        pg->equipaggiamento[pg->num_equip++] = indice;
    } else {
        int found = 0;
        for (int i = 0; i < pg->num_equip; i++) {
            if (pg->equipaggiamento[i] == indice) {
                found = 1;
                for (int j = i; j < pg->num_equip - 1; j++) {
                    pg->equipaggiamento[j] = pg->equipaggiamento[j + 1];
                }
                pg->num_equip--;
                break;
            }
        }
        if (!found) {
            printf("Oggetto non equipaggiato.\n");
        }
    }
}

Statistiche calcolaStatisticheComplete(Personaggio *pg, Inventario *inv) {
    Statistiche complete = pg->base;
    for (int i = 0; i < pg->num_equip; i++) {
        sommaStatistiche(&complete, &inv->oggetti[pg->equipaggiamento[i]].modificatori);
    }
    return complete;
}

void stampaPersonaggio(Personaggio *pg, Inventario *inv) {
    printf("Codice: %s, Nome: %s, Classe: %s\n", pg->codice, pg->nome, pg->classe);
    printf("Statistiche di base: ");
    stampaStatistiche(&pg->base);
    printf("Equipaggiamento:\n");
    for (int i = 0; i < pg->num_equip; i++) {
        stampaOggetto(inv, pg->equipaggiamento[i]);
    }
}

void liberaListaPersonaggi(ListaPersonaggi *lista) {
    NodoPg *curr = lista->head;
    while (curr) {
        NodoPg *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(lista);
}
