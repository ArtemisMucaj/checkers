#ifndef ARBRE_H
#define ARBRE_H

#include "commun.h"

void affiche_abr(Arbre *abr);

Noeud *creer_noeud(int pos);

Arbre **creer_arbre(Case *jeu,int couleur,int nb_pieces);

int max(int a, int b,int c, int d);

int hauteur(Arbre *abr);

int max_vertical_arbre(Arbre **abr,int nb_pieces);

void supprimer_abr(Arbre **abr);

#endif
