#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int matchRegexp(const char *src, const char *regexp);
char *cercaRegexp(char *src, char *regexp);

int main() {
    char src[] = "Questo è un test di voto e moto e anche Voto e Foto";
    char regexp[] = "\\aoto";


    char *result = cercaRegexp(src, regexp);

    if (result) {
        printf("Occorrenza trovata: %s\n", result);
    } else {
        printf("Nessuna occorrenza trovata.\n");
    }

    return 0;
}

int matchRegexp(const char *src, const char *regexp) {
    // Caso base: se la regexp è finita, abbiamo una corrispondenza
    if (*regexp == '\0') {
        return 1;
    }

    // Se la stringa src è finita, ma la regexp non lo è, non c'è corrispondenza
    if (*src == '\0') {
        return 0;
    }

    // Gestione del metacarattere '.'
    if (*regexp == '.') {
        return matchRegexp(src + 1, regexp + 1);
    }

    // Gestione delle parentesi '[]' e '[^...]'
    if (*regexp == '[') {
        int negazione = 0;
        regexp++;
        if (*regexp == '^') {
            negazione = 1;
            regexp++;
        }

        int match = 0;
        while (*regexp && *regexp != ']') {
            if (*regexp == *src) {
                match = 1;
            }
            regexp++;
        }

        if (*regexp == ']') {
            // Se corrisponde e non c'è negazione, oppure se non corrisponde ma c'è negazione
            if ((match && !negazione) || (!match && negazione)) {
                return matchRegexp(src + 1, regexp + 1);
            }
        }
        return 0; // Non corrisponde
    }

    // Gestione delle sequenze di escape '\a' e '\A'
    if (*regexp == '\\') {
        regexp++;
        if (*regexp == 'a' && islower(*src)) {
            return matchRegexp(src + 1, regexp + 1);
        } else if (*regexp == 'A' && isupper(*src)) {
            return matchRegexp(src + 1, regexp + 1);
        }
        return 0; // Non corrisponde
    }

    // Confronto normale per caratteri alfabetici
    if (*regexp == *src) {
        return matchRegexp(src + 1, regexp + 1);
    }

    return 0; // Non corrisponde
}

char *cercaRegexp(char *src, char *regexp) {
    // Scorri tutta la stringa `src` e prova a confrontare ogni sottostringa con la regexp
    if (*src == '\0') {
        return NULL; // Fine della stringa senza corrispondenza
    }

    // Se c'è corrispondenza a partire da questo punto della stringa
    if (matchRegexp(src, regexp)) {
        return src;
    }

    // Prova con la sottostringa successiva
    return cercaRegexp(src + 1, regexp);
}