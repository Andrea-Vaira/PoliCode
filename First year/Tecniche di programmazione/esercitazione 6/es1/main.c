#include <stdio.h>
#include "string.h"
#define MAX 1000

typedef struct {
    // yyyy:mm:dd
    int year;
    int month;
    int day
} date;

typedef struct {
    // hh:mm:ss
    int hour;
    int minute;
    int second;
} time;

typedef struct {
    char codiceTratta[30];
    char partenza[30];
    char destinazione[30];
    date data;
    time oraPartenza;
    time oraArrivo;
    int ritardo;
} tratta;

int getLength();
void getTratte(tratta[], int);
void es1(tratta[], int);
int controllaDate(date data1, date data2, tratta tratta1);
void es2(tratta tratte[], int len);
void printTratta(tratta tratta);
void es3(tratta tratte[], int len);
void es4(tratta tratte[], int len);
void es5(tratta tratte[], int len);

int main() {
    int len = getLength();
    tratta tratte[len];

    getTratte(tratte, len);

    int scelta = 0;

    do {
        printf("1. elencare tutte le corse partite in un certo intervallo di date\n"
               "2. elencare tutti le corse partite da una certa fermata (partenza)\n"
               "3. elencare tutti le corse aventi una specifica destinazione (capolinea)\n"
               "4. elencare tutte le corse che hanno raggiunto la destinazione in ritardo, in un certo intervallo di date\n"
               "5. elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta\n"
               "6. terminare il programma\n"
               "Scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                es1(tratte, len);
                break;
            case 2:
                es2(tratte, len);
                break;
            case 3:
                es3(tratte, len);
                break;
            case 4:
                es4(tratte, len);
                break;
            case 5:
                es5(tratte, len);
                break;
        }
    }while(scelta != 6);




    return 0;
}

int getLength(){
    FILE *fin = fopen("log.txt", "r");
    int len;
    fscanf(fin, "%d", &len);
    return len;
}

void getTratte(tratta tratte[], int len){
    FILE *fin = fopen("log.txt", "r");
    int leng;
    fscanf(fin, "%d", &len);

    for (int i = 0; i < len; i++) {
        fscanf(fin, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d",
               &tratte[i].codiceTratta,
               &tratte[i].partenza,
               &tratte[i].destinazione,
               &tratte[i].data.year,
               &tratte[i].data.month,
               &tratte[i].data.day,
               &tratte[i].oraPartenza.hour,
               &tratte[i].oraPartenza.minute,
               &tratte[i].oraPartenza.second,
               &tratte[i].oraArrivo.hour,
               &tratte[i].oraArrivo.minute,
               &tratte[i].oraArrivo.second,
               &tratte[i].ritardo);

    }
}

void printTratta(tratta tratta){
    printf("%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d\n",
           tratta.codiceTratta,
           tratta.partenza,
           tratta.destinazione,
           tratta.data.year,
           tratta.data.month,
           tratta.data.day,
           tratta.oraPartenza.hour,
           tratta.oraPartenza.minute,
           tratta.oraPartenza.second,
           tratta.oraArrivo.hour,
           tratta.oraArrivo.minute,
           tratta.oraArrivo.second,
           tratta.ritardo);
}

void es1(tratta tratte[], int len){
    date data1, data2;
    printf("Inserire la data inzio: ");
    scanf("%d/%d/%d", &data1.year, &data1.month, &data1.day);

    printf("Inserire la data fine: ");
    scanf("%d/%d/%d", &data2.year, &data2.month, &data2.day);

    for (int i = 0; i < len; i++) {
        if(controllaDate(data1, data2, tratte[i]) == 1){
            printTratta(tratte[i]);
        }
    }

}

int controllaDate(date data1, date data2, tratta tratta1){
    // ret 1 --> se è nel periodo
    int data1Conv = data1.year*365+ data1.month*30+data1.day;
    int data2Conv = data2.year*365+ data2.month*30+data2.day;
    int dataConv = tratta1.data.year*365+ tratta1.data.month*30+tratta1.data.day;

    if(dataConv<data2Conv && dataConv>data1Conv){
        return 1;
    }
    else{
        return 0;
    }
}

void es2(tratta tratte[], int len){
    char tappa[30];
    printf("Inserisci la fermata di partenza: ");
    scanf("%s", &tappa);

    for (int i = 0; i < len; ++i) {
        if(strcmp(tappa, tratte[i].partenza) == 0){
            printTratta(tratte[i]);
        }
    }
}

void es3(tratta tratte[], int len){
    char tappa[30];
    printf("Inserisci la fermata di partenza: ");
    scanf("%s", &tappa);

    for (int i = 0; i < len; ++i) {
        if(strcmp(tappa, tratte[i].destinazione) == 0){
            printTratta(tratte[i]);
        }
    }
}

void es4(tratta tratte[], int len){
    date data1, data2;
    printf("Inserire la data inzio: ");
    scanf("%d/%d/%d", &data1.year, &data1.month, &data1.day);

    printf("Inserire la data fine: ");
    scanf("%d/%d/%d", &data2.year, &data2.month, &data2.day);

    for (int i = 0; i < len; i++) {
        if(controllaDate(data1, data2, tratte[i]) == 1 && tratte[i].ritardo > 0){
            printTratta(tratte[i]);
        }
    }
}

void es5(tratta tratte[], int len){
    char codTratta[30];
    int cont = 0;
    printf("Inserisci il cod. tratta: ");
    scanf("%s", &codTratta);

    for (int i = 0; i < len; i++) {
        if(strcmp(codTratta, tratte[i].codiceTratta) == 0){
            cont += tratte[i].ritardo;
        }
    }
    printf("Il codice tratta %s ha totalizzato un ritardo di %d minuti\n", codTratta, cont);
}