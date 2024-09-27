#include <stdio.h>

typedef struct {
    int inizioX;
    int inizioY;
    int fineX;
    int fineY;

} rettangolo;

int* readFromFile(char *path);

int main() {
    rettangolo rettangoli[100];
    int *matrice = readFromFile("matrici.txt");
    int nrettangoli = 0;


    return 0;
}

int* readFromFile(char *path){
    FILE *fp = fopen(path, "r");
    int r,c;
    fscanf(fp, "%d %d", &r, &c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {

        }
    }
    fclose(fp);
}