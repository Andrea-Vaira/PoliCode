#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TILES 1000
#define MAX_BOARD_SIZE 50

typedef struct {
    char color1;
    int value1;
    char color2;
    int value2;
} Tile;

typedef struct {
    int tileIndex;
    int rotation;  // 0: non ruotata, 1: ruotata di 90°
} Cell;

Tile tiles[MAX_TILES];
Cell board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int R, C;
int numeroTessere;

void readTiles(const char *filename);
void readBoard(const char *filename);
int calculateLineScore(int indices[], int rotations[], int size, int isRow);
int calculateBoardScore();

int main() {
    readTiles("tiles.txt");
    readBoard("board.txt");

    printf("Punteggio iniziale: %d\n", calculateBoardScore());

    printf("Punteggio massimo ottenibile: %d\n", calculateBoardScore());
    return 0;
}

void readTiles(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Errore nell'apertura di tiles.txt");
        exit(EXIT_FAILURE);
    }
    fscanf(file, "%d", &numeroTessere);
    for (int i = 0; i < numeroTessere; i++) {
        fscanf(file, " %c%d %c%d",
               &tiles[i].color1, &tiles[i].value1,
               &tiles[i].color2, &tiles[i].value2);
    }
    fclose(file);
}

void readBoard(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Errore nell'apertura di board.txt");
        exit(EXIT_FAILURE);
    }
    fscanf(file, "%d %d", &R, &C);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            fscanf(file, "%d/%d", &board[i][j].tileIndex, &board[i][j].rotation);
        }
    }
    fclose(file);
}

int calculateLineScore(int indices[], int rotations[], int size, int isRow) {
    char currentColor = '\0';
    int currentScore = 0, totalScore = 0;

    for (int i = 0; i < size; i++) {
        Tile tile = tiles[indices[i]];
        char color = (rotations[i] == 0) ? (isRow ? tile.color1 : tile.color2)
                                         : (isRow ? tile.color2 : tile.color1);
        int value = (rotations[i] == 0) ? (isRow ? tile.value1 : tile.value2)
                                        : (isRow ? tile.value2 : tile.value1);

        if (currentColor == '\0') {
            currentColor = color;
            currentScore = value;
        } else if (color == currentColor) {
            currentScore += value;
        } else {
            totalScore += currentScore;
            currentColor = color;
            currentScore = value;
        }
    }
    totalScore += currentScore;
    return totalScore;
}


int calculateBoardScore() {
    int totalScore = 0;

    // Calcolo punteggio per le righe
    for (int i = 0; i < R; i++) {
        int indices[C], rotations[C];
        for (int j = 0; j < C; j++) {
            indices[j] = board[i][j].tileIndex;
            rotations[j] = board[i][j].rotation;
        }
        totalScore += calculateLineScore(indices, rotations, C, 1);
    }

    // Calcolo punteggio per le colonne
    for (int j = 0; j < C; j++) {
        int indices[R], rotations[R];
        for (int i = 0; i < R; i++) {
            indices[i] = board[i][j].tileIndex;
            rotations[i] = board[i][j].rotation;
        }
        totalScore += calculateLineScore(indices, rotations, R, 0);
    }

    return totalScore;
}
