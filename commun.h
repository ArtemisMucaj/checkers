#ifndef COMMUN_H
#define COMMUN_H

#define TAILLE 50 // taille du tableau de cases utilisé plus tard
#define MOVE_MAX 18
#define COTE 800

#include "SDL2/SDL.h"

typedef struct _case{
  int couleur,pos;
  int moves[MOVE_MAX];
  int eat[4];  // tableau de pointeurs sur des cases
}Case;

typedef struct _noeud{
  int pion; // pointeur sur un pion !
  struct _noeud *fils[4]; // tableau de pointeurs sur des noeuds/arbres
}Noeud;

typedef Noeud Arbre;

#endif
