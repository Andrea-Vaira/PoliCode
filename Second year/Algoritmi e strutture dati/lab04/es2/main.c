#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 51

typedef struct{
    int giorno;
    int mese;
    int anno;
} data;

typedef struct {
    char codice[6];
    char nome[MAX_STR];
    char cognome[MAX_STR];
    data data_di_nascita;
    char via[MAX_STR];
    char citta[MAX_STR];
    int cap;
} Item;

typedef struct Nodo {
    Item dato;
    struct Nodo *next;
} Nodo;

Nodo *crea_nodo(Item item) {
    Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
    if (nodo != NULL) {
        nodo->dato = item;
        nodo->next = NULL;
    }
    return nodo;
}

int confronta_date(data data1, data data2) {

    if (data1.anno != data2.anno)
        return data1.anno - data2.anno;
    else if (data1.mese != data2.mese)
        return data1.mese - data2.mese;
    else
        return data1.giorno - data2.giorno;
}

void inserisci_ordinato(Nodo **head, Item item) {
    Nodo *nodo = crea_nodo(item);
    if (*head == NULL || confronta_date(nodo->dato.data_di_nascita, (*head)->dato.data_di_nascita) > 0) {
        nodo->next = *head;
        *head = nodo;
    } else {
        Nodo *corrente = *head;
        while (corrente->next != NULL && confronta_date(nodo->dato.data_di_nascita, corrente->next->dato.data_di_nascita) <= 0) {
            corrente = corrente->next;
        }
        nodo->next = corrente->next;
        corrente->next = nodo;
    }
}

Nodo *cerca_per_codice(Nodo *head, const char *codice) {
    Nodo *corrente = head;
    while (corrente != NULL) {
        if (strcmp(corrente->dato.codice, codice) == 0) {
            return corrente;
        }
        corrente = corrente->next;
    }
    return NULL;
}

Item cancella_per_codice(Nodo **head, const char *codice) {
    Nodo *corrente = *head, *prev = NULL;
    Item item_vuoto = {"", "", "", {0,0,0}, 0};  // da restituire se non trovato

    while (corrente != NULL) {
        if (strcmp(corrente->dato.codice, codice) == 0) {
            if (prev == NULL)
                *head = corrente->next;
            else
                prev->next = corrente->next;

            Item dato = corrente->dato;
            free(corrente);
            return dato;
        }
        prev = corrente;
        corrente = corrente->next;
    }
    return item_vuoto;
}

Item estrai_primo_in_intervallo(Nodo **head, data data_inizio, data data_fine) {
    Nodo *corrente = *head, *prev = NULL;
    Item item_vuoto = {"", "", "", {0,0,0}, 0};  // da restituire se non trovato
    data dataI, dataF;

    while (corrente != NULL) {
        if (confronta_date(corrente->dato.data_di_nascita, dataI) >= 0 &&
            confronta_date(corrente->dato.data_di_nascita, dataF) <= 0) {

            if (prev == NULL)
                *head = corrente->next;
            else
                prev->next = corrente->next;

            Item dato = corrente->dato;
            free(corrente);
            return dato;
        }
        prev = corrente;
        corrente = corrente->next;
    }
    return item_vuoto;
}

void stampa_lista_su_file(Nodo *head, const char *nome_file) {
    FILE *file = fopen(nome_file, "w");
    if (file == NULL) {
        printf("Errore nell'aprire il file.\n");
        return;
    }

    Nodo *corrente = head;
    while (corrente != NULL) {
        fprintf(file, "%s %s %s %d/%d/%d %s %s %d\n",
                corrente->dato.codice,
                corrente->dato.nome,
                corrente->dato.cognome,
                corrente->dato.data_di_nascita.giorno,
                corrente->dato.data_di_nascita.mese,
                corrente->dato.data_di_nascita.anno,
                corrente->dato.via,
                corrente->dato.citta,
                corrente->dato.cap);
        corrente = corrente->next;
    }
    fclose(file);
}

void acquisisci_item_da_tastiera(Item *item) {
    printf("Inserisci codice: ");
    scanf("%s", item->codice);
    printf("Inserisci nome: ");
    scanf("%s", item->nome);
    printf("Inserisci cognome: ");
    scanf("%s", item->cognome);
    printf("Inserisci data di nascita (gg/mm/aaaa): ");
    scanf("%d/%d/%d", &item->data_di_nascita.giorno, &item->data_di_nascita.mese, &item->data_di_nascita.anno);
    printf("Inserisci via: ");
    scanf("%s", item->via);
    printf("Inserisci citta': ");
    scanf("%s", item->citta);
    printf("Inserisci CAP: ");
    scanf("%d", &item->cap);
}

void acquisisci_e_inserisci_da_file(Nodo ** head, char * nome_file){
    FILE *file = fopen(nome_file, "r");
    if (file == NULL) {
        printf("Errore nell'aprire il file.\n");
        return;
    }

    Item item;
    while (fscanf(file, "%s %s %s %d/%d/%d %s %s %d", item.codice, item.nome, item.cognome,
                  &item.data_di_nascita.giorno, &item.data_di_nascita.mese, &item.data_di_nascita.anno, item.via, item.citta, &item.cap) == 7) {
        inserisci_ordinato(head, item);
    }
    fclose(file);
    printf("Dati caricati da file.\n");
}

int main() {
    Nodo *head = NULL;  // Lista vuota
    int scelta;
    data data_inizio, data_fine;
    char codice[6];
    char nome_file[100];
    Item item;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Inserisci nuovo elemento (da tastiera)\n");
        printf("2. Carica elementi da file\n");
        printf("3. Ricerca elemento per codice\n");
        printf("4. Cancella elemento per codice\n");
        printf("5. Cancella elementi con data in un intervallo\n");
        printf("6. Stampa lista su file\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                acquisisci_item_da_tastiera(&item);
                inserisci_ordinato(&head, item);
                printf("Elemento inserito.\n");
                break;

            case 2:
                printf("Inserisci il nome del file: ");
                scanf("%s", nome_file);
                acquisisci_e_inserisci_da_file(&head, nome_file);
                break;

            case 3:
                printf("Inserisci il codice da cercare: ");
                scanf("%s", codice);
                Nodo *trovato = cerca_per_codice(head, codice);
                if (trovato != NULL) {
                    printf("Elemento trovato: %s %s %s %d/%d/%d %s %s %d\n",
                           trovato->dato.codice, trovato->dato.nome, trovato->dato.cognome,
                           trovato->dato.data_di_nascita.giorno, trovato->dato.data_di_nascita.mese, trovato->dato.data_di_nascita.anno, trovato->dato.via,
                           trovato->dato.citta, trovato->dato.cap);
                } else {
                    printf("Elemento non trovato.\n");
                }
                break;

            case 4:
                printf("Inserisci il codice da cancellare: ");
                scanf("%s", codice);
                item = cancella_per_codice(&head, codice);
                if (strcmp(item.codice, "") != 0) {
                    printf("Elemento cancellato: %s %s %s %s %s %s %d\n",
                           item.codice, item.nome, item.cognome,
                           item.data_di_nascita, item.via, item.citta, item.cap);
                } else {
                    printf("Elemento non trovato.\n");
                }
                break;

            case 5:
                printf("Inserisci la data di inizio (gg/mm/aaaa): ");
                scanf("%d/%d/%d", &data_inizio.giorno, &data_inizio.mese, &data_inizio.anno );
                printf("Inserisci la data di fine (gg/mm/aaaa): ");
                scanf("%d/%d/%d", &data_fine.giorno, &data_fine.mese, &data_fine.anno );
                while (1) {
                    item = estrai_primo_in_intervallo(&head, data_inizio, data_fine);
                    if (strcmp(item.codice, "") == 0) {
                        break;
                    }
                    printf("Elemento estratto: %s %s %s %d/%d/%d %s %s %d\n",
                           item.codice,
                           item.nome,
                           item.cognome,
                           item.data_di_nascita.giorno,
                           item.data_di_nascita.mese,
                           item.data_di_nascita.anno,
                           item.via,
                           item.citta,
                           item.cap);
                }
                break;

            case 6:
                printf("Inserisci il nome del file per la stampa: ");
                scanf("%s", nome_file);
                stampa_lista_su_file(head, nome_file);
                printf("Lista stampata su file.\n");
                break;

            case 0:
                printf("Uscita dal programma.\n");
                break;

            default:
                printf("Scelta non valida. Riprova.\n");
                break;
        }
    } while (scelta != 0);

    return 0;
}
