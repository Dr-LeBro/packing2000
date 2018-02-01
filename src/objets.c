#include<stdio.h>
#include<stdlib.h>

void initialiser_liste(){
	Liste *ptr;
	ptr=malloc(sizeof(Liste));
	ptr->nb_objets=0;
	ptr->nb_objets=0;
	ptr->nb_objets=0;
	ptr->objets=NULL;
	ptr->objets_sol=NULL;
	ptr->objets_sol_tmp=NULL;
	return ptr;
}

void receptionner_objets(Liste *a){
	int i=0;
	scanf("%d",a->nb_objets);
	a->objets=malloc(sizeof(objet)*nb_objets);
	while(scanf("%s",&tmp_char)){
		scanf("%d",a->objet[i].largeur);
		scanf("%d",a->objet[î].hauteur);
		a->objet[i].nom=tmp_char;
		a->objet[i].x=-1;
		a->objet[i].y=-1;	
		i++;
	}
}

void ajouter_objet(Liste *a, char nom ,int x, int y){
	a->nb_objets++;
	a->objets=malloc(sizeof(objet)*a->nb_objets);
	a->objet[nb_objets-1].largeur
	a->objet[nb_objets-1].hauteur
	a->objet[nb_objets-1].nom=nom;
	a->objet[nb_objets-1].x=x;
	a->objet[nb_objets-1].y=y;	
}