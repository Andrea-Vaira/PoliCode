#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personaggio.h"
#include "inventario.h"

void stampaMenu();

int main() {
    ListaPersonaggi *lista = NULL;
    Inventario *inventario = NULL;
    char buffer[100];

    lista = caricaPersonaggi("pg.txt");
    inventario = caricaInventario("inventario.txt");

    int scelta;
    do {
        stampaMenu();
        printf("Scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1: {
                Personaggio nuovo;
                printf("Inserisci codice, nome, classe e statistiche (hp mp atk def mag spr):\n");
                scanf("%s %s %s %d %d %d %d %d %d", nuovo.codice, nuovo.nome, nuovo.classe,
                      &nuovo.base.hp, &nuovo.base.mp, &nuovo.base.atk, &nuovo.base.def,
                      &nuovo.base.mag, &nuovo.base.spr);
                aggiungiPersonaggio(lista, nuovo);
                break;
            }
            case 2: {
                printf("Inserisci codice del personaggio da eliminare: ");
                scanf("%s", buffer);
                rimuoviPersonaggio(lista, buffer);
                break;
            }
            case 3: {
                printf("Inserisci codice personaggio e nome oggetto da aggiungere: ");
                scanf("%s %s", buffer, buffer+50);
                NodoPg *pg = cercaPersonaggio(lista, buffer);
                if (pg) modificaEquipaggiamento(&pg->pg, inventario, buffer+50, 1);
                else printf("Personaggio non trovato!\n");
                break;
            }
            case 4: {
                printf("Inserisci codice personaggio e nome oggetto da rimuovere: ");
                scanf("%s %s", buffer, buffer+50);
                NodoPg *pg = cercaPersonaggio(lista, buffer);
                if (pg) modificaEquipaggiamento(&pg->pg, inventario, buffer+50, 0);
                else printf("Personaggio non trovato!\n");
                break;
            }
            case 5: {
                printf("Inserisci codice personaggio: ");
                scanf("%s", buffer);
                NodoPg *pg = cercaPersonaggio(lista, buffer);
                if (pg) {
                    Statistiche complete = calcolaStatisticheComplete(&pg->pg, inventario);
                    stampaStatistiche(&complete);
                } else {
                    printf("Personaggio non trovato!\n");
                }
                break;
            }
            case 6: {
                printf("Inserisci codice personaggio: ");
                scanf("%s", buffer);
                NodoPg *pg = cercaPersonaggio(lista, buffer);
                if (pg) stampaPersonaggio(&pg->pg, inventario);
                else printf("Personaggio non trovato!\n");
                break;
            }
        }
    } while (scelta != 0);

    liberaListaPersonaggi(lista);
    liberaInventario(inventario);
    return 0;
}

void stampaMenu() {
    printf("Menu:\n");
    printf("1. Aggiungi personaggio\n");
    printf("2. Rimuovi personaggio\n");
    printf("3. Aggiungi oggetto a equipaggiamento\n");
    printf("4. Rimuovi oggetto da equipaggiamento\n");
    printf("5. Calcola statistiche complete\n");
    printf("6. Stampa dettagli personaggio\n");
    printf("0. Esci\n");
}