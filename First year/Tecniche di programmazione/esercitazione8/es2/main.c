#include <stdio.h>

// LITTLE ENDIAN
void stampaCodifica (void *p, int size, int bigEndian);
int isBigEndian();
int main() {
    float af;
    double ad;
    int bigEndian = isBigEndian();
    printf("Dimensione double: %d Byte\n", sizeof(ad));
    printf("Dimensione float: %d Byte\n", sizeof(af));


    printf("inserisci numero: ");
    scanf("%lf", &ad);
    af = (float) ad;

    printf("Stampa float: ");
    stampaCodifica((void *)&af,sizeof(af),bigEndian);
    printf("Stampa double: ");
    stampaCodifica((void *)&ad,sizeof(ad),bigEndian);

    return 0;
}

void stampaCodifica (void *p, int size, int bigEndian){
    unsigned char *byte = ( char *)p;
    if (bigEndian) {
        for (int i = 0; i < size; i++) {
            for (int j = 7; j >= 0; j--) {
                int val = (byte[i] >> j) == 0 ? 0 : 1 ;
                printf("%d", val);
            }
            printf(" ");
        }
    } else {
        for (int i = size - 1; i >= 0; i--) {
            for (int j = 7; j >= 0; j--) {
                int val = (byte[i] >> j) == 0 ? 0 : 1 ;
                printf("%d", val);
            }
            printf(" ");
        }
    }
    printf("\n");
}

int isBigEndian() {
    unsigned int x = 1;
    char *c = (char*)&x;
    return (*c == 0); // Ritorna 1 se Big Endian, 0 se Little Endian
}