#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODI 100
#define MAX_NOME 31
#define INF 0x3f3f3f3f

// Strutture dati
typedef struct {
    char nome[MAX_NOME];
    char rete[MAX_NOME];
} Nodo;

typedef struct {
    int **matrice;           // Matrice di adiacenza
    Nodo *nodi;              // Tabella dei nodi
    int numNodi;             // Numero di nodi
    char **symbolTable;      // Tabella di simboli (da indice a nome)
} Grafo;

typedef struct ListaAdj {
    int nodo;                // Indice del nodo
    int flusso;              // Peso dell'arco
    struct ListaAdj *next;
} ListaAdj;

typedef struct {
    ListaAdj **lista;        // Lista di adiacenza
    int numNodi;
} ListaAdiacenza;

// Prototipi delle funzioni
Grafo *creaGrafo(int numNodi);
void distruggiGrafo(Grafo *grafo);
int aggiungiNodo(Grafo *grafo, char *nome, char *rete);
int trovaNodo(Grafo *grafo, char *nome);
void aggiungiArco(Grafo *grafo, char *nome1, char *nome2, int flusso);
void stampaVertici(Grafo *grafo);
int verificaSottografoCompletoMatrice(Grafo *grafo, int n1, int n2, int n3);
ListaAdiacenza *generaListaAdiacenza(Grafo *grafo);
void stampaListaAdiacenza(ListaAdiacenza *listaAdj, Grafo *grafo);
void distruggiListaAdiacenza(ListaAdiacenza *listaAdj);

// Funzione per creare il grafo
Grafo *creaGrafo(int numNodi) {
    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    grafo->matrice = (int **)malloc(numNodi * sizeof(int *));
    for (int i = 0; i < numNodi; i++) {
        grafo->matrice[i] = (int *)calloc(numNodi, sizeof(int));
    }
    grafo->nodi = (Nodo *)malloc(numNodi * sizeof(Nodo));
    grafo->symbolTable = (char **)malloc(numNodi * sizeof(char *));
    grafo->numNodi = 0;
    return grafo;
}

// Funzione per distruggere il grafo
void distruggiGrafo(Grafo *grafo) {
    for (int i = 0; i < grafo->numNodi; i++) {
        free(grafo->matrice[i]);
        free(grafo->symbolTable[i]);
    }
    free(grafo->matrice);
    free(grafo->nodi);
    free(grafo->symbolTable);
    free(grafo);
}

// Aggiungi nodo al grafo
int aggiungiNodo(Grafo *grafo, char *nome, char *rete) {
    for (int i = 0; i < grafo->numNodi; i++) {
        if (strcmp(grafo->nodi[i].nome, nome) == 0) {
            return i; // Nodo già presente
        }
    }
    strcpy(grafo->nodi[grafo->numNodi].nome, nome);
    strcpy(grafo->nodi[grafo->numNodi].rete, rete);
    grafo->symbolTable[grafo->numNodi] = strdup(nome);
    return grafo->numNodi++;
}

// Trova nodo dato il nome
int trovaNodo(Grafo *grafo, char *nome) {
    for (int i = 0; i < grafo->numNodi; i++) {
        if (strcmp(grafo->nodi[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// Aggiungi arco al grafo
void aggiungiArco(Grafo *grafo, char *nome1, char *nome2, int flusso) {
    int idx1 = trovaNodo(grafo, nome1);
    int idx2 = trovaNodo(grafo, nome2);
    if (idx1 == -1 || idx2 == -1) return;
    grafo->matrice[idx1][idx2] = flusso;
    grafo->matrice[idx2][idx1] = flusso;
}

// Stampa i vertici e gli archi in ordine alfabetico
void stampaVertici(Grafo *grafo) {
    for (int i = 0; i < grafo->numNodi; i++) {
        printf("Nodo: %s\n", grafo->symbolTable[i]);
        for (int j = 0; j < grafo->numNodi; j++) {
            if (grafo->matrice[i][j] > 0) {
                printf("  -> %s (flusso: %d)\n", grafo->symbolTable[j], grafo->matrice[i][j]);
            }
        }
    }
}

// Verifica se tre nodi formano un sottografo completo (matrice)
int verificaSottografoCompletoMatrice(Grafo *grafo, int n1, int n2, int n3) {
    return grafo->matrice[n1][n2] > 0 && grafo->matrice[n2][n3] > 0 && grafo->matrice[n3][n1] > 0 &&
           grafo->matrice[n2][n1] > 0 && grafo->matrice[n3][n2] > 0 && grafo->matrice[n1][n3] > 0;
}

// Genera lista di adiacenza
ListaAdiacenza *generaListaAdiacenza(Grafo *grafo) {
    ListaAdiacenza *listaAdj = (ListaAdiacenza *)malloc(sizeof(ListaAdiacenza));
    listaAdj->lista = (ListaAdj **)malloc(grafo->numNodi * sizeof(ListaAdj *));
    listaAdj->numNodi = grafo->numNodi;

    for (int i = 0; i < grafo->numNodi; i++) {
        listaAdj->lista[i] = NULL;
        for (int j = 0; j < grafo->numNodi; j++) {
            if (grafo->matrice[i][j] > 0) {
                ListaAdj *nuovo = (ListaAdj *)malloc(sizeof(ListaAdj));
                nuovo->nodo = j;
                nuovo->flusso = grafo->matrice[i][j];
                nuovo->next = listaAdj->lista[i];
                listaAdj->lista[i] = nuovo;
            }
        }
    }
    return listaAdj;
}

// Stampa lista di adiacenza
void stampaListaAdiacenza(ListaAdiacenza *listaAdj, Grafo *grafo) {
    for (int i = 0; i < listaAdj->numNodi; i++) {
        printf("%s:", grafo->symbolTable[i]);
        ListaAdj *corrente = listaAdj->lista[i];
        while (corrente) {
            printf(" -> %s (flusso: %d)", grafo->symbolTable[corrente->nodo], corrente->flusso);
            corrente = corrente->next;
        }
        printf("\n");
    }
}

// Distruggi lista di adiacenza
void distruggiListaAdiacenza(ListaAdiacenza *listaAdj) {
    for (int i = 0; i < listaAdj->numNodi; i++) {
        ListaAdj *corrente = listaAdj->lista[i];
        while (corrente) {
            ListaAdj *temp = corrente;
            corrente = corrente->next;
            free(temp);
        }
    }
    free(listaAdj->lista);
    free(listaAdj);
}

// Main
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <file_grafo>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Errore nell'apertura del file.\n");
        return 1;
    }

    Grafo *grafo = creaGrafo(MAX_NODI);
    char id1[MAX_NOME], rete1[MAX_NOME], id2[MAX_NOME], rete2[MAX_NOME];
    int flusso;

    while (fscanf(file, "%s %s %s %s %d", id1, rete1, id2, rete2, &flusso) == 5) {
        int idx1 = aggiungiNodo(grafo, id1, rete1);
        int idx2 = aggiungiNodo(grafo, id2, rete2);
        aggiungiArco(grafo, id1, id2, flusso);
    }

    fclose(file);

    stampaVertici(grafo);

    ListaAdiacenza *listaAdj = generaListaAdiacenza(grafo);
    stampaListaAdiacenza(listaAdj, grafo);

    distruggiListaAdiacenza(listaAdj);
    distruggiGrafo(grafo);

    return 0;
}
