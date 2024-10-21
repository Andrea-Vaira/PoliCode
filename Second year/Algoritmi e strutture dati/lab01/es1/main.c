#include <stdio.h>
#include <ctype.h>

#define LEN 256

int matchRegexp(const char *src, const char *regexp);
char *cercaRegexp(char *src, char *regexp);

int main() {
    char src[LEN];
    char regexp[LEN];

    printf("Inserisci il testo: ");
    scanf("%s", src);
    printf("Inserisci la regex: ");
    scanf("%s", regexp);

    char *result = cercaRegexp(src, regexp);

    if (result) {
        printf("Occorrenza trovata: %s\n", result);
    } else {
        printf("Nessuna occorrenza trovata.\n");
    }

    return 0;
}

int matchRegexp(const char *src, const char *regexp) {
    if (*regexp == '\0') {
        return 1;
    }

    if (*src == '\0') {
        return 0;
    }

    if (*regexp == '.') {
        return matchRegexp(src + 1, regexp + 1);
    }

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
            if ((match && !negazione) || (!match && negazione)) {
                return matchRegexp(src + 1, regexp + 1);
            }
        }
        return 0;
    }

    if (*regexp == '\\') {
        regexp++;
        if (*regexp == 'a' && islower(*src)) {
            return matchRegexp(src + 1, regexp + 1);
        } else if (*regexp == 'A' && isupper(*src)) {
            return matchRegexp(src + 1, regexp + 1);
        }
        return 0;
    }

    if (*regexp == *src) {
        return matchRegexp(src + 1, regexp + 1);
    }

    return 0;
}

char *cercaRegexp(char *src, char *regexp) {
    if (*src == '\0') {
        return NULL;
    }

    if (matchRegexp(src, regexp)) {
        return src;
    }

    return cercaRegexp(src + 1, regexp);
}