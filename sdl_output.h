#ifndef SDL_OUTPUT_H
#define SDL_OUTPUT_H

#include "commun.h"
#include "damesio.h"
#include "remplir_tab.h"
#include "rafle.h"
#include "arbre.h"

SDL_Surface* SDL_init(); 
// Initialise la SDL 

void initSDL_damier(SDL_Surface* damierSDL,SDL_Surface* ecran);
// Initialise le damier : cad la surface en forme de "damier"! 

void init_pions(Case* jeu,SDL_Surface* ecran, SDL_Surface* noir, SDL_Surface* blanc,SDL_Surface *noir_dames,SDL_Surface *blanc_dames);
// Place les pions comme ils sont lors de la configuration "jeu" 

int obtenir_couleur(SDL_Rect position, Case *jeu); 
// Permet d'obtenir la couleur de la piece aux coordonnées Position.x et Position.y

SDL_Surface* pions_sauf_un(SDL_Surface* damierSDL,Case *jeu,SDL_Rect position, SDL_Surface* noir, SDL_Surface* blanc,SDL_Surface *noir_dames,SDL_Surface *blanc_dames);
//pion_sauf_un : cree une surface avec les pions sauf celui aux coord "position" qui ne sera pas affiché; Cette fonction est utile pour les déplacements afin de ne pas avoir a redessinner le damier en entier a chaque mouvement de la souris.
// Attention : cette fonction n'est utilsable que si le resultat d'obtenir_couleur a la meme "position" est different de 0 !

/* Dessine un pion a "coord" */
void dessiner_pion(SDL_Surface *blanc, SDL_Surface *noir, SDL_Surface* ecran,SDL_Surface *noir_dames,SDL_Surface *blanc_dames, int couleur, SDL_Rect coord);

#endif
