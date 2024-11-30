#include <stdio.h>
#include "statistiche.h"

void sommaStatistiche(Statistiche *base, Statistiche *mod) {
    base->hp += mod->hp;
    base->mp += mod->mp;
    base->atk += mod->atk;
    base->def += mod->def;
    base->mag += mod->mag;
    base->spr += mod->spr;

    // Assicura che nessuna statistica sia negativa
    if (base->hp < 0) base->hp = 0;
    if (base->mp < 0) base->mp = 0;
    if (base->atk < 0) base->atk = 0;
    if (base->def < 0) base->def = 0;
    if (base->mag < 0) base->mag = 0;
    if (base->spr < 0) base->spr = 0;
}

void stampaStatistiche(Statistiche *stat) {
    printf("HP: %d, MP: %d, ATK: %d, DEF: %d, MAG: %d, SPR: %d\n",
           stat->hp, stat->mp, stat->atk, stat->def, stat->mag, stat->spr);
}
