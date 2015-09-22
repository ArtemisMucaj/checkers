#include <stdlib.h>
#include <stdio.h>

#include "commun.h"
#include "arbre.h"
#include "rafle.h"
#include "remplir_tab.h"
#include "damesio.h"
#include "sdl_output.h"

#define valu 80 // (COTE)/10, valu*valu pixels est la taille "image" d'une case sur le damier !

int main()
{
  int i=0,k, nb_pieces_blanc, nb_pieces_noir,gain=0,couleur_jeu,color; /* Color variable pour ne pas écraser la valeur de la variable couleur déclarée plus bas ! */
  int *nb_pieces; //Pointera vers l'adresse de nb_pieces_blanc ou nb_pieces_noir pour modifier directement la valeur 
  Case *jeu;
  Arbre **br=NULL,**br_max = NULL;
  Arbre **tmp = NULL; // Variable temporaire d'arbre !
  
  int existe_prise=0, multiple=-2, indice_multiple=-1;
  /*prise : variable de test pour savoir si il existe une prise
    multiple : variable de test pour voir si la position clickée correspond a qqechose dans l'arbre des prises, si elle vaut 0 , piece figée, 1 : il y a prise possible, -1 deplacements possibles
    -2 est sa valeur neutre : c'est à dire qu'il faudra la recalculer
    indice_multiple : variable contenant l'indice dans notre arbre de l'endroit ou on a clické ou alors -1 !*/
  
  /* Variables a utiliser pour la boucle de gestion des event */
  SDL_Event event;
  int continuer = 1,couleur=0;
  SDL_Rect position,initiale,pos_dep,clipper,origine;
  int ecran_bis = 0,ligne,col,dep_ligne,dep_col;
 
  origine.x=0;
  origine.y=0;

  SDL_Surface* fond;
  
  jeu=creer_jeu();

  nb_pieces_blanc = 20;
  nb_pieces_noir =20;

  /* JEU TEST 
  jeu=init_jeu_nul();
  jeu[22].couleur=2;
  jeu[13].couleur=-1;
  jeu[4].couleur=-1;

  nb_pieces_blanc=1;
  nb_pieces_noir=2;*/

 //Demarrer SDL 
  SDL_Surface *ecran = NULL;
  ecran=SDL_init();
  //On charge les images des pions et damier
  SDL_Surface *noir=SDL_LoadBMP("noir.bmp");
  SDL_Surface *blanc = SDL_LoadBMP("blanc.bmp");
  SDL_Surface *damierSDL = SDL_LoadBMP("damier.bmp");

  SDL_Surface *noir_dames= SDL_LoadBMP("noir_dames.bmp");
  SDL_Surface *blanc_dames= SDL_LoadBMP("blanc_dames.bmp");

  /* FIN */
  fond = SDL_LoadBMP("menu.bmp");
  SDL_BlitSurface(fond,NULL,ecran,&origine);
  SDL_Flip(ecran);

  while(continuer == 1)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
	{
	case SDL_QUIT:
	  continuer=0;
	  gain = 100;
	  break;
	case SDL_KEYUP:
	  switch(event.key.keysym.sym)
	    {
	    case SDLK_RETURN:
	      continuer =-1;
	      gain=0;
	      break;
	    }
	}
    }
  SDL_FreeSurface(fond);
  /* DEBUT DU JEU 
     On affiche un écran blanc avec tapez entrez pour jouer */
  
  SDL_SetColorKey(blanc, SDL_SRCCOLORKEY, SDL_MapRGB(blanc->format, 220, 255, 255));
  SDL_SetColorKey(noir, SDL_SRCCOLORKEY, SDL_MapRGB(noir->format, 220, 255, 255)); 
  SDL_SetColorKey(noir_dames, SDL_SRCCOLORKEY, SDL_MapRGB(noir->format, 220, 255, 255)); 
  SDL_SetColorKey(blanc_dames, SDL_SRCCOLORKEY, SDL_MapRGB(noir->format, 220, 255, 255)); 
 
  initSDL_damier(damierSDL,ecran);
  init_pions(jeu,ecran,noir,blanc,noir_dames,blanc_dames);
  // Fonction qui place les pieces sur le damier/elle recharge la page

  // BOUCLE PRINCIPALE DU JEU
  couleur_jeu = 1; // Les blancs commencent la partie 
  while(gain == 0) // Tant que personne n'a gagné !
    {
      printf("\n ---- Nouveau tour ---- \n");

      afficher_damier(jeu);

      /*On reinitialise les tableaux eat et moves pour une nouvelle utilisation propre */
      for(i=0;i<TAILLE;i++)
	vider_case(jeu,i);
      //On transforme en dames les pions arrivés sur la dernière ligne (s'il y en a)
      for(i=0;i<5;i++)
	if(jeu[i].couleur==1){
	  jeu[i].couleur = 2;
	  printf("LES BLANCS GAGNENT UNE DAME");
	}
      
      for(i=45;i<TAILLE;i++)
	if(jeu[i].couleur == -1){
	  jeu[i].couleur = -2;
	  printf("LES NOIRS GAGNENT UNE DAME");
	}

      // On va maintenant creer l'arbre de tous les déplacements possibles
      //Puis ne garder que les déplacements max
      if(couleur_jeu == 1)
	{
	  nb_pieces = &nb_pieces_blanc;
	}
      else
	{
	  nb_pieces = &nb_pieces_noir;
	}
      

      if(*nb_pieces == 0)
	{
	  gain = couleur_jeu; // C'est couleur_jeu qui a perdu, "gain" est un nom trompeur ...
	  break;
	}

      printf("\n-- Joueur %d as %d pieces -- ",couleur_jeu,*nb_pieces);

      br_max=arbre_maxi_vertical(jeu,couleur_jeu,*nb_pieces);
      remplir_moves(couleur_jeu,jeu);

      for(i=0;i<*nb_pieces;i++)
	affiche_abr(br_max[i]);

      gain=0;
      existe_prise=0;
      perdu_partie(&gain,&existe_prise,jeu,couleur_jeu,*nb_pieces, br_max); // FONCTION A REVOIR
      /* Apres cette fonction "existe_prise" est prete a être utilisée dans la suite du programme ! */
      printf("\n-- Variables : existe_prise:%d; gain:%d; --",existe_prise,gain);

      if(gain!=0)
	break;

      //Boucle des evenements souris
      origine.x=0;
      origine.y=0;
      continuer=1;
      ecran_bis = 0;

      while(continuer==1)
	{
	  SDL_WaitEvent(&event);
	  switch(event.type)
	    {
	    case SDL_QUIT:
	      continuer = -1;
	      break;
	    case SDL_MOUSEBUTTONDOWN:
	      //Position initiale ou l'on clic, on desirera la garder pour plus tard
	      initiale.x=event.button.x;
	      initiale.y=event.button.y;

	      // On stock la position initiale dans une variable position que l'on pourra modifier!
	      position.x=initiale.x; 
	      position.y=initiale.y;

	      dep_col=position.x/valu; // Obtient un indice de colonne de la position initiale
	      dep_ligne=position.y/valu; // Obtient un indice de ligne	     	     

	      // On garde la couleur du pion cliqué ici.
	      couleur = obtenir_couleur(initiale,jeu);
	      if(couleur != 0){  // ON TEST LA COULEUR : Très important car si la couleur est nulle on n'as pas le droit d'utiliser pions_sauf_un !
		color= couleur/abs(couleur);
		
		// Renormage de "couleur"	   
		if(color != couleur_jeu) // Si la couleur clickée est differente de celle du joueur en cours on quitte le switch pour y re-rentrer
		  {

		  }
		else
		  {		    
		    if(multiple == -2) // Si multiple est a sa valeur neutre, on la recalcule 
		      {
			/*On verifie si on a la possibilité de déplacer quoi que ce soit!*/
			if(existe_prise ==0)
			  {
			    /*On a le droit d'acceder a cette case car le test de couleur avant
			      nous assure d'avoir éliminé les cases qui sont inaccessibles */
			    if(jeu[(dep_col/2)+dep_ligne*5].moves[0]==-1) //Pas de déplacements possible
			      {
				multiple = 0; /* Figé */
			      }
			    else // Il existe des déplacements 
			      {
				multiple = -1; /* Déplacement possible */
			      }  
			  }
			else{
			  /*Il existe une prise */
			  /* On va parcourir l'arbre pour essayer de voir si (dep_col/2)+dep_ligne*5 +1
			     est dedans 
			    ( On dessine un damier 10*10 alors que notre damier virtuel est 10*5, donc on a besoin de diviser 
			     par deux la composante x(colonne) de position pour obtenir le bon endroit dans le damier */
			  if(indice_multiple == -1)
			    for(i=0;i<*nb_pieces;i++)
			      {			      
				if(br_max[i]!=NULL)
				  {      
				    if(((dep_col/2)+dep_ligne*5 + 1) == br_max[i]->pion)
				      indice_multiple =i;
				  }
			      }

			  if(indice_multiple != -1){
			    multiple =1;
			    if(br_max[indice_multiple]->fils !=NULL)
			      tmp = br_max[indice_multiple]->fils;
			  }
			  else
			    multiple= 0;
			}
		      }

		    printf("\n | Position: %d ; multiple: %d ; indice_multiple: %d | \n ",(dep_col/2)+dep_ligne*5+1,multiple,indice_multiple);
		    
		    //Cree une surface avec les pions sauf celui aux coord "initiale"
		    if(multiple != 0){
		      damierSDL=SDL_LoadBMP("damier.bmp"); // On remet le damier d'origine car il est modifié par "pions_sauf_un"!
		      fond=pions_sauf_un(damierSDL,jeu,initiale,noir,blanc,noir_dames,blanc_dames);
		      SDL_BlitSurface(fond,NULL, ecran, &origine); 
		    }
		    ecran_bis=1; // Variable de test pour ne rien faire dans mousemotion si pas de click ou si mauvais click
		  }
	      }
	      
	      break;
	    case SDL_MOUSEMOTION:

	      if(ecran_bis == 0)
		{
		  //ICI ON NE FAIS RIEN
		}
	      else
		{
		  if(multiple == 0) // Si bon clic mais pion "figé"
		    {

		    }
		  else
		    {
		      clipper.x = position.x; // CLIPPER 
		      clipper.y = position.y;// augmante la fluidité !
		      clipper.h = noir->h;// On stock les coordonnées et la taille
		      clipper.w = noir->w;// a l'endroit ou est notre pion
		      
		      if(couleur >= 1)
			{
			  if(couleur == 2)
			    {
			      SDL_BlitSurface(fond, &clipper, ecran, &position); 
			      //On reactualise les coordonnees.
			      position.x=event.motion.x-(valu/2);
			      position.y=event.motion.y-(valu/2);
			      SDL_BlitSurface(blanc_dames, NULL, ecran, &position); // On ajoute le pion.
			    }
			  else{
			    //On blitt une partie de "fond", de taille "clipper" sur l'écran
			    SDL_BlitSurface(fond, &clipper, ecran, &position); 
			    //On reactualise les coordonnees.
			    position.x=event.motion.x-(valu/2);
			    position.y=event.motion.y-(valu/2);
			    SDL_BlitSurface(blanc, NULL, ecran, &position); // On ajoute le pion.
			  }
			}
		      else 
			{
			  if(couleur == -1)
			    {
			      SDL_BlitSurface(fond, &clipper, ecran, &position);
			      position.x=event.motion.x-(valu/2);
			      position.y=event.motion.y-(valu/2);
			      SDL_BlitSurface(noir, NULL, ecran, &position);
			    }
			  else
			    {
			      if(couleur==-2)
				{
				  SDL_BlitSurface(fond, &clipper, ecran, &position);
				  position.x=event.motion.x-(valu/2);
				  position.y=event.motion.y-(valu/2);
				  SDL_BlitSurface(noir_dames, NULL, ecran, &position);
				}
			      else{

			      }
			    }
			}
		      SDL_Flip(ecran);
		    }		  
		}
	      
	      break;
	    case SDL_MOUSEBUTTONUP:
	      if(ecran_bis == 0)
		{
		  // On ne fais rien si on a pas modifié cette variable
		}
	      else{
		/* "initiale" est la position de click, si on veux une position propre sur le damier on fait ceci! */
		initiale.x = dep_col*valu;// Coordonnées colonne
		initiale.y= dep_ligne*valu; // Coordonnées ligne			
		
		/* -----------------------------------------------------------------------------------------------------------------------------------------------------*/
		if(multiple == 0)
		  {
		    multiple = -2; /* On remet a sa valeur "neutre" cette variable, ainsi au prochain passage dans la boucle, elle pourra être modifiée !*/
		    ecran_bis = 0;
		  }
		else
		  { /* Si on peux soit manger, soit bouger! */
		    /* Après avoir bougé la souris, le pion va se blitter sur la derniere position avant de relacher la souris, cette position ne sera pas propre
		       car le pion sera placée n'importe comment dans la case du damier, on redessine donc le damier sans le pion, puis on blittera à une position
		       dite "propre" */

		    SDL_BlitSurface(fond, NULL, ecran, &origine); 
	
		    /* On obtiens la position au relachement du click */
		    position.x=event.button.x;
		    position.y=event.button.y;
		    
		    /* On va calculer la position "propre" de "position" 
		       la division étant entière on se retrouve avec une position 
		       en fonction de "valu" */

		    position.x=position.x/valu;
		    position.y=position.y/valu; 
		    position.x = position.x * valu;
		    position.y= position.y * valu; 
		    		    
		    /* C'est maintenant que l'on doit tester si le déplacement souhaite a "position" est correct ou pas
		       et agir en conséquence */
		    
		    /* Conversion de position (x,y) vers position dans le damier a 50cases ! */
		    col = position.x/valu;
		    ligne=position.y/valu;
		    
		    //Pour acceder a la bonne case : (col/2)+ligne*5; ATTENTION : DEPEND DE LA PARITE DE "col" et "ligne", car certains endroits sur notre damier 10*10 sont 
		    //Inaccessibles sur le damier 10*5
		    
		    if(((ligne%2 == 0)&&(col%2 !=0))||((ligne%2 !=0)&&(col%2 ==0))) /* Si ligne paire et colonne impaire ou ligne impaire et colonne paire !*/
		      {
			/* --------------------------------------------------------------------------------------------------------------------*/
			/* Cette endroit est accessible, on test si on a le droit de s'y placer! */
			/* Si c'est un déplacement */
			if(multiple == -1)
			  {
			    multiple = -2;
			    for(i=0;i<MOVE_MAX;i++)
			      {  /* Si la position d'arrivée correspond a un element du tableau "move" de la position de départ, on peux réaliser le mouvement!*/
				if((1+(col/2)+ligne*5) == jeu[(dep_col/2)+dep_ligne*5].moves[i]){
				  realiser_mouvement(jeu,(dep_col/2)+dep_ligne*5,(col/2)+ligne*5);
				  /* On dessine la piece a sa nouvelle position */
				  damierSDL=SDL_LoadBMP("damier.bmp"); // on recharge damierSDL car il est modifié par l'appel a pions_sauf_un au début de la boucle, donc
				  // si on essaies d'actualiser le damier ici,cela ne marchera pas!
				  /* On redessine tout sauf l'origine, puis on remet l'origine pour actualiser le damier */
				  SDL_BlitSurface(damierSDL,NULL,ecran,&origine);
				  init_pions(jeu,ecran,noir,blanc,noir_dames,blanc_dames);
				  			  
				  /* Fin du dessin */
				  continuer=0;
				}	      
			      }
			    if(continuer == 1) /* Si on a pas réalisé le mouvement on redessine la pièce a sa position initiale !*/
			      {
				damierSDL=SDL_LoadBMP("damier.bmp"); // on recharge damierSDL car il est modifié par l'appel a pions_sauf_un au début de la boucle, donc
				// si on essaies d'actualiser le damier ici,cela ne marchera pas!
				/* On redessine tout sauf l'origine, puis on remet l'origine pour actualiser le damier */
				SDL_BlitSurface(damierSDL,NULL,ecran,&origine);
				init_pions(jeu,ecran,noir,blanc,noir_dames,blanc_dames);
			      }
			  }
			else /* Si c'est une prise */
			  {
			    /* tmp = br[indice_multiple]->fils est ce sur quoi on va travailler */
			    if((tmp[0] != NULL)||(tmp[1] != NULL)||(tmp[2] != NULL)||(tmp[3] != NULL))
			      {
				for(i=0;i<4;i++)
				  {
				    /* Pour chaque sous fils de notre arbre tmp on va tester si il correspond a l'endroit ou l'on a clické */
				    if(tmp[i] != NULL)
				      {
					if(((col/2)+ligne*5 +1) == tmp[i]->pion) /* Si l'endroit ou on veux le déplacer corrspond a un element de mon arbre */
					  {
					    realiser_eat(jeu,(dep_col/2)+dep_ligne*5,(col/2)+ligne*5);
					    realiser_mouvement(jeu,(dep_col/2)+dep_ligne*5,(col/2)+ligne*5);
					    /* Dessinner la piece */	
					    damierSDL=SDL_LoadBMP("damier.bmp"); // on recharge damierSDL car il est modifié par l'appel a pions_sauf_un au début de la boucle, donc
					    // si on essaies d'actualiser le damier ici,cela ne marchera pas!
					    /* On redessine tout sauf l'origine, puis on remet l'origine pour actualiser le damier */
					    SDL_BlitSurface(damierSDL,NULL,ecran,&origine);
					    init_pions(jeu,ecran,noir,blanc,noir_dames,blanc_dames);
					    /* Il faut retirer un pion a l'adversaire*/	

					    br_max[indice_multiple]=tmp[i]; // Dans br_max[indice_multiple] on passe au prochain étage de l'arbre
					    tmp=tmp[i]->fils;
					    multiple =-2;
					    indice_multiple = -1; 
					    /* On quitte la boucle for */
					    i=5;
					    // 
					    if(couleur_jeu == 1){
					      nb_pieces_noir--;
					    }
					    else{
					      nb_pieces_blanc--;
					    }
					    
					    /* Ici on va tester si le sous arbre est vide et quitter si
					       c'est le cas! */
					    if((tmp[0] == NULL)&&(tmp[1] == NULL)&&(tmp[2] == NULL)&&(tmp[3] == NULL)){
					      continuer=0; 
					      break;
					    }
					  }
					else
					  { /* Si c'est au mauvais endroit on le redessine ! */
					     damierSDL=SDL_LoadBMP("damier.bmp"); // on recharge damierSDL car il est modifié par l'appel a pions_sauf_un au début de la boucle, donc
					    // si on essaies d'actualiser le damier ici,cela ne marchera pas!
					    /* On redessine tout sauf l'origine, puis on remet l'origine pour actualiser le damier */
					    SDL_BlitSurface(damierSDL,NULL,ecran,&origine);
					    init_pions(jeu,ecran,noir,blanc,noir_dames,blanc_dames);
					    // dessiner_pion(blanc, noir, ecran,couleur,initiale);
					    /*On remet multiple et indice_multiple a leur valeur neutre pour qu'elles soient recalculées au prochain passage
					      dans la boucle */ 
					    indice_multiple = -1;
					    multiple = -2;
					  }
					/* Ici on va tester si le sous arbre est vide et quitter si
					   	   c'est le cas! */
				      }
				  }			
			      }
			    else
			      { /* tmp->fils[i] est NULL on a rien a faire dans ce cas la! */

			      } 
			  }
			/* -------------------------------------------------------------------------------------------------------------------*/			
		      }
		    else
		      {
			// ENDROIT INACCESSIBLE, ON REDESSINE LA PIECE A SA POSITION INITIALE ( corresponds aux cases blanches du damier)
			damierSDL=SDL_LoadBMP("damier.bmp"); // on recharge damierSDL car il est modifié par l'appel a pions_sauf_un au début de la boucle, donc
			// si on essaies d'actualiser le damier ici,cela ne marchera pas!
			/* On redessine tout sauf l'origine, puis on remet l'origine pour actualiser le damier */
			SDL_BlitSurface(damierSDL,NULL,ecran,&origine);
			init_pions(jeu,ecran,noir,blanc,noir_dames,blanc_dames);
			//	dessiner_pion(blanc, noir, ecran,couleur,initiale);
			multiple = -2;
		      }
		    
		    if(multiple != 0)
		      SDL_FreeSurface(fond); // On libère le fond
		    
		    ecran_bis = 0;
		    SDL_Flip(ecran);
		  }
	      }	      
	      break;     	      
	    }	  
	}
      
      //Fin evenements souris
      printf("\n-- Changement couleur --");
      
      for(i=0;i<*nb_pieces;i++)
	{
	  supprimer_abr(&br_max[i]);
	}
      br_max=NULL;

      if(continuer == -1) // Si on quitte notre boucle avec pour option "quitter le jeu"
	break;

      couleur_jeu=couleur_jeu*(-1);     
    }

  printf("\n\n------------------ MERCI D'AVOIR JOUE -----------------\n\n");
  // FIN BOUCLE PRINCIPALE
  free(jeu);
  // FIN
  //Quitter SDL 
  SDL_Quit(); 
  
  return 0;
}	
