#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
    char codice[6];
    char nome[51];
    char cognome[51];
    char data_di_nascita[11];
    char via[51];
    char citta[51];
    int cap;
    struct Item* next;
} Item;

Item* creaItem(char codice[], char nome[], char cognome[], char data_di_nascita[], char via[], char citta[], int cap) {
    Item* nuovo = (Item*)malloc(sizeof(Item));
    if (!nuovo) {
        printf("Errore: memoria insufficiente.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(nuovo->codice, codice);
    strcpy(nuovo->nome, nome);
    strcpy(nuovo->cognome, cognome);
    strcpy(nuovo->data_di_nascita, data_di_nascita);
    strcpy(nuovo->via, via);
    strcpy(nuovo->citta, citta);
    nuovo->cap = cap;
    nuovo->next = NULL;
    return nuovo;
}

// Funzione per inserire un elemento nella lista in ordine per data di nascita
void inserisciOrdinato(Item** head, Item* nuovo) {
    if (*head == NULL || strcmp(nuovo->data_di_nascita, (*head)->data_di_nascita) > 0) {
        nuovo->next = *head;
        *head = nuovo;
    } else {
        Item* current = *head;
        while (current->next != NULL && strcmp(nuovo->data_di_nascita, current->next->data_di_nascita) <= 0) {
            current = current->next;
        }
        nuovo->next = current->next;
        current->next = nuovo;
    }
}

// Funzione per cercare un elemento per codice
Item* cercaPerCodice(Item* head, char codice[]) {
    while (head != NULL) {
        if (strcmp(head->codice, codice) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

// Funzione per cancellare un elemento per codice
Item* cancellaPerCodice(Item** head, char codice[]) {
    Item* current = *head;
    Item* prev = NULL;

    while (current != NULL && strcmp(current->codice, codice) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) return NULL; // Elemento non trovato

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    return current;
}

// Funzione per cancellare ed estrarre elementi tra due date
Item* cancellaTraDate(Item** head, char data_inizio[], char data_fine[]) {
    Item* current = *head;
    Item* prev = NULL;

    while (current != NULL && (strcmp(current->data_di_nascita, data_inizio) < 0 || strcmp(current->data_di_nascita, data_fine) > 0)) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) return NULL; // Nessun elemento trovato nell'intervallo

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    return current;
}

// Funzione per stampare la lista su file
void stampaSuFile(Item* head, const char* nome_file) {
    FILE* file = fopen(nome_file, "w");
    if (!file) {
        printf("Errore nell'apertura del file.\n");
        return;
    }

    while (head != NULL) {
        fprintf(file, "%s %s %s %s %s %s %d\n",
                head->codice, head->nome, head->cognome,
                head->data_di_nascita, head->via, head->citta, head->cap);
        head = head->next;
    }

    fclose(file);
    printf("Lista stampata su %s.\n", nome_file);
}

// Funzione principale
int main() {
    Item* lista = NULL; // Lista inizialmente vuota
    int scelta;
    char buffer[100];
    char codice[6], nome[51], cognome[51], data_di_nascita[11], via[51], citta[51], data_inizio[11], data_fine[11];
    int cap;

    do {
        printf("\nMenu:\n");
        printf("1. Inserisci un nuovo elemento (da tastiera)\n");
        printf("2. Carica elementi da file\n");
        printf("3. Cerca un elemento per codice\n");
        printf("4. Cancella un elemento per codice\n");
        printf("5. Cancella elementi tra due date\n");
        printf("6. Stampa la lista su file\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                printf("Inserisci i dati (codice, nome, cognome, data_di_nascita, via, citta, cap):\n");
                scanf("%s %s %s %s %s %s %d", codice, nome, cognome, data_di_nascita, via, citta, &cap);
                inserisciOrdinato(&lista, creaItem(codice, nome, cognome, data_di_nascita, via, citta, cap));
                break;
            case 2:
                printf("Nome del file da caricare: ");
                scanf("%s", buffer);
                FILE* file = fopen(buffer, "r");
                if (!file) {
                    printf("Errore nell'apertura del file.\n");
                    break;
                }
                while (fscanf(file, "%s %s %s %s %s %s %d", codice, nome, cognome, data_di_nascita, via, citta, &cap) == 7) {
                    inserisciOrdinato(&lista, creaItem(codice, nome, cognome, data_di_nascita, via, citta, cap));
                }
                fclose(file);
                printf("Dati caricati con successo.\n");
                break;
            case 3:
                printf("Inserisci il codice da cercare: ");
                scanf("%s", codice);
                Item* trovato = cercaPerCodice(lista, codice);
                if (trovato) {
                    printf("Trovato: %s %s %s %s %s %s %d\n",
                           trovato->codice, trovato->nome, trovato->cognome,
                           trovato->data_di_nascita, trovato->via, trovato->citta, trovato->cap);
                } else {
                    printf("Elemento non trovato.\n");
                }
                break;
            case 4:
                printf("Inserisci il codice da cancellare: ");
                scanf("%s", codice);
                Item* cancellato = cancellaPerCodice(&lista, codice);
                if (cancellato) {
                    printf("Cancellato: %s %s %s %s %s %s %d\n",
                           cancellato->codice, cancellato->nome, cancellato->cognome,
                           cancellato->data_di_nascita, cancellato->via, cancellato->citta, cancellato->cap);
                    free(cancellato);
                } else {
                    printf("Elemento non trovato.\n");
                }
                break;
            case 5:
                printf("Inserisci le due date (inizio e fine, formato gg/mm/aaaa): ");
                scanf("%s %s", data_inizio, data_fine);
                while ((cancellato = cancellaTraDate(&lista, data_inizio, data_fine)) != NULL) {
                    printf("Estratto: %s %s %s %s %s %s %d\n",
                           cancellato->codice, cancellato->nome, cancellato->cognome,
                           cancellato->data_di_nascita, cancellato->via, cancellato->citta, cancellato->cap);
                    free(cancellato);
                }
                break;
            case 6:
                printf("Nome del file per la stampa: ");
                scanf("%s", buffer);
                stampaSuFile(lista, buffer);
                break;
            case 0:
                printf("Uscita...\n");
                break;
            default:
                printf("Scelta non valida.\n");
                break;
        }
    } while (scelta != 0);

    // Liberazione della memoria
    while (lista != NULL) {
        Item* temp = lista;
        lista = lista->next;
        free(temp);
    }

    return 0;
}
