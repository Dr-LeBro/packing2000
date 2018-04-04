#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include"../headers/algo.h"
#include"../headers/boite.h"
#include"../headers/objets.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int cc=0;
int cc2=0;
Liste best;

//SELECTION DE LARGEURS V1 - BOURRIN
int select_largeurs(Liste_objet *liste_objets, Liste *listeA, int largeurs[],int k){
	int i,j=0;
	for(i=0;i<liste_objets->nb_objets;i++){
		//TEST SI LARGEUR RENTRE DANS PLACE DISPO
		if(listeA->objets[i] == 0){
			if(liste_objets->objets[i].largeur <= k){
				largeurs[j]=liste_objets->objets[i].largeur;
				j++;
			}
		}
		//LIMITEUR LARGEURS
		if(j==100){return j;}
	}
	return j;
}

//CALCUL SURFACE OBJET
int surface_objet(objet A){
	return A.largeur*A.hauteur;
}

//REMPLISAGE BANDE PAR SAC A DOS | MANQUE ORIENTATION
void remplir_bande_sac(int hauteur, int largeur_bande, Liste_objet *liste_objets, Liste *listeA, int profondeur){
	int Pmax = hauteur, //Hauteur maximale
		N = liste_objets->nb_objets - listeA->nb_objets; //Nombre d'objets
	int A[N+1][Pmax+1]; //Matrice sac a dos
	int Conv[N]; //Table conversion des indices
	int i=0, j=0, p=0;

	//CALCUL + AFFICHAGE DES INDICES
	for(i=0; i < liste_objets->nb_objets; i++){
		if(listeA->objets[i] == 0){
			Conv[j]=i;
			j++;
		}
	}
	j--;
	//INITIALISATION MATRICE
	for(i=0; i <= N; i++){
		for(p=0; p <= Pmax; p++){
			A[i][p]=0;
		}
	}
	//REMPLISAGE MATRICE 
	for(i=1; i<=N; i++){
		for(p=1; p<=Pmax; p++){
			//TEST HAUTEUR
			if(liste_objets->objets[Conv[i-1]].hauteur > p || liste_objets->objets[Conv[i-1]].largeur > largeur_bande){
				//TEST LARGEUR
				if(liste_objets->objets[Conv[i-1]].largeur <= p && liste_objets->objets[Conv[i-1]].hauteur <= largeur_bande){
					if(A[i-1][p] < A[i-1][p-liste_objets->objets[Conv[i-1]].largeur] + (liste_objets->objets[Conv[i-1]].largeur * liste_objets->objets[Conv[i-1]].hauteur))
					 A[i][p] = A[i-1][p-liste_objets->objets[Conv[i-1]].largeur] + (liste_objets->objets[Conv[i-1]].largeur * liste_objets->objets[Conv[i-1]].hauteur);
					else A[i][p] = A[i-1][p];
				}else{
					A[i][p] = A[i-1][p];
				}
			}
			else{
				if(A[i-1][p] < A[i-1][p-liste_objets->objets[Conv[i-1]].hauteur] + (liste_objets->objets[Conv[i-1]].largeur * liste_objets->objets[Conv[i-1]].hauteur))
					 A[i][p] = A[i-1][p-liste_objets->objets[Conv[i-1]].hauteur] + (liste_objets->objets[Conv[i-1]].largeur * liste_objets->objets[Conv[i-1]].hauteur);
				else A[i][p] = A[i-1][p];
			}
		}
	}

	//RESOLUTION
	i=N;
	p=Pmax;
	while(p >= 0 && i >0){
		if(A[i][p] != A[i-1][p]){
			//AJOUT OBJ
			listeA->objets[Conv[i-1]]=profondeur;
			listeA->nb_objets++;
			//TEST SENS DE LA PIECE
			if(liste_objets->objets[Conv[i-1]].largeur > largeur_bande || liste_objets->objets[Conv[i-1]].hauteur > p){
				listeA->orientation[Conv[i-1]]=1;
				p-=liste_objets->objets[Conv[i-1]].largeur;
			}else{
				listeA->orientation[Conv[i-1]]=0;
				p-=liste_objets->objets[Conv[i-1]].hauteur;
			}
			listeA->surface+=surface_objet(liste_objets->objets[Conv[i-1]]);
		}
		i--;
	}
}

//CALCUL SURFACE PERDUE
int calcul_surface_perdue(int k, int surface, boite *box){
	int largeur=box->largeur-k;
	return largeur*box->hauteur-surface;
	
}

void remplir_boite_D(boite *box, Liste_objet *liste_objets, Liste listeP, int k, int couche){
	//INIT bestD
	if(best.nb_objets == 0){
		printf("INIT bestD\n");
		best=initialiser_listeA(liste_objets->nb_objets); 
	}
	
	//COMPARE listeP ET bestD
	if(listeP.surface > best.surface){
		printf("NEW best | listeP:%d best:%d\n",listeP.surface, best.surface);
		best=dupliquer_listeA(&listeP, liste_objets->nb_objets);
	}
	
	//SELECTION LARGEURS
	int i, largeurs[liste_objets->nb_objets];
	int nb_largeurs = select_largeurs(liste_objets, &listeP, largeurs, k);
	int surface_perdue_old = box->hauteur*box->largeur;
	int surface_init = listeP.surface;
	//PARCOURS LARGEUR
	for(i=0;i<nb_largeurs;i++){
		remplir_bande_sac(box->hauteur, largeurs[i], liste_objets, &listeP, couche);
		int nv_k=k-largeurs[i];
		listeP.surface_perdue = calcul_surface_perdue(nv_k, listeP.surface, box);
		
		if(listeP.surface_perdue <= surface_perdue_old){
			remplir_boite_D(box, liste_objets, listeP, nv_k, couche+1);
			surface_perdue_old = listeP.surface_perdue;
		}
		retablir_liste(&listeP, liste_objets->nb_objets, surface_init, couche);
	}
	cc2++;
}
