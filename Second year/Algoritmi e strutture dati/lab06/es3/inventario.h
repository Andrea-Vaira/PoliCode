#include "statistiche.h"
typedef struct {
    char nome[51];
    char tipo[51];
    Statistiche modificatori;
} Oggetto;

typedef struct {
    Oggetto *oggetti;
    int num_oggetti;
} Inventario;

Inventario* caricaInventario(const char *file);
int cercaOggetto(Inventario *inv, const char *nome);
void stampaOggetto(Inventario *inv, int indice);
void liberaInventario(Inventario *inv);
