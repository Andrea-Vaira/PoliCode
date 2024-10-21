#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANZONI 5
#define MAX_TITOLO 256

char*** leggiFile(const char* nome_file, int* num_amici, int** num_canzoni);

void generaPlaylist(char*** brani, int* num_canzoni, int num_amici, char** playlist, int livello) ;


int main() {
    int num_amici;
    int* num_canzoni;
    char*** brani;

    brani = leggiFile("brani.txt", &num_amici, &num_canzoni);

    char** playlist = (char**)malloc(num_amici * sizeof(char*));

    generaPlaylist(brani, num_canzoni, num_amici, playlist, 0);

    for (int i = 0; i < num_amici; i++) {
        for (int j = 0; j < num_canzoni[i]; j++) {
            free(brani[i][j]);
        }
        free(brani[i]);
    }
    free(brani);
    free(num_canzoni);
    free(playlist);

    return 0;
}

char*** leggiFile(const char* nome_file, int* num_amici, int** num_canzoni) {
    FILE* file = fopen(nome_file, "r");
    if (file == NULL) {
        printf("Errore nell'apertura del file.\n");
        exit(1);
    }

    fscanf(file, "%d", num_amici);

    *num_canzoni = (int*)malloc((*num_amici) * sizeof(int));

    char*** brani = (char***)malloc((*num_amici) * sizeof(char**));

    for (int i = 0; i < *num_amici; i++) {
        fscanf(file, "%d", &(*num_canzoni)[i]);

        brani[i] = (char**)malloc((*num_canzoni)[i] * sizeof(char*));
        for (int j = 0; j < (*num_canzoni)[i]; j++) {
            brani[i][j] = (char*)malloc(MAX_TITOLO * sizeof(char));
            fscanf(file, "%s", brani[i][j]);
        }
    }

    fclose(file);
    return brani;
}

void generaPlaylist(char*** brani, int* num_canzoni, int num_amici, char** playlist, int livello) {
    if (livello == num_amici) {
        printf("Playlist: ");
        for (int i = 0; i < num_amici; i++) {
            printf("%s ", playlist[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < num_canzoni[livello]; i++) {
        playlist[livello] = brani[livello][i];
        generaPlaylist(brani, num_canzoni, num_amici, playlist, livello + 1);
    }
}