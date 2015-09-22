#ifndef REMPLIR_TAB_H
#define REMPLIR_TAB_H

#include "commun.h"

//Remplit les déplacements pour tous les pions (&dames) associés a "couleur"
void remplir_moves(int couleur, Case *jeu);

void remplir_eat(int couleur, int indice, Case *jeu); // Remplit le tableau "eat" du pion a la case "indice"

#endif
