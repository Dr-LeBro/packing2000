#ifndef _H_BOITE_
#define _H_BOITE_
#include"objets.h"

/*Type boite*/
typedef struct{
	int largeur;
	int hauteur;
}boite;

/*Type Bande*/
typedef struct{
	int nb_objets;
	int surface;
}bande;

void initialiser_boite(boite *box);
void reception_boite(boite *box);

#endif
