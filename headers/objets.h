#ifndef _H_OBJETS_
#define _H_OBJETS_

typedef struct{
	char nom[50];
	int largeur;
	int hauteur;
} objet;


/*Type Bande*/
typedef struct{
	int nb_objets;
	int surface;
	objet* objets_bande;
}bande;

typedef struct{
	int nb_objets;
	int nb_objets_courant;
	int nb_bande_solution;
	objet* objets;
	bande* bande_solution;
}Liste;

Liste initialiser_liste();
void reception_objets(Liste* a);
void ajouter_objet(Liste* a, char *nom, int l, int h, int x, int y);
void ajouter_objet_struct(Liste* a, objet* obj);
void supprimer_objet(Liste* a, char *nom);
void ajouter_bande_solution(Liste *a, bande *b);

#endif
