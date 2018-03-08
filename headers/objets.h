#ifndef _H_OBJETS_
#define _H_OBJETS_

typedef struct{
	char nom[50];
	int largeur;
	int hauteur;
} objet;

typedef struct{
	int nb_objets;
	objet* objets;
}Liste_objet;

typedef struct{
	int surface;
	int surface_perdue;
	int nb_objets;
	int* objets;
	int* orientation;	
}Liste;

Liste_objet initialiser_liste();
void reception_objets(Liste_objet* a);
void ajouter_objet(Liste_objet* a, char *nom, int l, int h, int x, int y);
void ajouter_objet_struct(Liste_objet* a, objet* obj);
void supprimer_objet(Liste_objet* a, char *nom);
Liste initialiser_listeA(int nb_objets);
Liste dupliquer_listeA(Liste* listeA, int nb_objets_total);
void supprimer_listeA(Liste* A);

#endif

