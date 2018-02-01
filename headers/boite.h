#ifndef _H_BOITE_
#define _H_BOITE_

void initialiser_boite(boite *box);
void reception_boite(boite *box);

/*Type boite*/
typedef struct{
	int largeur;
	int hauteur;
}boite;