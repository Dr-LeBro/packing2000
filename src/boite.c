/********************************/
/* FONCTIONS OPERATIONS BOITES	*/
/********************************/

#include<stdio.h>
#include<stdlib.h>
#include"../headers/boite.h"

/*Initialise la taille de la boite*/
void initialiser_boite(boite *box){
	box->largeur=-1;
	box->hauteur=-1;
}

/*Receptionne les sur l'entré standar la taille de la boite */
void reception_boite(boite *box){
	int tmpl, tmph;
	scanf("%d",&tmpl);
	scanf("%d",&tmph);
	printf("RECEP BOITE | l:%d h:%d\n",tmpl,tmph);
	box->largeur=tmpl;
	box->hauteur=tmph;
}