#include<stdio.h>
#include<stdlib.h>

#include"../headers/algo.h"
#include"../headers/boite.h"
#include"../headers/objets.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"


void afficher_bande(bande *B){
	int i;
	printf("[ AFFICHER BANDE | %d objets | surface %d]\n",B->nb_objets,B->surface);
	for(i=0;i<B->nb_objets;i++){
		printf(" %8s |",B->objets_bande[i].nom);
		printf(" %7.d |", B->objets_bande[i].largeur);
		printf(" %7.d \n",B->objets_bande[i].hauteur);
	}
}

void afficher_objet(objet *O){
	printf("[ AFFICHER OBJET ]\n");
	printf(" %8s |",O->nom);
	printf(" %7.d |", O->largeur);
	printf(" %7.d \n",O->hauteur);
}


void afficher_liste(Liste *a){ 
    int i; 
    printf("[ AFFICHER LISTE | %d objets ]\n",a->nb_objets); 
	printf("______________________________\n");
	printf("Nom Objet | Largeur | Hauteur \n"); 
        for(i=0;i<a->nb_objets;i++){ 
            printf(" %8s | %7.d | %7.d\n",a->objets[i].nom, a->objets[i].largeur, a->objets[i].hauteur); 
	}
}

//SELECTION DE LARGEURS V1 - BOURRIN - OK
int select_largeurs(Liste *liste_objets,int nb_objets, int largeurs[], int k){
	int i,j=0;
	for(i=0;i<nb_objets;i++){
		//TEST SI LARGEUR RENTRE DANS PLACE DISPO
		if(liste_objets->objets[i].largeur <= k){
			largeurs[j]=liste_objets->objets[i].largeur;
			j++;
		}
		//LIMITEUR LARGEURS
		if(j==2){return j;}
	}
	return j;
}

//ECHANGE LES POSITIONS ENTRE i ET nb_objets DANS liste_objets - OK
void invertir_liste(Liste *liste_objets,int i, int nb_objets){
	objet tmp;
	tmp=liste_objets->objets[i];
	liste_objets->objets[i]=liste_objets->objets[nb_objets-1];
	liste_objets->objets[nb_objets-1]=tmp;
}


//MANQUE AJOUT OBJET A BANDE + ORIENTATION<----------------------------------------------------------------------------------------------------------
//REMPLISAGE BANDE
bande *remplir_bande(int largeur, int hauteur, Liste *liste_objets, int nb_objets_dispo){
	bande *B=malloc(sizeof(bande));
	B->nb_objets=0;
	int i, surface=0;
	printf("DEBUT REMPLISAGE BANDE\n");
	//PARCOURS DE TOUS LES OBJETS DISPO | nb_objets_dispo
	printf("TEST REMPLIR BANDE | largeur : %d ,nb_objets_dispo : %d\n",largeur,nb_objets_dispo);
	for(i=0; i<nb_objets_dispo; i++){
		//printf("TEST REMPLIR BANDE | FOR i:%d , nb_objets_dispo : %d hauteur %d\n",i,nb_objets_dispo,hauteur);
		//TEST HORIZONTAL
		if(hauteur <= 0) break;
		if(liste_objets->objets[i].largeur <= largeur){
			//TEST HAUTEUR RESTANTE
			if(hauteur - liste_objets->objets[i].hauteur >= 0){
				//printf("TEST REMPLIR BANDE | LARGEUR\n");
				//CALCUL SURFACE
				surface=surface+liste_objets->objets[i].largeur*liste_objets->objets[i].hauteur;
				hauteur=hauteur-liste_objets->objets[i].hauteur;
				B->objets_bande=realloc(B->objets_bande,sizeof(objet)*(B->nb_objets+1));
				B->objets_bande[B->nb_objets]=liste_objets->objets[i];
				invertir_liste(liste_objets,i,nb_objets_dispo);
				//DECREMENT i ET nb_objets_dispo POUR REITERATION NV OBJ SAUF SI DERNIER OBJET
				if(i!=nb_objets_dispo-1){
					i--;
				}
				nb_objets_dispo--;
				B->nb_objets++;
			}

		}
		//TEST VERTICAL
		else if (liste_objets->objets[i].hauteur <= largeur){
			//TEST HAUTEUR RESTANTE
			if(hauteur - liste_objets->objets[i].largeur >= 0){
				//printf("TEST REMPLIR BANDE | HAUTEUR\n");
				//CALCUL SURFACE
				surface=surface+liste_objets->objets[i].largeur*liste_objets->objets[i].hauteur;
				hauteur=hauteur-liste_objets->objets[i].largeur;
				B->objets_bande=realloc(B->objets_bande,sizeof(objet)*(B->nb_objets+1));
				B->objets_bande[B->nb_objets]=liste_objets->objets[i];
				invertir_liste(liste_objets,i,nb_objets_dispo);
				//DECREMENT i ET nb_objets_dispo POUR REITERATION NV OBJ SAUF SI DERNIER OBJET
				if(i!=nb_objets_dispo-1){
					i--;
				}
				nb_objets_dispo--;
				B->nb_objets++;
			}
		}
	}
	B->surface=surface;
	afficher_bande(B);
	return B;
}


//REMPLISAGE BOITE V1 - NB LARGEURS FIXES | BOURRIN | CALCUL SEULEMENT LA SURFACE
int remplir_boite(int largeur_boite, int hauteur_boite, Liste *liste_objets,int k,int nb_objets){
	//SECU NB OBJ
	if(nb_objets<=0||k<=0){
		return 0;
	}

	int best=0, i, P=0;
	bande *B, *best_bande=NULL;
	int largeurs[3];
	int nb_largeurs = select_largeurs(liste_objets, nb_objets, largeurs, k);
	printf(ANSI_COLOR_BLUE "\n[---------------------------------- LARGEURS %d : %d %d %d ----------------------------------]"ANSI_COLOR_RESET"\n",nb_largeurs,largeurs[0],largeurs[1],largeurs[2]);
	
	//SECU NB LARGEURS
	if(nb_largeurs <= 0){
		return 0;
	}

	//printf("NB OBJETS : %d\n",nb_objets);	
	for(i=0;i<nb_largeurs;i++){
		printf("\n[----------------- REMPLIR BANDE %d -----------------]\n",i);
		B=remplir_bande(largeurs[i],hauteur_boite, liste_objets, nb_objets);
		//printf("BANDE %d %d\n",B->nb_objets, B->surface);
		int nv_nb_objets=nb_objets-B->nb_objets;
		int nv_k=k-largeurs[i];
		//printf("NOUVEAU NB OBJ: %d | NV K :%d\n",nv_nb_objets,nv_k);
		P=remplir_boite(largeur_boite-largeurs[i],hauteur_boite, liste_objets, nv_k, nv_nb_objets);
		if(B->surface+P > best){
			//printf(ANSI_COLOR_YELLOW "NOUVEAU BEST BANDE | surface %d P %d"ANSI_COLOR_RESET "\n",B->surface,P);
			best_bande=B;
			best=B->surface+P;
		}
	}
	if(nb_largeurs > 0){
		//printf(ANSI_COLOR_RED "AJOUT BANDE SOLUTION | %d" ANSI_COLOR_RESET "\n",B->surface);
		ajouter_bande_solution(liste_objets,best_bande);
	}
	printf(ANSI_COLOR_GREEN"RETURN BEST %d"ANSI_COLOR_RESET"\n",best);
	return best;
}