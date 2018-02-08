#ifndef _H_OBJETS_
#define _H_OBJETS_

typedef struct{
	int nb_objets;	
	objet* objets;
}Liste;

typedef struct{
	char nom;
	int largeur;
	int hauteur;
	int x;
	int y;
} objet;

#endif
