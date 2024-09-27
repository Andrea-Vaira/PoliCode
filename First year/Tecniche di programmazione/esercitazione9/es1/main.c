#include <stdio.h>

typedef struct{
    int integer;
    float fl;
} myStruct;
void caricaVet(int[]);
void stampaCodifica (void *p, int size);
int main() {
    int vet[10];
    caricaVet(vet);
    int* p = vet;

    stampaCodifica(p, sizeof(int));
    stampaCodifica(p+1, sizeof(int));
    printf("%d", (void*)(p+1)-(void*)(p));
    printf("\n\n");

    myStruct struttura = {
            .integer = 1,
            .fl = 1.2
    };
    void* pInt = &struttura.integer;
    void* pFl = &struttura.fl;
    stampaCodifica(p, sizeof(int));
    stampaCodifica(p + sizeof(float), sizeof(float));
    return 0;
}

void caricaVet(int vet[]){
    for (int i = 0; i < 10; i++) {
        scanf("%d", &vet[i]);
    }
}

void stampaCodifica (void *p, int size){
    unsigned char *byte = ( char *)p;
    for (int i = size - 1; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
            int val = (byte[i] >> j) == 0 ? 0 : 1 ;
            printf("%d", val);
        }
        printf(" ");
    }
    printf("\n");
}
