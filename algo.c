#include<stdio.h>
#include<stdlib.h>
#include"../headers/algo.h"


int selecteur_largeur(int largeurBoite, Liste *boiteObjets, int largeurBandes, int resultats[3]){
	int largeurRestante = largeurBoite-largeurBandes; 
	int i, moyLargeur=0;
	for(i=0; i<boiteObjets->nbObjets; i++){
		moyLargeur+=boiteObjets->objets[i];
	}
	for(i=0; i<boiteObjets->nbObjets_sol; i++){
		moyLargeur+=boiteObjets->objets_sol[i];
	}
	resultats[0] = moyLargeur - objets[i];
	resultats[1] = moyLargeur \=  boiteObjets->nbObjets-boiteObjets->nbObjets_sol;
	resultats[2] = moyLargeur + objets[i];
	return 3;
}

bande *remplir_bande(int largeurBande, int hauteur, Liste *boiteObjets, bande *bandes){
	int i;
	bande *bande1;
	for(i=0; i<boiteObjets->nb_objets; i++){
		if(boiteObjets->largeur =< boiteObjets->hauteur && boiteObjets->largeur =< largeurBande){
			ajouter_objet_struct(boiteObjets->objets[i], bande1->objets);
			supprimer_objet_struct(boiteObjets->objets[i]);
		}else if(boiteObjets->largeur > boiteObjets->hauteur && boiteObjets->hauteur =< largeurBande){
			ajouter_objet_struct(boiteObjets->objets[i], bande1->objets);
			supprimer_objet_struct(boiteObjets->objets[i]);
		}
	}
}


bande *remplir_boite(boite *boiteARemplir, Liste boiteObjets, int largeurBandes, int bandeCourrante){
	int resultats[3], i;
	bande meilleure = NULL, bande1 = NULL;
	nbLargeurs = selectLargeurs(boiteARemplir.largeur, &boiteObjets, largeurBandes, resultats);
	for(i=0; i<nbLargeurs; i++){
		bande1 = remplir_bande(largeurBande, boiteARemplir->hauteur, &boiteObjets);
		remplir_boite(boiteARemplir->largeur-resultats[i], boiteObjets, bande1->largeur+largeurBandes, i+1);
		if(){
			
		}
	}
	
	
}
