#include <stdio.h>

int majority(int *a, int len);

int main() {
    int a[] = {  0, 1, 0, 2, 3, 4, 0, 5 };
    int len = 8;
    int ris = majority(a, len);
    printf("%d", ris);
    return 0;
}

int majority(int *a, int len){
    if(len == 1){
        return *a;
    }
    int sx = majority(a, len/2);
    int dx = majority((a+len/2), len-(len/2));
    if(sx == dx)
        return sx;
    if(sx == -1 && dx != -1)
        return dx;
    if(sx != -1 && dx == -1)
        return sx;
    return -1;
}





