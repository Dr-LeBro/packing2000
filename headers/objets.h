#ifndef _H_OBJETS_
#define _H_OBJETS_

typedef struct{
	char nom[50];
	int largeur;
	int hauteur;
} objet;

typedef struct{
	int nb_objets;
	int nb_objets_courant;
	objet* objets;
}Liste;

Liste initialiser_liste();
void reception_objets(Liste* a);
void ajouter_objet(Liste* a, char *nom, int l, int h, int x, int y);
void ajouter_objet_struct(Liste* a, objet* obj);
void supprimer_objet(Liste* a, char *nom);	

#endif
