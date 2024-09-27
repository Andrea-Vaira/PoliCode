#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "testo.txt"
#define MAX_CHAR_PER_LINE 25

void process_text(FILE *input, FILE *output) {
    char c, c1;
    int char_count = 0;
    int line_char_count = 0;
    int punctuation_flag = 0; // Flag per segnalare la presenza di segni di punteggiatura

    c = fgetc(input);
    while (c  != EOF) {
        // Sostituzione cifre numeriche con '*'
        if (isdigit(c)) {
            fputc('*', output);
            char_count++;
            line_char_count++;
        }
            // Aggiunta spazio dopo segni di punteggiatura se non già presenti
        else if (ispunct(c)) {
            fputc(c, output);
            char_count++;
            line_char_count++;
            punctuation_flag = 1;
            if (c == '.' || c == '!' || c == '?') {
                punctuation_flag = 1;
            }
        }
            // Trasformazione primo carattere alfabetico dopo punteggiatura in maiuscolo
        else if (isalpha(c)) {
            if (punctuation_flag == 1) {
                c = toupper(c);
                punctuation_flag = 0;
            }
            fputc(c, output);
            char_count++;
            line_char_count++;
        }
            // Aggiunta spazio tra parole
        else if (c == ' ' ) {
            fputc(c, output);
            char_count++;
            line_char_count++;
            punctuation_flag = 0;
        }
        else if (c == '\n') {
            char_count++;
            line_char_count++;
            punctuation_flag = 0;
        }

        // Controllo lunghezza massima della riga
        if (line_char_count >= MAX_CHAR_PER_LINE) {
            // Troncamento delle righe

            if(c!='\n'){
                fprintf(output, " | c:%d\n", char_count ); // -1 per escludere il carattere di a-capo
                char_count = 0;
                line_char_count = 0;
            }
            else{
                fprintf(output, " | c:%d\n", char_count-1 ); // -1 per escludere il carattere di a-capo
                char_count = 0;
                line_char_count = 0;
            }
        }

        // Controllo fine riga
        if (c == '\n') {
            int i = char_count;
            while(i<=MAX_CHAR_PER_LINE){
                fputc(' ', output);
                i++;
            }
            fprintf(output, " | c:%d\n", char_count - 1); // -1 per escludere il carattere di a-capo
            char_count = 0;
            line_char_count = 0;
        }

        c1 = fgetc(input);
        if(c1 == EOF){
            int i = char_count;
            while(i<=MAX_CHAR_PER_LINE){
                fputc(' ', output);
                i++;
            }
            fprintf(output, " | c:%d\n", char_count - 1); // -1 per escludere il carattere di a-capo
            char_count = 0;
            line_char_count = 0;
        }
        c = c1;
    }
}

int main() {
    FILE *input = fopen(INPUT_FILE, "r");
    FILE *output = fopen(OUTPUT_FILE, "w");

    if (input == NULL || output == NULL) {
        printf("Errore nell'apertura dei file.\n");
        return 1;
    }

    process_text(input, output);

    fclose(input);
    fclose(output);

    return 0;
}
