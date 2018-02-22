/****************************************/
/* FONCTIONS OPERATIONS OBJETS/LISTES	*/
/****************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../headers/objets.h"
#include"../headers/boite.h"

/*Initialisation de liste d'objets, renvoi pointeur nouvelle liste*/
Liste_objet initialiser_liste(){
	Liste_objet *ptr;
	ptr=malloc(sizeof(Liste));
	ptr->nb_objets=0;
	ptr->objets=NULL;
	return *ptr;
}

/*Receptions objets pour liste depuis generateur*/
void reception_objets(Liste_objet* a){
	int i=0;
	char tmp_char[50];
	scanf("%d",&a->nb_objets);
	a->objets=malloc(sizeof(objet)*a->nb_objets);
	while(scanf("%s",tmp_char) > 0){
		if(i>=a->nb_objets){printf("Trop d'objets\n"); break;}
		scanf("%d",&a->objets[i].largeur);
		scanf("%d",&a->objets[i].hauteur);
		strcpy(a->objets[i].nom,tmp_char);
		//a->objets[i].x=-1;
		//a->objets[i].y=-1;	
		i++;
	}
}

/*Ajout objet a liste, N°Liste/nom/largeur/hauteur/posX/posY*/
void ajouter_objet(Liste_objet* a, char *nom ,int l, int h, int x, int y){
	a->nb_objets++;
	a->objets=realloc(a->objets, sizeof(objet)*a->nb_objets);
	a->objets[a->nb_objets-1].largeur=l;
	a->objets[a->nb_objets-1].hauteur=h;
	strcpy(a->objets[a->nb_objets-1].nom,nom);
	//a->objets[a->nb_objets-1].x=x;
	//a->objets[a->nb_objets-1].y=y;
}

/*Ajout objet a liste, objet, N°Liste (Simplification de ajouter_objet)*/
void ajouter_objet_struct(Liste_objet* a, objet* obj){
	ajouter_objet(a, obj->nom, obj->largeur, obj->hauteur, 0,0);	
}

/*Supp objets*/
void supprimer_objet(Liste_objet* a, char *nom){
	int i;
	for(i=0;i<a->nb_objets;i++){
		if(strcmp(a->objets[i].nom,nom)){
			printf("TEST1\n");
			free(&a->objets[i]);
			printf("TEST2\n");
			a->objets[i]=a->objets[a->nb_objets-1];
			printf("TEST3\n");
			a->nb_objets--;
			printf("TEST4\n");
			a->objets=realloc(a->objets, sizeof(objet)*a->nb_objets);
		}
	}
}
void ajouter_bande_solution(Liste_objet *a, bande *b){
}

/*
Liste_Bande fusionner_liste_bande(Liste_Bande *A, Liste_Bande *B){
	Liste_Bande *tmp;
	tmp->nb_bandes=A->nb_bandes+B->nb_bandes;
	tmp->surface=A->surface+B->surface;
	tmp->bande=malloc(sizeof(bande)*(A->nb_bandes+B->nb_bandes));
	for(i=0;i<A->nb_bandes;i++){
		tmp->bande[i]=A->bande[i];
	}
	for(i=0;i<B->nb_bandes;i++){
		tmp->bande[i+A->nb_bandes]=B->bande[i];
	}
	return tmp;
}
*/
void ajout_bande(Liste_Bande *A, bande *b){
	A->bande=realloc(A->bande,sizeof(bande)*(A->nb_bandes+1));
	A->bande[A->nb_bandes]=*b;
	A->nb_bandes++;
	A->surface+=b->surface;
}

Liste_Bande *initialiser_liste_bande(){
	Liste_Bande *tmp=malloc(sizeof(Liste_Bande));
	tmp->surface=0;
	tmp->nb_bandes=0;
	tmp->bande=NULL;
	return tmp;
}

Liste initialiser_listeA(int nb_objets){
	Liste tmp;
	tmp.nb_objets=0;
	tmp.surface=0;
	tmp.objets=malloc(sizeof(int)*nb_objets);
	tmp.orientation=malloc(sizeof(int)*nb_objets);
	int i;
	for(i=0; i<nb_objets;i++){
		tmp.objets[i]=0;
		tmp.orientation[i]=0;
	}
	return tmp;
}
	
Liste dupliquer_listeA(Liste* A, int nb_objets_total){
	Liste tmp=initialiser_listeA(nb_objets_total);
	tmp.nb_objets=A->nb_objets;
	tmp.surface=A->surface;
	int i;
	for(i=0;i<nb_objets_total;i++){
		tmp.objets[i]=A->objets[i];
		tmp.orientation[i]=A->orientation[i];
	}
	return tmp;
}

