#include <stdio.h>

int main() {
    int a=0, b=0, c = 0;
    printf("Inserisci a: ");
    scanf("%d", &a);
    printf("Inserisci b: ");
    scanf("%d", &b);
    do{
        c = a%b;
        a = b;
        b = c;
    }while(b>0);
    printf("MCD %d", a);
    return 0;
}
