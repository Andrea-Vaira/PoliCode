
#include "statistiche.h"
#include "inventario.h"

#define MAX_EQUIP 8

typedef struct {
    char codice[10];
    char nome[51];
    char classe[51];
    Statistiche base;
    int equipaggiamento[MAX_EQUIP];
    int num_equip;
} Personaggio;

typedef struct nodo {
    Personaggio pg;
    struct nodo *next;
} NodoPg;

typedef struct {
    NodoPg *head;
} ListaPersonaggi;

ListaPersonaggi* caricaPersonaggi(const char *file);
void aggiungiPersonaggio(ListaPersonaggi *lista, Personaggio pg);
void rimuoviPersonaggio(ListaPersonaggi *lista, const char *codice);
NodoPg* cercaPersonaggio(ListaPersonaggi *lista, const char *codice);
void stampaPersonaggio(Personaggio *pg, Inventario *inv);
void modificaEquipaggiamento(Personaggio *pg, Inventario *inv, const char *nome, int aggiungi);
Statistiche calcolaStatisticheComplete(Personaggio *pg, Inventario *inv);
void liberaListaPersonaggi(ListaPersonaggi *lista);

