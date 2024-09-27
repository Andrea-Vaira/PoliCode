#include <stdio.h>

int main() {
    FILE *fin = fopen("expr.txt", "r");
    char ch1, ch2;

    ch1='0';
    while(ch2 != EOF){
        ch2 = fgetc(fin);
        if(ch2 != EOF){

            

            ch2 = ch1;
        }
    }

    return 0;
}
