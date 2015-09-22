#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arbre.h"

void affiche_abr(Arbre *abr)
{
  int i,j;
  Arbre **tmp;
  
  if(abr == NULL)
    return;
  else{
    
    printf("Noeud : %d ",abr->pion);
    tmp=abr->fils;
    printf("( ");
    for(i=0;i<4;i++)
      {
	if(tmp[i]==NULL)
	  {
	    printf("NULL;",i);
	  }
	else
	  {
	    affiche_abr(tmp[i]);
	  }
      }
    printf(" )");
    printf("\n");
  }
}

  
Noeud *creer_noeud(int pos) // FONCTION CORRECTE : Créatio d'un noeud et ses fils NULL(s)
{
  int i;
  Noeud *n =(Noeud*)malloc(sizeof(Noeud));
  n->pion=pos; // On donne la valeuur
  for(i=0;i<4;i++)
    n->fils[i]=NULL; // initialise a NULL les fils
  return n;
}


Arbre **creer_arbre(Case *jeu,int couleur,int nb_pieces)
{
  int i,j=0,color;
  Arbre **abr;

  if(nb_pieces ==0)
    return NULL;
  if(nb_pieces>=0)
    {
      abr =(Arbre**)malloc(nb_pieces*sizeof(Arbre*));//Alloue les pointeurs sur Arbres
    }
  else
    {
      printf("Nb_pieces négatif... %d  Problème...\n", nb_pieces);
      return NULL;
    }

  if(abr==NULL)
    fprintf(stderr,"Erreur allocation arbre\n");
  else{
    for(i=0;i<TAILLE;i++)
      {
	if(jeu[i].couleur != 0)
	  color=(jeu[i].couleur)/abs(jeu[i].couleur);
	else
	  color=0;

	if(color == (couleur/abs(couleur))) // Si c'est la bonne couleur
	  {
	    abr[j]=creer_noeud(jeu[i].pos); // On crée le noeud avec des fils nuls
	    j++;
	  }
      }
  }
  return abr;
}


int max(int a, int b,int c, int d)
{
  if(a>b)
    {
      if(a>c)
	{
	  if(a>d)
	    {
	      return a;
	    }
	  else
	    {
	      return d;
	    }
	}
      else
	{
	  if(c>d)
	    {
	      return c;
	    }
	  else
	    {
	      return d;
	    }
	}
    }
  else{
    if(b>c)
      {
	if(b>d)
	  {
	    return b;
	  }
	else
	  {
	    return d;
	  }
      }
    else
      {
	if(c>d)
	  {
	    return c;
	  }
	else
	  {
	    return d;
	  }
      }
  } 
}


int hauteur(Arbre *abr)
{
  if(abr == NULL)
    {
      return 0;
    }
  else
    {
      return 1 + max(hauteur(abr->fils[0]),hauteur(abr->fils[1]),hauteur(abr->fils[2]),hauteur(abr->fils[3]));
    } 
}

int max_vertical_arbre(Arbre **abr,int nb_pieces) 
{
  int maxi=0,max_tmp,i;
  
  maxi = hauteur(abr[0]);

  for(i=1;i<nb_pieces;i++)
    {
      max_tmp = hauteur(abr[i]);

      if(max_tmp>=maxi)
	maxi = max_tmp;
    }
  return maxi;
}

void supprimer_abr(Arbre **abr)
{
  int i;
  if(*abr!=NULL)
    {
      for(i=0;i<4;i++)
	{
	  if((*abr)->fils[i]!=NULL)
	    {
	      supprimer_abr(&((*abr)->fils[i])); 
	      free((*abr)->fils[i]);
	    }

	}
      free(*abr);
      *abr=NULL;     
    }
}
