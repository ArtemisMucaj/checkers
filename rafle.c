#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rafle.h"

Arbre **prises(Case *jeu, int couleur, int nb_pieces)
{
  int a=0;

  if(nb_pieces == 0)
    return NULL;

  Arbre **abr = creer_arbre(jeu,couleur,nb_pieces);
  int i,j;
 
  for(i=0;i<nb_pieces;i++)
    {
   
      remplir_eat(couleur,abr[i]->pion-1,jeu);
      for(j=0;j<4;j++)
	{
	  abr[i]->fils[j]=prise_mult(jeu,jeu[abr[i]->pion-1].eat[j]-1,abr[i]->pion-1,couleur);
	}
    }
  return abr;
}

Arbre *prise_mult(Case *jeu,int position,int pos_dep,int couleur)
{
  int i,k,a=0;
  Case new_jeu[TAILLE];
  Arbre *tmp=NULL;
 
  if(position+1 == -1)
    {
      // On ne fais rien si il n'y a pas de déplacement possible
    }
  else
    {   
      //Copie du damier
      for(i=0;i<TAILLE;i++)
	{
	  new_jeu[i]=jeu[i];
	}

      tmp=creer_noeud(position+1);
      //On se déplace sur le nouveau "jeu".
      realiser_eat(new_jeu,pos_dep,position);
      realiser_mouvement(new_jeu,pos_dep,position);
      //On remplit les possibilité de manger du pion auquel on s'est déplacés.
      remplir_eat(couleur,position,new_jeu);

      // On relance la fonction sur chacun des fils !
      for(k=0;k<4;k++)
	{
	  tmp->fils[k]=prise_mult(new_jeu,new_jeu[position].eat[k]-1,position,couleur);	  
	}
    }
  return tmp;
}

Arbre **arbre_maxi_vertical(Case *jeu,int couleur, int nb_pieces){ //passage par pointeur pour liberer "abr"

  int max,i;
  Arbre **abr;

  abr=prises(jeu,couleur,nb_pieces);

  max = max_vertical_arbre(abr,nb_pieces);
  printf("\n -- MAX Vertical : %d --\n",max);

  for(i=0;i<nb_pieces;i++)
    {
      if((hauteur(abr[i])<max)||((abr[i]->fils[0]==NULL)&&(abr[i]->fils[1]==NULL)&&(abr[i]->fils[2]==NULL)&&(abr[i]->fils[3]==NULL)))
	{
	  //On ne fais rien
	  supprimer_abr(&abr[i]);
	}
      else
	{ 
	  // la hauteur de l'arbre n'est pas inférieure au max
	  // on garde donc ce sous arbre, réduit a son sous arbre maximal!
	  maxi_abr(&abr[i]);
	}
    }
  return abr;
}

void maxi_abr(Arbre **abr)
{
  int max_f1,max_f2,max_f3,max_f4,maximum;
  
  if(*abr == NULL)
    {
      /* Cas ou abr est vide ! */
    }
  else{
    max_f1 = hauteur((*abr)->fils[0]);
    max_f2 = hauteur((*abr)->fils[1]);
    max_f3 = hauteur((*abr)->fils[2]);
    max_f4 = hauteur((*abr)->fils[3]);

    maximum = max(max_f1,max_f2,max_f3,max_f4);
    
    if(max_f1 < maximum)
      { // Si plus petit que le max : on le supprime
	supprimer_abr(&(*abr)->fils[0]);
      }
    else
      {  // Sinon on regardes le max du sous arbre !
	maxi_abr(&(*abr)->fils[0]);
      }
    
    if(max_f2 < maximum) 
      {
	supprimer_abr(&(*abr)->fils[1]);
      }
    else 
      { 
	maxi_abr(&(*abr)->fils[1]);
      }

    if(max_f3 < maximum) 
      {
	supprimer_abr(&(*abr)->fils[2]);
      }
    else 
      { 
	maxi_abr(&(*abr)->fils[2]);
      }

    if(max_f4 < maximum) 
      {
	supprimer_abr(&(*abr)->fils[3]);
      }
    else 
      { 
	maxi_abr(&(*abr)->fils[3]);
      }

  }
}

