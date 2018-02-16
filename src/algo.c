#include<stdio.h>
#include<stdlib.h>

#include"../headers/algo.h"
#include"../headers/boite.h"
#include"../headers/objets.h"

//SELECTION DE LARGEURS V1 - BOURRIN
int select_largeurs(Liste *liste_objets,int nb_objets, int largeurs[]){
	switch(nb_objets){
		case 0 : 	largeurs[0]=-1;
					largeurs[1]=-1;
					largeurs[2]=-1;
					return 0;
		case 1 : 	largeurs[0]=liste_objets->objets[0].largeur;
					largeurs[1]=-1;
					largeurs[2]=-1;
					return 1;
		case 2 : 	largeurs[0]=liste_objets->objets[0].largeur;
					largeurs[1]=liste_objets->objets[1].largeur;
					largeurs[2]=-1;
					return 2;
		default : 	largeurs[0]=liste_objets->objets[0].largeur;
					largeurs[1]=liste_objets->objets[1].largeur;
					largeurs[2]=liste_objets->objets[2].largeur;
					return 3;
	}
}

//ECHANGE LES POSITIONS ENTRE i ET nb_objets DANS liste_objets
void invertir_liste(Liste *liste_objets,int i, int nb_objets){
	Liste *tmp=malloc(sizeof(Liste));
	tmp->objets=malloc(sizeof(objet));
	tmp->objets[0]=liste_objets->objets[i];
	liste_objets->objets[i]=liste_objets->objets[nb_objets];
	liste_objets->objets[nb_objets]=tmp->objets[0];
}

bande *remplir_bande(int largeur, int hauteur, Liste *liste_objets, int nb_objets_dispo){
	bande *B=malloc(sizeof(bande));
	B->nb_objets=0;
	int i, surface=0;
	printf("DEBUT REMPLISAGE BANDE\n");
	//PARCOURS DE TOUS LES OBJETS DISPO | nb_objets_dispo = ADDRESS DERNIER OBJ DISPO
	for(i=0; i<=nb_objets_dispo; i++){
		printf("TEST REMPLIR BANDE | FOR i:%d , nb_objets_dispo : %d\n",i,nb_objets_dispo);
		//TEST HORIZONTAL
		if(liste_objets->objets[i].largeur <= largeur){
			printf("TEST REMPLIR BANDE | LARGEUR\n");
			//CALCUL SURFACE
			surface=surface+liste_objets->objets[i].largeur*liste_objets->objets[i].hauteur;
			invertir_liste(liste_objets,i,nb_objets_dispo);
			//DECREMENT i ET nb_objets_dispo POUR REITERATION NV OBJ
			i--;
			nb_objets_dispo--;
			B->nb_objets++;

		}
		//TEST VERTICAL
		else if (liste_objets->objets[i].hauteur <= largeur){
			printf("TEST REMPLIR BANDE | HAUTEUR\n");
			//CALCUL SURFACE
			surface=surface+liste_objets->objets[i].largeur*liste_objets->objets[i].hauteur;
			invertir_liste(liste_objets,i,nb_objets_dispo);
			//DECREMENT i ET nb_objets_dispo POUR REITERATION NV OBJ
			i--;
			nb_objets_dispo--;
			B->nb_objets++;
		}
	}
	B->surface=surface;
	return B;
}


//REMPLISAGE BOITE V1 - NB LARGEURS FIXES | BOURRIN | CALCUL SEULEMENT LA SURFACE
int remplir_boite(int largeur_boite, int hauteur_boite, Liste *liste_objets,int k,int nb_objets){
	//SECU NB OBJ
	if(nb_objets<=0){
		return 0;
	}

	int best=0, i, P=0;
	bande *B;
	int largeurs[3];
	printf("NBLARGEURS\n");
	int nb_largeurs = select_largeurs(liste_objets, nb_objets, largeurs);
	printf("LARGEURS : %d %d %d\n",largeurs[0],largeurs[1],largeurs[2]);

	printf("ITERATION NBLARG %d\n",nb_largeurs);
	printf("NB OBJETS : %d\n",nb_objets);	
	for(i=0;i<nb_largeurs;i++){
		printf("REMPLIR BANDE %d\n",i);
		B=remplir_bande(largeurs[i],hauteur_boite, liste_objets, nb_objets);
		printf("BANDE %d %d\n",B->nb_objets, B->surface);
		printf("APPEL RECURSIF\n");
		P=remplir_boite(largeur_boite-largeurs[i],hauteur_boite, liste_objets, k, nb_objets-B->nb_objets);
		if(B->surface+P > best){
			best=B->surface+P;
		}
	}
	printf("RETURN BEST %d\n",best);
	return best;
}


