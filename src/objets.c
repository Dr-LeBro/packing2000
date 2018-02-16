/****************************************/
/* FONCTIONS OPERATIONS OBJETS/LISTES	*/
/****************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../headers/objets.h"
#include"../headers/boite.h"

/*Initialisation de liste d'objets, renvoi pointeur nouvelle liste*/
Liste initialiser_liste(){
	Liste *ptr;
	ptr=malloc(sizeof(Liste));
	ptr->nb_objets=0;
	ptr->objets=NULL;
	return *ptr;
}

/*Receptions objets pour liste depuis generateur*/
void reception_objets(Liste* a){
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
void ajouter_objet(Liste* a, char *nom ,int l, int h, int x, int y){
	a->nb_objets++;
	a->objets=realloc(a->objets, sizeof(objet)*a->nb_objets);
	a->objets[a->nb_objets-1].largeur=l;
	a->objets[a->nb_objets-1].hauteur=h;
	strcpy(a->objets[a->nb_objets-1].nom,nom);
	//a->objets[a->nb_objets-1].x=x;
	//a->objets[a->nb_objets-1].y=y;
}

/*Ajout objet a liste, objet, N°Liste (Simplification de ajouter_objet)*/
void ajouter_objet_struct(Liste* a, objet* obj){
	ajouter_objet(a, obj->nom, obj->largeur, obj->hauteur, 0,0);	
}

/*Supp objets*/
void supprimer_objet(Liste* a, char *nom){
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