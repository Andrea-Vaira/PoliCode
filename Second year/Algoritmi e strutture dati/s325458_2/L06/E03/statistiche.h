typedef struct {
    int hp, mp, atk, def, mag, spr;
} Statistiche;

void sommaStatistiche(Statistiche *base, Statistiche *mod);
void stampaStatistiche(Statistiche *stat);
