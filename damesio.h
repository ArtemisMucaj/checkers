#ifndef DAMESIO_H
#define DAMESIO_H

#include "commun.h" 

void vider_case(Case* jeu,int pos);
 // Fonction qui mets des -1 aux tableaux "eat" et "moves" a l'indice "pos"
// Important pour l'initialisation du jeu.

Case *creer_jeu(); // Mets le damier de base lorsqu'aucun mouvement n'a été fait !

Case* init_jeu_nul(); // Initialise la damier avec des cases vides partout !

void realiser_mouvement(Case *jeu, int pos_dep,int pos_arr);
// Cette fonction déplace le contenu de la case d'indice "pos_dep" a la case d'indice "pos_arr"

void realiser_eat(Case *jeu,int pos_dep, int pos_arr);
// Cette fonction mange le pion se situant entre "pos_dep" et "pos_arr" (que ce soit un pion ou une dame)

void perdu_partie(int *gain,int *existe_prise,Case *jeu, int couleur, int nb_pieces, Arbre **prises_coul);
// Modifies existe_prise pour savoir si il existe une prise ou pas !
//Fonction qui mets renvoies 0 si le joueur "couleur" n'as pas perdu et +-10 sinon
// Utilisation : En phase de jeu, après avoir rempli l'arbre des prises, on va tester si le joueur perds ou non la partie !

#endif
