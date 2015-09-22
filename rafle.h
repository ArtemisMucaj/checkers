#ifndef RAFLE_H
#define RAFLE_H

#include "commun.h"
#include "arbre.h"
#include "remplir_tab.h"

Arbre **prises(Case *jeu, int couleur, int nb_pieces);

Arbre *prise_mult(Case *jeu,int position,int pos_dep,int couleur);

void maxi_abr(Arbre **abr); //pointeur sur Arbre *abr !

Arbre **arbre_maxi_vertical(Case* jeu,int couleur,int nb_pieces); // On travaille sur un pointeur sur un arbre**


#endif
