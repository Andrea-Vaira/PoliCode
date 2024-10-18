#include <stdio.h>

int gcd(int a, int b){
    int aus;
    if(a == 0) return b;
    if(b == 0) return a;
    if(b>=a){
        aus = a;
        a = b;
        b = aus;
    }
    if(a%2==0 && b%2 ==0){
        return 2 * gcd(a/2,b/2);
    }
    if(a%2!=0 && b%2 ==0){
        return gcd(a, b/2);
    }
    if(a%2==0 && b%2 !=0){
        return gcd(a/2, b);
    }
    if(a%2!=0 && b%2!=0){
        return gcd((a-b)/2, b);
    }
}

int main() {
    int a, b, ris;
    printf("Inserisci i 2 numeri: ");
    scanf("%d %d", &a, &b);

    ris = gcd(a,b);
    printf("%d", ris);
    return 0;
}
