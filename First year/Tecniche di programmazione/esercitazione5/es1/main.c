#include <stdio.h>

#define MAX_TEAMS 20
#define MAX_DAYS 20
#define filename "data.txt"
int matrix[MAX_TEAMS][MAX_DAYS];
int teams, days;

void caricaMatrice();

int main() {
    caricaMatrice();
    
    for (int day = 0; day < days; day++) {
        int max_points = -1;
        int top_team_index = -1;

        // Calcolo dei punti totali per ogni squadra fino al giorno corrente
        for (int team = 0; team < teams; team++) {
            int total_points = 0;
            for (int d = 0; d <= day; d++) {
                total_points += matrix[team][d];
            }

            // Verifica se questa squadra è in cima alla classifica
            if (total_points > max_points) {
                max_points = total_points;
                top_team_index = team;
            }
        }
        printf("Giornata %d: Squadra in cima alla classifica: %d\n", day + 1, top_team_index + 1);
    }

    return 0;
}


void caricaMatrice(){
    // Apertura del file
    FILE *file = fopen(filename, "r");

    fscanf(file, "%d %d", &teams, &days);

    for (int i = 0; i < teams; i++) {
        for (int j = 0; j < days; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    fclose(file);
}