#include<stdio.h>
#include<stdlib.h>
#include"../headers/boite.h"
#include"../headers/objets.h"
#include"../headers/algo.h"

void afficher_tout(Liste_objet *a,boite *box){ 
        int i; 
        printf("---------AFFICHER TOUT---------\n"); 
        printf(" Dimensions boite: %d x %d\n",box->largeur, box->hauteur); 
        printf("\n---------Liste objets-----------\n"); 
        printf(" Nombres objets: %d\n",a->nb_objets);
	printf("_____________________________________________\n");
	printf("Nom Objet | Largeur | Hauteur | Pos X | Pos Y\n"); 
        for(i=0;i<a->nb_objets;i++){ 
                printf(" %8s | %7.d | %7.d | %5.d | %5.d\n",a->objets[i].nom, a->objets[i].largeur, a->objets[i].hauteur, 0,0); 
	}
}

void afficher_liste_bande(Liste_Bande *a){
	int i,j;
	
	printf("----------AFFICHAGE OBJETS BANDE SOLUTION----------\n");
	printf("Surface %d \n",a->surface);
	printf("_____________________________\n");
	printf("Nom Objet | Largeur | Hauteur\n"); 
	for(i=0;i<a->nb_bandes;i++){
		printf("	Bande %d | %d objets | surface %d\n",i,a->bande[i].nb_objets,a->bande[i].surface);
		for(j=0; j<a->bande[i].nb_objets;j++){
			printf(" %8s |",a->bande[i].objets_bande[j].nom);
			printf(" %7.d |", a->bande[i].objets_bande[j].largeur);
			printf(" %7.d \n",a->bande[i].objets_bande[j].hauteur);
		}
	}
}

void afficher_listeS(Liste *listeS, Liste_objet *a){
	int i;
	printf("----------------AFFICHAGE LISTE S--------------------\n");
	printf("	nb_objets : %d\n",listeS->nb_objets);
	for(i=0; i<a->nb_objets;i++){
		printf(" %d , %d \n",listeS->objets[i], listeS->orientation[i]);
	}
}

int main(){
	boite B;
	initialiser_boite(&B);
	Liste_objet L;
	L=initialiser_liste();
	reception_boite(&B);
	reception_objets(&L);
	fflush(stdout);
	Liste listeA=initialiser_listeA(L.nb_objets);
	printf("DEBUT \n");
	Liste listeS = remplir_boite(&B,&L, listeA, B.largeur, 1);
	printf("----------------------------------------\n RESULTAT SURFACE : %d \n",listeS.surface);
	afficher_listeS(&listeS, &L);
	afficher_tout(&L,&B);
	return 0;
}
