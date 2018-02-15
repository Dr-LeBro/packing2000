#include<stdio.h>
#include<stdlib.h>

#include"../headers/algo.h"
#include"../headers/boite.h"
#include"../headers/objets.h"
//~ 
//~ int selecteur_largeurs(int largeurBoite, Liste *boiteObjets, int largeurBandes, int resultats[3]){
	//~ //int largeurRestante = largeurBoite-largeurBandes; 
	//~ int i, moyLargeur=0;
	//~ for(i=0; i<boiteObjets->nb_objets; i++){
		//~ moyLargeur+=boiteObjets->objets[i].largeur;
		//~ moyLargeur+=boiteObjets->objets[i].hauteur;
	//~ }
	//~ resultats[0] = boiteObjets->objets[(int)(i-i/1.4)].largeur;
	//~ resultats[1] = moyLargeur / boiteObjets->nb_objets;
	//~ resultats[2] = boiteObjets->objets[i-i/4].largeur;
	//~ return 3;
//~ }
//~ 
//~ bande *remplir_bande(int largeurBande, int hauteur, Liste *boiteObjets, bande *bandes){
	//~ int i;
	//~ bande *bande1;
	//~ for(i=0; i<boiteObjets->nb_objets; i++){
		//~ if(boiteObjets->objets[i].largeur <= boiteObjets->objets[i].hauteur && boiteObjets->objets[i].largeur <= largeurBande){
			//~ ajouter_objet_struct(bande1->boite_objets, &(boiteObjets->objets[i]));
			//~ supprimer_objet_struct(boiteObjets, &(boiteObjets->objets[i]));
		//~ }else if(boiteObjets->objets[i].largeur > boiteObjets->objets[i].hauteur && boiteObjets->objets[i].hauteur <= largeurBande){
			//~ ajouter_objet_struct(bande1->boite_objets, &(boiteObjets->objets[i]));
			//~ supprimer_objet_struct(boiteObjets, &(boiteObjets->objets[i]));
		//~ }
	//~ }
	//~ return bande1;
//~ }
//~ 
//~ int calcul_surface(bande1, ){
	//~ 
	//~ 
	//~ 
//~ }
//~ 
//~ bande *remplir_boite(boite *boiteARemplir, Liste boiteObjets, int largeurBandes, int bandeCourrante){
	//~ int resultats[3], i;
	//~ bande *meilleure = NULL, *bande1 = NULL;
	//~ int nbLargeurs = selecteur_largeurs(boiteARemplir->largeur, &boiteObjets, largeurBandes, resultats);
	//~ for(i=0; i<nbLargeurs; i++){
		//~ bande1 = remplir_bande(resultats[i], boiteARemplir->hauteur, &boiteObjets, bande1);
		//~ remplir_boite(boiteARemplir, boiteObjets, bande1->largeur+largeurBandes, i+1);
		//~ if(calcul_surface(bande1){
			//~ 
		//~ }
	//~ }
	//~ 
	//~ return meilleure;
//~ }

int select_largeurs(int largeur_boite, Liste *liste_objets,int nb_objets, int k, int largeurs[]){
	if(nb_objets > 3){
		largeurs[0]=liste_objets->objets[0].largeur;
		largeurs[1]=liste_objets->objets[1].largeur;
		largeurs[2]=liste_objets->objets[2].largeur;
		return 3;
	}
	else {
		largeurs[0]=-1;
		largeurs[1]=-1;
		largeurs[2]=-1;
		return 0;
	}
}

int calcul_surface_bande(bande *B, int nb_objets, Liste *liste_objets){
	int i, surface=0;
	for(i=0;i<nb_objets;i++){
		if(B->tab[i] == 1){
			surface=surface+liste_objets->objets[i].largeur*liste_objets->objets[i].hauteur;
		}
	}	
	return surface;
}

void inversion_liste(Liste *liste_objets,int i, int nb_objets){
	Liste *tmp=malloc(sizeof(Liste));
	tmp->objets=malloc(sizeof(objet));
	tmp->objets[0]=liste_objets->objets[i];
	liste_objets->objets[i]=liste_objets->objets[nb_objets];
	liste_objets->objets[nb_objets]=tmp->objets[0];
}

bande *remplir_bande(int largeur, int hauteur, Liste *liste_objets, int nb_objets){
	bande *B=malloc(sizeof(bande));
	int i, nb_obj_total=liste_objets->nb_objets;
	B->nb_objets=0;
	B->tab=malloc(sizeof(int)*(nb_obj_total+1));
	B->tab_rotation=malloc(sizeof(int)*(nb_obj_total+1));
	printf("TEST 1 %d \n",nb_obj_total);
	for(i=0; i<nb_objets; i++){
		printf("FOR %d\n",i);
		if(liste_objets->objets[i].largeur <= largeur){
			printf("TEST 2\n");
			B->objets=malloc(sizeof(objet)*(nb_objets+1));
			B->objets[nb_objets]=&liste_objets->objets[i];
			printf("TEST 3\n");
			B->nb_objets++;
			printf("TEST 4\n");
			B->tab[i]=1;
			printf("TEST 41\n");
			B->tab_rotation[i]=0;
			printf("TEST 5\n");
			inversion_liste(liste_objets ,i ,nb_objets);
			printf("TEST 6\n");
			nb_objets--;
		}else if (liste_objets->objets[i].hauteur <= largeur){	
			B->objets[nb_objets]=&liste_objets->objets[i];
			B->nb_objets++;
			B->tab[i]=1;
			B->tab_rotation[i]=1;
			inversion_liste(liste_objets ,i ,nb_objets);
			nb_objets--;
		}
	}
	B->surface=calcul_surface_bande(B, nb_objets, liste_objets);
	return B;
}
	
int remplir_boite(int largeur_boite, int hauteur_boite, Liste *liste_objets,int k,int nb_objets){
	int best=0, i, P=0;
	bande *B;
	int largeurs[3];
	printf("NBLARGEURS\n");
	int nb_largeurs = select_largeurs(largeur_boite, liste_objets,nb_objets,k, largeurs);
	printf("LARGEURS : %d %d %d\n",largeurs[0],largeurs[1],largeurs[2]);


	printf("ITERATION NBLARG %d\n",nb_largeurs);
	printf("NB OBJETS : %d\n",nb_objets);	
	sleep(1);
	for(i=0;i<nb_largeurs;i++){
		printf("REMPLIR BANDE %d\n",i);
		B=remplir_bande(largeurs[i],hauteur_boite, liste_objets, nb_objets);
		printf("APPEL RECURSIF\n");
		P=remplir_boite(largeur_boite-largeurs[i],hauteur_boite, liste_objets, k, nb_objets-B->nb_objets);
		if(B->surface+P > best){
			best=B->surface+P;
		}
	}
	printf("RETURN BEST %d\n",best);
	sleep(1);
	return best;
}


