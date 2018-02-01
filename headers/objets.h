#ifndef _H_OBJETS_
#define _H_OBJETS_

typedef struct{
	int nb_objets;	
	int nb_objets_sol;
	int nb_objets_sol_tmp;
	objet* objets;
	objet* objets_sol;
	objet* objets_sol_tmp;
}Liste;

typedef struct{
	char nom;
	int largeur;
	int hauteur;
	int x;
	int y;
} objet;