#include<stdio.h>
#include<stdlib.h>
#include"boite.h"

/*Initialise la taille de la boite*/
void initialiser_boite(boite *box){
	box->largeur=-1;
	box->hauteur=-1;
}

/*Receptionne les sur l'entré standar la taille de la boite */
void reception_boite(boite *box){
	scanf("%d",&box->largeur);
	scanf("%d",&box->hauteur);
}