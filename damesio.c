#include <stdio.h>
#include <stdlib.h>
#include "damesio.h"


Case* creer_jeu()
{
  int i,j;
  Case *jeu;
  
  jeu =(Case*)malloc(TAILLE*sizeof(Case));
  if(jeu==NULL)
    {
      printf("Erreur allocation jeu\n");
      return NULL;
    }
  for(i=0;i<TAILLE;i++)
    {
      vider_case(jeu,i); // mets des -1 au tableau eat et move

      jeu[i].pos = i+1;
      if(i<20)
	{
	  jeu[i].couleur = -1;
	}
      else{
	if(i<30)
	  {
	    jeu[i].couleur = 0;
	  }
	else
	  {
	    jeu[i].couleur = 1;
	  }
      }
    }
  return jeu;
}

Case* init_jeu_nul()
{
  int i=0;
  Case *jeu;
  
  jeu =(Case*)malloc(TAILLE*sizeof(Case));
  if(jeu==NULL)
    {
      printf("Erreur allocation jeu\n");
      return NULL;
    }
  for(i=0;i<TAILLE;i++)
    {
      jeu[i].pos = i+1;
      jeu[i].couleur = 0;
      vider_case(jeu,i);
    }

  return jeu;
}

void vider_case(Case* jeu,int pos)
{
  int i;
  
  for(i=0;i<MOVE_MAX;i++)
    {
      jeu[pos].moves[i]=-1;
    }
  
  for(i=0;i<4;i++)
    {
      jeu[pos].eat[i]=-1;
    }
}

void afficher_damier(Case* jeu)
{
  int i;
  for(i=0;i<TAILLE;i++)
    {
      if(i%5==0)
	printf("\n");
      printf("%d ",jeu[i].couleur);
    }
}

void realiser_mouvement(Case *jeu, int pos_dep,int pos_arr)
{
  jeu[pos_arr].couleur=jeu[pos_dep].couleur;
  jeu[pos_dep].couleur=0;
  
  vider_case(jeu,pos_dep);
  vider_case(jeu,pos_arr);
}

void realiser_eat(Case *jeu,int pos_dep, int pos_arr)// Mange le pion entre pos_dep et pos_arr
{
  int i,ligne_paire;
  
  if(pos_arr!=pos_dep)
    {
      if(((pos_dep/5)%2)==0){
	ligne_paire=1;
	
      }
      else{
	
	ligne_paire=-1;
      }
      
      if(abs(jeu[pos_dep].couleur) == 1)// si c'est un pion
	{
	  jeu[(pos_arr + pos_dep + ligne_paire)/2].couleur=0;
	} 
      else
	{
	  if(abs(jeu[pos_dep].couleur) == 2) // si c'est une dame
	    {
	      if((((pos_arr)/5)%2)==0){
		ligne_paire=0;
		
	      }
	      else{
		
		ligne_paire=1;
	      }
	      if((jeu[pos_dep].eat[0]-1) == pos_arr) // Si la 1e case de "eat" est notre pos_arr
		{	  
		  //haut gauche, on va aller une case en arrière vers bas droite et manger le pion dessus		
		  if(ligne_paire){
		    jeu[pos_arr + 5].couleur = 0;
		  }
		  else{
		    jeu[pos_arr + 6].couleur=0;
		  }

		}
	   
	      if((jeu[pos_dep].eat[1]-1) == pos_arr) 
		{
		  // haut droite , on va aller bas gauche
		  if(ligne_paire){
		    jeu[pos_arr + 4].couleur=0;
		  }
		  else{
		    jeu[pos_arr + 5].couleur=0;
		  }
		}
       
	      if((jeu[pos_dep].eat[2]-1) == pos_arr) //2
		{
		  // bas gauche, on va aller haut droite
		  if(ligne_paire){
		    jeu[pos_arr-5].couleur=0;
		  }
		  else{
		    jeu[pos_arr-4].couleur=0;
		  }
		}
	      if((jeu[pos_dep].eat[3]-1) == pos_arr) // 3
		{
		  // bas droite, on va aller haut gauche
		  if(ligne_paire){
		    jeu[pos_arr-6].couleur=0;
		  }
		  else{
		    jeu[pos_arr-5].couleur=0;
		  }
		}
	    
	    }
	
	}
    }
}

void perdu_partie(int *gain, int *existe_prise, Case *jeu, int couleur_jeu, int nb_pieces, Arbre **br_max)
{
  int i;

  for(i=0;i<nb_pieces;i++){
    if(br_max[i] != NULL){
     *existe_prise = 1;
     break;
    }
  }
  
  if(*existe_prise ==0){
    for(i=0;i<TAILLE;i++){
      if(jeu[i].couleur == couleur_jeu){
	if(jeu[i].moves[0]!=-1){
	  break;
	}
      }
    }
    if(i==TAILLE){
     *gain = couleur_jeu;
    }
    else
      {
	*gain = 0;
      }
  }
}
  
  


