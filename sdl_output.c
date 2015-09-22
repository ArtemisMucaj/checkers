#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sdl_output.h"

SDL_Surface* SDL_init()
{
  SDL_Surface *ecran = NULL;
  if(SDL_Init(SDL_INIT_EVERYTHING)==-1)
    {
      fprintf(stderr,"Errur ini SDL");
      exit(EXIT_FAILURE);
    } 
  ecran=SDL_SetVideoMode(COTE, COTE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  //Test si l'ecran est bien chargé 
  if(ecran == NULL)
    {
      fprintf(stderr,"Impossible de charger le mode video : %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
    }
  
  SDL_WM_SetCaption("Dames Premium", NULL); // Nommage de la fenêtre
  return ecran;
}
void initSDL_damier(SDL_Surface* damierSDL,SDL_Surface* ecran)
{
  SDL_Rect positionFond;
  positionFond.x = 0;
  positionFond.y = 0;
  SDL_BlitSurface(damierSDL,NULL,ecran, &positionFond); 
}

void init_pions(Case* jeu,SDL_Surface* ecran, SDL_Surface* noir, SDL_Surface* blanc,SDL_Surface *noir_dames,SDL_Surface *blanc_dames)
{
  int i,j;
  SDL_Rect positionPion;
  int val = (COTE)/10;

  for(j=0;j<10;j++)
    {
      for(i=0;i<5;i++)
	{
	  if(j%2==0) //Si c'est pair
	    {
	      positionPion.x = (i*2+1)*val;
	      positionPion.y=j*val;
	    }
	  else
	    {
	      // si c'est impair
	      positionPion.x = i*2*val;
	      positionPion.y=j*val;
	    }
	  if(jeu[j*5+i].couleur <= -1)
	    {
	      if(jeu[j*5+i].couleur == -2)
		SDL_BlitSurface(noir_dames,NULL,ecran,&positionPion);
	      else
		SDL_BlitSurface(noir,NULL,ecran, &positionPion);
	    }
	  else{
	    if(jeu[j*5+i].couleur >= 1)
	      {
		if(jeu[j*5+i].couleur ==2)
		  SDL_BlitSurface(blanc_dames,NULL,ecran, &positionPion);
		else
		  SDL_BlitSurface(blanc,NULL,ecran,&positionPion);
	      }
	    else{
	      // Si elle n'as pas de couleur ne rien faire !
	    }
	  }
	}
    }   
  SDL_Flip(ecran);
}

int obtenir_couleur(SDL_Rect position, Case *jeu)
{
  int i,j;
  i=position.x/(COTE/10);
  j=position.y/(COTE/10);
  
  if(j%2 ==0) // Ligne paire
    {
      if(i%2 !=0)//Colonne impaire 
	{
	  return jeu[(i/2)+j*5].couleur;
	}
      else // Colonne paire
	{
	  //Je retourne  car je n'ai pas le droit d'acceder a cette case !
	  return 0;
	}
    }
  else // Ligne impaire
    {
      if(i%2 ==0)//Colonne paire 
	{
	  return jeu[(i/2)+j*5].couleur;
	}
      else // Colonne impaire
	{
	  return 0;
	}

    }
}

SDL_Surface* pions_sauf_un(SDL_Surface* damierSDL,Case *jeu, SDL_Rect position, SDL_Surface* noir, SDL_Surface* blanc,SDL_Surface *noir_dames,SDL_Surface *blanc_dames)
{
  int i,j;
  SDL_Rect positionPion;
  int val = (COTE)/10;
  SDL_Surface *fond;
  int x,y;
  
  fond=damierSDL;
  
  
  x=position.x/val;
  x=x/2; // Lorsqu'on utilise la fonction pions_sauf_un, on suppose qu'un test a déja été effectué avec obtenir_couleur
  //pour savoir qu'on est pas dans une case a laquelle on ne peux acceder. Donc ici toutes nos cases sont accessibles
  //donc on peux diviser par deux notre position obtenue sur un damier "imaginaire" de 10 colonnes !

  y=position.y/val;
  for(j=0;j<10;j++)
    {
      for(i=0;i<5;i++)
	{
	  
	  if(j%2==0) //Si c'est pair
	    {
	      positionPion.x = (i*2+1)*val;
	      positionPion.y=j*val;
	    }
	  else
	    {
	      // si c'est impair
	      positionPion.x = i*2*val;
	      positionPion.y=j*val;
	    }
	  
	  if((i==x) && (j==y))
	    {

	    }
	  else
	    {
	      if(jeu[i+5*j].couleur==0)
		{

		}
	      else
		{
		  if(jeu[i+5*j].couleur>0)
		    {
		      if(jeu[j*5+i].couleur ==2)
			SDL_BlitSurface(blanc_dames,NULL,fond, &positionPion);
		      else
			SDL_BlitSurface(blanc,NULL,fond,&positionPion);
		      //dessinner les blancs
		    }
		  else
		    {
		      if(jeu[j*5+i].couleur == -2)
			SDL_BlitSurface(noir_dames,NULL,fond,&positionPion);
		      else
			SDL_BlitSurface(noir,NULL,fond, &positionPion);
		      //dessinne les noirs
		    }

		}
	    }
	}
    }
  return fond;
}
