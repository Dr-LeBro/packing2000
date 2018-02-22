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

//SELECTION DE LARGEURS V1 - BOURRIN - OK
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
		if(j==2){return j;}
	}
	return j;
}

int surface_objet(objet A){
	return A.largeur*A.hauteur;
}

//REMPLISAGE BANDE
void remplir_bande(int hauteur, int largeur_bande, Liste_objet *liste_objets, Liste *listeA){
	int i;
	//printf("DEBUT REMPLISAGE BANDE\n");
	//PARCOURS DE TOUS LES OBJETS DISPO | nb_objets_dispo
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
					listeA->objets[i]=1;
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
					listeA->objets[i]=1;
					listeA->nb_objets++;
					listeA->orientation[i]=1;
					listeA->surface+=surface_objet(liste_objets->objets[i]);
					hauteur-=liste_objets->objets[i].hauteur;
				}
			}
		}
	}
}

void hierarchie(int n){
	int i; // Utiliser nb largeur + i
	printf(ANSI_COLOR_GREEN "%d├", n);
	for(i=0; i<n; i++){
		printf("─");
	}
	printf(">" ANSI_COLOR_RESET);
}


//REMPLISAGE BOITE V1 - NB LARGEURS FIXES | BOURRIN | CALCUL SEULEMENT LA SURFACE
Liste remplir_boite(boite *box, Liste_objet *liste_objets, Liste listeA, int k, int couche){
        //SECU NB OBJ
        if(listeA.nb_objets==liste_objets->nb_objets||k<=0){
			hierarchie(couche);
			printf(ANSI_COLOR_GREEN"RETURN FIN %d "ANSI_COLOR_RESET"\n", listeA.surface);
			return listeA;
        }
        int i;
        int largeurs[3];
        int nb_largeurs = select_largeurs(liste_objets, &listeA, largeurs, k);
        //printf(ANSI_COLOR_BLUE "\n[---------------------------------- LARGEURS %d : %d %d %d ----------------------------------]"ANSI_COLOR_RESET"\n",nb_largeurs,largeurs[0],largeurs[1],largeurs[2]);
       
	if(nb_largeurs == 0){
		hierarchie(couche);
		printf(ANSI_COLOR_GREEN"RETURN FIN | PLUS LARGEURS %d "ANSI_COLOR_RESET"\n", listeA.surface);
		return listeA;
	}
	Liste best;
	best=initialiser_listeA(liste_objets->nb_objets); 
	//printf("NB OBJETS : %d\n",nb_objets); 
        for(i=0;i<nb_largeurs;i++){
		Liste listeB=dupliquer_listeA(&listeA, liste_objets->nb_objets);
                //printf("\n[----------------- REMPLIR BANDE %d | RESTANT %d -----------------]\n",i, k);
                remplir_bande(box->hauteur, largeurs[i], liste_objets, &listeB);
                int nv_k=k-largeurs[i];
                //printf("NOUVEAU NB OBJ: %d | NV K :%d\n",nv_nb_objets,nv_k);
                Liste listeP=remplir_boite(box, liste_objets, listeB, nv_k, couche+1);
                if(listeP.surface > best.surface){
                        //printf(ANSI_COLOR_YELLOW "NOUVEAU BEST BANDE | surface %d P %d"ANSI_COLOR_RESET "\n",B->surface,P);
                        best=dupliquer_listeA(&listeP, liste_objets->nb_objets);
                }
        }
        hierarchie(couche);
        printf(ANSI_COLOR_GREEN"RETURN BEST %d"ANSI_COLOR_RESET"\n",best.surface);
        return best;
}
