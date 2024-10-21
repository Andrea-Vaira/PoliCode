#include <stdio.h>

int majority(int *a, int len);
int ricercaMajority(int *a, int start, int end);
int contaOccorrenze(int *a, int len, int val);

int main() {
    int a[] = {  0, 1, 0, 2, 3, 4, 0, 5};
    int len = 8;
    int ris = majority(a, len);
    printf("%d", ris);
    return 0;
}

int majority(int *a, int len){
    if(len == 0)
        return -1;
    return ricercaMajority(a, 0, len - 1);
}

int ricercaMajority(int *a, int start, int end){
    if (start == end) {
        return a[start];
    }

    int sx = ricercaMajority(a, start, (start + end) / 2);
    int dx = ricercaMajority(a, ((start + end) / 2) + 1, end);

    if (sx == dx) {
        return sx;
    }

    int contSx = contaOccorrenze(a, end - start + 1, sx);
    int contDx = contaOccorrenze(a, end - start + 1, dx);

    if (contSx > (end - start + 1) / 2) {
        return sx;
    } else if (contDx > (end - start + 1) / 2) {
        return dx;
    }

    // Non c'è maggioritario
    return -1;
}

int contaOccorrenze(int *a, int len, int val){
    int cont = 0;
    for (int i = 0; i < len; ++i) {
        if(a[i] == val)
            cont++;
    }
    return cont;
}