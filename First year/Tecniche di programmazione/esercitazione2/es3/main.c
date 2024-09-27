#include <stdio.h>
#include <string.h>

int comprimi(FILE *fin, FILE *fout);
int decomprimi(FILE *fin, FILE *fout);

int main() {
    printf("Hello, World!\n");
    return 0;
}

int comprimi(FILE *fin, FILE *fout){
    char ch1, ch2;
    int cont = 0, num_car = 0;
    int i = 0;

    ch1 = fgetc(fin);
    while(!feof(fin)){

        if(!feof(fin)){
            ch1 = fgetc(fin);
            if(ch1 == ch2 && cont < 9){
                cont ++;
            }
            else if(cont >= 9){

            }
        }
    }

}
int decomprimi(FILE *fin, FILE *fout){

}