#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "remplir_tab.h"

void remplir_moves(int couleur, Case *jeu){
  //Cette fonction permet de remplir les tableaux moves de chaque case
  int i,j,k,l,m,ligne_paire;

	
  if(couleur<0){ //si c'est au tour des noirs
    
    for(i=0;i<TAILLE;i++){ //on parcourt toutes les cases
      j=0;
      if((((jeu[i].pos-1)/5)%2)==0)
	ligne_paire=0;
      else
	ligne_paire=1;
	
      if(jeu[i].couleur == 0) // Si couleur est 0
	jeu[i].moves[0]=-1;

      if(jeu[i].couleur*couleur>0){ //si l'element sur la case est de la bonne couleur
	if(abs(jeu[i].couleur) == 1){ //si c'est un pion
	  if(!ligne_paire){ //s'il est sur une rangee paire
	    if((jeu[i+5]).couleur == 0){ //si la case a gauche est vide
	      jeu[i].moves[j] = jeu[i+5].pos; //on la met dans le tableau move comme possibilite de deplacement
	      j++;
	    }
	    if((jeu[i].pos)%5 != 0){ //si la case n'est pas sur l'etremite droite
	      if((jeu[i+6]).couleur == 0){ //si la case a droite est vide
		jeu[i].moves[j] = jeu[i+6].pos; // on la met dans le tableau move comme possibilite de deplacement
		j++;
	      }
	    }
	    jeu[i].moves[j]=-1; // on met un -1 a la fin des deplacements possibles
	  }
	  else{ //memes operations mais si on est sur une rangee impaire
	    if((jeu[i+5]).couleur == 0){
	      jeu[i].moves[j] = jeu[i+5].pos;
	      j++;
	    }
	    if((jeu[i].pos)%10 != 6){
	      if((jeu[i+4]).couleur == 0){
		jeu[i].moves[j] = jeu[i+4].pos;
		j++;
	      }
	    }
	    jeu[i].moves[j]=-1;                                                                                                                             
	  }
	}

	if(abs(jeu[i].couleur)==2){ // si c'est une dame

	  if(ligne_paire){
	    l=-1;
	    m=6;
	  }
	  else{
	    l=1;
	    m=5;
	  }
	  k=i;
	  
	  while(((k)>4)&&(jeu[k-m].couleur==0)&&(jeu[k-m].pos>0)&&((jeu[k].pos)%10 != 6)){ // on remplit le tableau moves avec les possibilites de mouvement dans la diagonale arriere gauche
	    jeu[i].moves[j] = jeu[k-m].pos;
	    j++;
	    k=k-m;
	    m=m+l;
	    l=-1*l;
	  }

	  if(ligne_paire){
	    l=-1;
	    m=5;
	  }
	  else{
	    l=1;
	    m=4;
	  }
	  // remplissage pour la diagonale arriere droite
	  k=i;
	  while((k>4)&&(jeu[k-m].couleur==0)&&(jeu[k-m].pos>0)&&((jeu[k].pos)%10 != 5)){
	    jeu[i].moves[j] = jeu[k-m].pos;
	    j++;
	    k=k-m;
	    m=m+l;
	    l=-1*l;
	  }


	  if(ligne_paire){
	    l=1;
	    m=4;
	  }
	  else{
	    l=-1;
	    m=5;
	  } 
	  // remplissage pour la diagonale avant gauche
	  k=i;
	  while((k<45)&&(jeu[k+m].couleur==0)&&(jeu[k+m].pos>0)&&((jeu[k].pos)%10 != 6)){
	    jeu[i].moves[j] = jeu[k+m].pos;
	    j++;
	    k=k+m;
	    m=m+l;
	    l=-1*l;
	  }

	  if(ligne_paire){
	    l=1;
	    m=5;
	  }
	  else{
	    l=-1;
	    m=6;
	  }
	  // remplissage pour la diagonale avant droite
	  k=i;
	  while((k<45)&&(jeu[k+m].couleur==0)&&(jeu[k+m].pos>0)&&((jeu[k].pos)%10 != 5)){
	    jeu[i].moves[j] = jeu[k+m].pos;
	    j++;
	    k=k+m;
	    m=m+l;
	    l=-1*l;
	  }

	  jeu[i].moves[j]=-1; // on met un -1 a la fin des deplacements possibles
	}
      }
    }
  }
  // si c'est au tour des blancs
  else{
    for(i=0;i<TAILLE;i++){ //on parcourt toutes les cases
      j=0;
      if((((jeu[i].pos-1)/5)%2)==0)
	ligne_paire=0;
      else
	ligne_paire=1;
	
      if(jeu[i].couleur == 0) // Si couleur est 0
	jeu[i].moves[0]=-1;

      if(jeu[i].couleur*couleur>0){ //si l'element sur la case est de la bonne couleur
	if(abs(jeu[i].couleur) == 1){ //si c'est un pion
	  if(ligne_paire){ //s'il est sur une rangee paire
	    if((jeu[i-5]).couleur == 0){ //si la case a droite est vide 
	      jeu[i].moves[j] = jeu[i-5].pos; //on la met dans le tableau move comme possibilite de deplacement
	      j++;
	    }
	    if((jeu[i].pos)%10 != 4){ //si la case n'est pas sur l'etremite gauche
	      if((jeu[i-6]).couleur == 0){ //si la case a gauche est vide
		jeu[i].moves[j] = jeu[i-6].pos; // on la met dans le tableau move comme possibilite de deplacement
		j++;
	      }
	    }
	    jeu[i].moves[j]=-1; // on met un -1 a la fin des deplacements possibles
	  }
	  else{ //memes operations mais si on est sur une rangee impaire
	    if((jeu[i-5]).couleur == 0){
	      jeu[i].moves[j] = jeu[i-5].pos;
	      j++;
	    }
	    if((jeu[i].pos)%10 != 5){   //
	      if((jeu[i-4]).couleur == 0){
		jeu[i].moves[j] = jeu[i-4].pos;
		j++;
	      }
	    }
	    jeu[i].moves[j]=-1;                                                                                                                             
	  }
	}
	
	if(abs(jeu[i].couleur)==2){ // si c'est une dame
	  
	  if(ligne_paire){
	    l=-1;
	    m=6;
	  }
	  else{
	    l=1;
	    m=5;
	  }
	  k=i;
	  while((k>4)&&(jeu[k-m].couleur==0)&&(jeu[k-m].pos>0)&&((jeu[k].pos)%10 != 6)){ // on remplit le tableau moves avec les possibilites de mouvement dans la diagonale arriere gauche
	    jeu[i].moves[j] = jeu[k-m].pos;
	    j++;
	    k=k-m;
	    m=m+l;
	    l=-1*l;
	  }
	  
	  if(ligne_paire){
	    l=-1;
	    m=5;
	  }
	  else{
	    l=1;
	    m=4;
	  }
	  // remplissage pour la diagonale arriere droite
	  k=i;
	  while((k>4)&&(jeu[k-m].couleur==0)&&(jeu[k-m].pos>0)&&((jeu[k].pos)%10 != 5)){
	    jeu[i].moves[j] = jeu[k-m].pos;
	    j++;
	    k=k-m;
	    m=m+l;
	    l=-1*l;
	  }


	  if(ligne_paire){
	    l=1;
	    m=4;
	  }
	  else{
	    l=-1;
	    m=5;
	  }
	  // remplissage pour la diagonale avant gauche
	  k=i;
	  while((k<45)&&(jeu[k+m].couleur==0)&&(jeu[k+m].pos>0)&&((jeu[k].pos)%10 != 5)){
	    jeu[i].moves[j] = jeu[k+m].pos;
	    j++;
	    k=k+m;
	    m=m+l;
	    l=-1*l;
	  }

	  if(ligne_paire){
	    l=1;
	    m=5;
	  }
	  else{
	    l=-1;
	    m=6;
	  }
	  // remplissage pour la diagonale avant droite
	  k=i;
	  while((k<45)&&(jeu[k+m].couleur==0)&&(jeu[k+m].pos>0)&&((jeu[k].pos)%10 != 5)){
	    jeu[i].moves[j] = jeu[k+m].pos;
	    j++;
	    k=k+m;
	    m=m+l;
	    l=-1*l;
	  }

	  jeu[i].moves[j]=-1; // on met un -1 a la fin des deplacements possibles
	}
      }
    }
  }

}


void remplir_eat(int couleur, int indice, Case *jeu)
{
  int j=0, ligne_paire,l,k,m;

  if (jeu[indice].couleur == 0){ // on regarde si la case examinée est de la bonne couleur
    jeu[indice].eat[0] = -1;
    printf("not your turn!");
    return;
  }

  if((jeu[indice].couleur)*couleur > 0){ // on regarde si on est sur une ligne paire ou impaire
    if((((jeu[indice].pos-1)/5)%2)==0){
      ligne_paire=0;
 
    }
    else{
      
      ligne_paire=1;
    }
    if(abs(jeu[indice].couleur) == 1){ //si c'es un pion
      if(ligne_paire){
	if((((jeu[indice].pos)%10) != 6) && (jeu[indice].pos>10)){ //si le pion n'est ni sur la rangée de gauche si sur celle de haut, il peut manger dans cette direction
	  if(((jeu[indice - 6].couleur * jeu[indice].couleur)<0) && (jeu[indice - 11].couleur == 0)) //si possibilté de manger vers en haut à gauche
	    {
	      jeu[indice].eat[j] = jeu[indice-11].pos;
	      j++;
	    }
	}

	
	// meme operation pour les autres directions
	
	if((((jeu[indice].pos)%10) != 0) && (jeu[indice].pos>10)){ //haut droite
	  if(((jeu[indice - 5].couleur * jeu[indice].couleur)<0) && (jeu[indice - 9].couleur == 0))
	    {
	      jeu[indice].eat[j] = indice - 9 + 1;
	      j++;
	    }

	}

	
	if((((jeu[indice].pos)%10) != 6) && (jeu[indice].pos<41)){ // bas gauche
	  if(((jeu[indice + 4].couleur * jeu[indice].couleur)<0) && (jeu[indice + 9].couleur == 0))
	    {
	      jeu[indice].eat[j] = indice + 9 + 1;
	      j++;
	    }

	}


	if((((jeu[indice].pos)%10) != 0) && (jeu[indice].pos<41)){ //bas droite
	  if(((jeu[indice + 5].couleur * jeu[indice].couleur)<0) && (jeu[indice + 11].couleur == 0))
	    {
	      jeu[indice].eat[j] = indice +11 + 1;
	      j++;
	    }

	}
	
      }

      else{ // si rangee impaire
	
	if((((jeu[indice].pos)%10) != 1) && (jeu[indice].pos>10)){ //si le pion n'est ni sur la rangée de gauche si sur celle du haut, il peut manger dans cette direction
	  
	  if(((jeu[indice - 5].couleur * jeu[indice].couleur)<0) && (jeu[indice - 11].couleur == 0)) //si possibilté de manger vers en haut à gauche
	    {
	      
	      jeu[indice].eat[j] = indice - 11 + 1;
	      j++;
	    }

	}

	// meme operation pour les autres directions

	if((((jeu[indice].pos)%10) != 5) && (jeu[indice].pos>10)){ //haut droite
	  	 
	  if(((jeu[indice - 4].couleur * jeu[indice].couleur)<0) && (jeu[indice - 9].couleur == 0))
	    {
	      
	      jeu[indice].eat[j] = indice -  9 + 1;
	      j++;
	    }

	}


	if((((jeu[indice].pos)%10) != 1) && (jeu[indice].pos<41)){ // bas gauche
	 
	  if(((jeu[indice+5].couleur * jeu[indice].couleur)<0) && (jeu[indice + 9].couleur == 0))
	    {
	      
	      jeu[indice].eat[j] = indice + 9 + 1;
	      j++;
	    }

	}

	if((((jeu[indice].pos)%5) != 0) && (jeu[indice].pos<41)){ //bas droite
	  
	  if(((jeu[indice + 6].couleur * jeu[indice].couleur)<0) && (jeu[indice + 11].couleur == 0))
	    {
	      
	      jeu[indice].eat[j] = indice +11+1;
	      j++;
	    }

	}

      }
    }
    if(abs(jeu[indice].couleur)==2){ // si c'est une dame
      if(ligne_paire){
	l=-1;
	m=6;
      }
      else{
	l=1;
	m=5;
      }
      k=indice;
      while((k>9)&&(jeu[k-m].pos>0)&&((jeu[k].pos)%10 != 1)){ //rangee haut gauche
	if(jeu[k-m].couleur==0){
	k=k-m;
	m=m+l;
	l=-1*l;
	}
	else{
	  if(jeu[k-m].couleur*jeu[indice].couleur<0){
	    k=k-m;
	    m=m+l;
	    l=-1*l;
	    if(jeu[k-m].couleur==0){
	      jeu[indice].eat[j] = jeu[k-m].pos;
	      j++;
	      break;
	    }
	    else{
	      jeu[indice].eat[j] = -1;
	      j++;
	      break;
	    }
	  }
	  else
	    break;
	}
      }

      if(j==0){
	jeu[indice].eat[j]=-1;
	j++;
      }

      if(ligne_paire){
	l=-1;
	m=5;
      }
      else{
	l=1;
	m=4;
      }
      k=jeu[indice].pos-1;
      while((k>9)&&(jeu[k-m].pos>0)&&((jeu[k].pos)%10 != 0)){ //rangee haut droite
	if(jeu[k-m].couleur==0){
	k=k-m;
	m=m+l;
	l=-1*l;
	}
	else{
	  if(jeu[k-m].couleur*jeu[indice].couleur<0){
	    k=k-m;
	    m=m+l;
	    l=-1*l;
	    if(jeu[k-m].couleur==0){
	      jeu[indice].eat[j] = jeu[k-m].pos;
	      j++;
	    break;
	    }
	    else{
	      jeu[indice].eat[j]=-1;
	      j++;
	      break;
	    }
	  }
	  else
	    break;
	}
      }
     if(j==1){
	jeu[indice].eat[j]=-1;
	j++;
      }

 if(ligne_paire){
	l=1;
	m=4;
      }
      else{
	l=-1;
	m=5;
      }
      k=jeu[indice].pos-1;
	while((k<40)&&(jeu[k+m].pos>0)&&((jeu[k].pos)%10 != 1)){ //rangee bas gauche
	  if(jeu[k+m].couleur==0){
	    k=k+m;
	    m=m+l;
	    l=-1*l;
	  }
	  else{
	    if(jeu[k+m].couleur*jeu[indice].couleur<0){
	      k=k+m;
	      m=m+l;
	      l=-1*l;
	      if(jeu[k+m].couleur==0){
		jeu[indice].eat[j] = jeu[k+m].pos;
		j++;
		break;
	      }
	      else{
		jeu[indice].eat[j] = -1;
		j++;
		break;
	      }
	    }
	    else
	      break;
	  }
	}

     if(j==2){
	jeu[indice].eat[j]=-1;
	j++;
      }
	
	if(ligne_paire){
	  l=1;
	  m=5;
	}
	else{
	  l=-1;
	  m=6;
	}
	k=indice;
	while((k<40)&&(jeu[k+m].pos>0)&&((jeu[k].pos)%10 != 0)){ //rangee bas droite
	    if(jeu[k+m].couleur==0){
	      
	      k=k+m;
	      m=m+l;
	      l=-1*l;
	    }
	    else{
	      if((jeu[k+m].couleur)*(jeu[indice].couleur)<0){
	
		k=k+m;
		m=m+l;
		l=-1*l;
		if(jeu[k+m].couleur==0){
		  
		  jeu[indice].eat[j] = jeu[k+m].pos;
		  j++;
		  break;
		}
		else{
		  jeu[indice].eat[j]=-1;
		  j++;
		  break;
		}
	      }
	      else
		break;
	    }
	}
     if(j==3){
	jeu[indice].eat[j]=-1;
	j++;
      }

    }
    
    
  }
}

  
