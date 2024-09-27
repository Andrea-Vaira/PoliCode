#include <stdio.h>

void sottoSequenze(int V[], int N);
void caricaAus(int v[], int aus[], int start);
int checkZero(int aus[]);
void stampaAus(int aus[]);

int main() {
    int v [30], n;


    printf("inserisci la lunghezza del vettore: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("inserisci il valore in posizione %d: ", i);
        scanf("%d", &v[i]);
    }

    sottoSequenze(v, n);



    return 0;
}

void sottoSequenze(int V[], int N){
    /*// trovo la sequenza di lunghezza massima
    int max = 0;
    int cont = 0;
    for (int i = 0; i < N; i++) {
        if(V[i] != 0){
            cont++;
        }
        else{
            if(cont>max) max = cont;
            cont = 0;
        }
    }


    //carico i primi cont valori nel vet aus
    int j = 0;
    int aus[max/4];
    while(j+max<=N){
        caricaAus(V, aus, j);
        //se =1 no zeri, se =0 zeri
        if(checkZero(aus) == 0){
            stampaAus(aus);
        }
        j++;
    }*/

    int max = 0; // sotto vettori di lunghezza massima
    int cont = 0;
    for (int i = 0; i < N; i++) {
        if(V[i] != 0){
            cont++;
        }
        else{
            if(cont>max) max = cont;
            cont = 0;
        }
    }

    int i = 0;
    while(i<N){
        for (; i < max && V[i] != 0; i++) {}
        if(V[i] == 0){
            i++;
        }
        else{
            int j = i;
            printf("[");
            for (; i-j < max ; j++) {
                printf("%d ", V[j]);
            }
            printf("]");

        }
    }
}

void caricaAus(int v[], int aus[], int start){
    for (int i = start, j = 0; j < sizeof(aus)/4; i++, j++) {
        aus[j] = v[i];
        printf("%d, ", aus[j]);
    }
}

int checkZero(int aus[]){
    int flag = 0;
    for (int i = 0; i < sizeof(aus)/4; ++i) {
        if(aus[i] == 0){
            flag = 1;
        }
    }
    return flag;
}

void stampaAus(int aus[]){
    printf("[");
    for (int i = 0; i < (sizeof(aus)/4)-1; i++) {
        printf("%d, ", aus[i]);
    }
    printf("%d]", aus[(sizeof(aus)/4)-1]);
}