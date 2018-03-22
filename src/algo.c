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

//SELECTION DE LARGEURS V2
int select_largeurs_new(Liste_objet *liste_objets, Liste *listeA, int largeurs[],int k){
	int moy=0, max=0, variance=0, min = 99999;
	int j=0, i=0, y=0;
	for(i=0;i<liste_objets->nb_objets;i++){
		if(listeA->objets[i] == 0 && liste_objets->objets[i].largeur <= k){
			moy+=liste_objets->objets[i].largeur;
			moy+=liste_objets->objets[i].hauteur;
			j+=2;
			if(liste_objets->objets[i].largeur>max){
				max = liste_objets->objets[i].largeur;
			}
			if(liste_objets->objets[i].hauteur>max){
				max = liste_objets->objets[i].hauteur;
			}
			if(liste_objets->objets[i].largeur<min){
				min = liste_objets->objets[i].largeur;
			}
			if(liste_objets->objets[i].hauteur<min){
				min = liste_objets->objets[i].hauteur;
			}
		}
	}
	if(j==0){
		return 0;
	}else{
		moy/=j;
		for(i=0;i<liste_objets->nb_objets;i++){
			if(listeA->objets[i] == 0 && liste_objets->objets[i].largeur <= k){
				variance+=((int) pow(liste_objets->objets[i].largeur- moy, 2));
				variance+=((int) pow(liste_objets->objets[i].hauteur- moy, 2));
			}
		}
		variance=(int)sqrt(variance/j)/2;
		if(variance < 1) variance = 1;
		for(i=min; i<max && y<liste_objets->nb_objets; i+=variance){
			largeurs[y] = i;
			y++;
		}
		//printf("min: %d, max: %d | moy: %d, variance: %d | y:%d\n", min, max, moy, variance, y);
		return y;
	}
}

//CALCUL SURFACE OBJET
int surface_objet(objet A){
	return A.largeur*A.hauteur;
}

//REMPLISAGE BANDE SAC A DOS
void remplir_bande_sac(int hauteur, int largeur_bande, Liste_objet *liste_objets, Liste *listeA, int profondeur){
	int W = hauteur, N = listeA->nb_objets;
	int M[N][W];
	int i, j;
	
	for(i=0; i < N; i++){
		for(j=0; j < W; j++){
			M[i][j]=-1;
		}
	}
	
	//INIT MATRICE
	for(i=0; i < W; i++) M[0][i]=0;
	
	for(i=1; i < N; i++){
		for(j=0; j < W; j++){
			if(j >= liste_objets->objets[i].hauteur){
				if(M[i-1][j] > M[i-1][j - liste_objets->objets[i].hauteur] + liste_objets->objets[i].hauteur*liste_objets->objets[i].largeur)	M[i][j] = M[i-1][j];
				else M[i][j] = M[i-1][j - liste_objets->objets[i].hauteur] + liste_objets->objets[i].hauteur*liste_objets->objets[i].largeur;
			}else{
				M[i][i] = M[i-1][j];
			}
		}
	}
	printf("Matrice %d x %d\n",N,W);
	for(i=0; i < N; i++){
		for(j=0; j < W; j++){
			printf("%d ", M[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
}

//REMPLISAGE BANDE
void remplir_bande(int hauteur, int largeur_bande, Liste_objet *liste_objets, Liste *listeA, int profondeur){

	int i;
	//printf("DEBUT REMPLISAGE BANDE\n");
	//PARCOURS DE TOUS LES OBJETS
	//printf("TEST REMPLIR BANDE | largeur : %d , hauteur : %d \n",largeur_bande,hauteur);
	for(i=0; i<liste_objets->nb_objets; i++){
		//printf("TEST REMPLIR BANDE | FOR i:%d , nb_objets_dispo : %d hauteur %d\n",i,nb_objets_dispo,hauteur);
		//TEST HORIZONTAL
		if(hauteur <= 0) break;
		if(listeA->objets[i]==0){
			if(liste_objets->objets[i].largeur <= largeur_bande){
				//TEST HAUTEUR RESTANTE
				if(hauteur - liste_objets->objets[i].hauteur >= 0){
					//printf("TEST REMPLIR BANDE | LARGEUR\n");
					listeA->objets[i]=profondeur;
					listeA->nb_objets++;
					listeA->orientation[i]=0;
					listeA->surface+=surface_objet(liste_objets->objets[i]);
					hauteur-=liste_objets->objets[i].hauteur;
				}
			}
			//TEST VERTICAL
			else if (liste_objets->objets[i].hauteur <= largeur_bande){
				//TEST HAUTEUR RESTANTE
				if(hauteur - liste_objets->objets[i].largeur >= 0){
					//printf("TEST REMPLIR BANDE | HAUTEUR\n");
					listeA->objets[i]=profondeur;
					listeA->nb_objets++;
					listeA->orientation[i]=1;
					listeA->surface+=surface_objet(liste_objets->objets[i]);
					hauteur-=liste_objets->objets[i].largeur;
				}
			}
		}
	}
}

//AFFICHAGE COUCHE
void hierarchie(int n){
	int i; // Utiliser nb largeur + i
	printf(ANSI_COLOR_GREEN "%d├", n);
	for(i=0; i<n; i++){
		printf("─");
	}
	printf(">" ANSI_COLOR_RESET);
}

//CALCUL SURFACE PERDUE
int calcul_surface_perdue(int k, int surface, boite *box){
	int largeur=box->largeur-k;
	return largeur*box->hauteur-surface;
	
}

//REMPLISAGE BOITE V1 | ascendante
Liste remplir_boite_A(boite *box, Liste_objet *liste_objets, Liste listeA, int k, int couche){
	//SECU NB OBJ
	if(listeA.nb_objets==liste_objets->nb_objets||k<=0){
		//hierarchie(couche);
		//printf(ANSI_COLOR_GREEN"RETURN FIN %d "ANSI_COLOR_RESET"\n", listeA.surface);
		return listeA;
	}
	int i;
	int largeurs[liste_objets->nb_objets];
	int nb_largeurs = select_largeurs_new(liste_objets, &listeA, largeurs, k);
	//printf(ANSI_COLOR_BLUE "\n[---------------------------------- LARGEURS %d : %d %d %d ----------------------------------]"ANSI_COLOR_RESET"\n",nb_largeurs,largeurs[0],largeurs[1],largeurs[2]);
	if(nb_largeurs == 0){
		//hierarchie(couche);
		//printf(ANSI_COLOR_GREEN"RETURN FIN | PLUS LARGEURS %d "ANSI_COLOR_RESET"\n", listeA.surface);
		return listeA;
	}
	Liste best;
	best=initialiser_listeA(liste_objets->nb_objets); 
	//printf("NB OBJETS : %d\n",nb_objets); 
	for(i=0;i<nb_largeurs;i++){
		Liste listeB=dupliquer_listeA(&listeA, liste_objets->nb_objets);
		//printf("\n[----------------- REMPLIR BANDE %d | RESTANT %d -----------------]\n",i, k);
		remplir_bande(box->hauteur, largeurs[i], liste_objets, &listeB, couche);
		
		int nv_k=k-largeurs[i];
		listeB.surface_perdue = calcul_surface_perdue(nv_k, listeB.surface, box); 
		//printf("NOUVEAU NB OBJ: %d | NV K :%d\n",nv_nb_objets,nv_k);
		if(listeB.surface_perdue<=best.surface_perdue){
			Liste listeP=remplir_boite_A(box, liste_objets, listeB, nv_k, couche+1);
			if(listeP.surface > best.surface){
				//printf(ANSI_COLOR_YELLOW "NOUVEAU BEST BANDE | surface %d P %d"ANSI_COLOR_RESET "\n",B->surface,P);
				supprimer_listeA(&best);
				best=dupliquer_listeA(&listeP, liste_objets->nb_objets);
			}
		}
		supprimer_listeA(&listeB);
	}
	//hierarchie(couche);
	//printf(ANSI_COLOR_GREEN"RETURN BEST %d"ANSI_COLOR_RESET"\n",best.surface);
	cc++;
	return best;
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
		remplir_bande(box->hauteur, largeurs[i], liste_objets, &listeP, couche);
		remplir_bande_sac(box->hauteur, largeurs[i], liste_objets, &listeP, couche);
		int nv_k=k-largeurs[i];
		listeP.surface_perdue = calcul_surface_perdue(nv_k, listeP.surface, box);
		
		if(listeP.surface_perdue <= surface_perdue_old){
			remplir_boite_D(box, liste_objets, listeP, nv_k, couche+1);
			surface_perdue_old = listeP.surface_perdue;
		}
		//supprimer_listeA(&listeB);
		retablir_liste(&listeP, liste_objets->nb_objets, surface_init, couche);
	}
	cc2++;
}
