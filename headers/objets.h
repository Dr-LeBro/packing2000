#ifndef _H_OBJETS_
#define _H_OBJETS_

typedef struct{
	char nom[50];
	int largeur;
	int hauteur;
} objet;

typedef struct{
	int nb_objets;
	int surface;
	objet* objets_bande;
}bande;

typedef struct{
	int nb_objets;
	objet* objets;
}Liste_objet;

typedef struct{
	int surface;
	int nb_objets;
	int* objets;
	int* orientation;	
}Liste;

typedef struct{
	bande* bande;
	int nb_bandes;
	int surface;
}Liste_Bande;
	
Liste_objet initialiser_liste();
void reception_objets(Liste_objet* a);
void ajouter_objet(Liste_objet* a, char *nom, int l, int h, int x, int y);
void ajouter_objet_struct(Liste_objet* a, objet* obj);
void supprimer_objet(Liste_objet* a, char *nom);
void ajouter_bande_solution(Liste_objet *a, bande *b);
void ajout_bande(Liste_Bande *A, bande *b);
Liste_Bande *initialiser_liste_bande();
Liste initialiser_listeA(int nb_objets);
Liste dupliquer_listeA(Liste* listeA, int nb_objets_total);

#endif

