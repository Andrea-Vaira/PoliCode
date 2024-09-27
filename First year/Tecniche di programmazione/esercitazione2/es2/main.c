#include <stdio.h>

int main() {
    int a=0, b=1, c=1;
    int nNum=0;
    printf("Inserire il numero di cifre della successione di Fibonacci: ");
    scanf("%d", &nNum);

    if(nNum>=1)
        printf("0 ");
    if(nNum >= 2)
        printf("1 ");
    if(nNum >= 3)
        printf("1 ");
    if(nNum>=4){
        for (int i = 3; i < nNum; i++) {
            a = b;
            b = c;
            c = a+b;
            printf("%d ", c);
        }
    }

    return 0;
}
