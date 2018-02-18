#include<stdio.h>
#include<stdlib.h>
#include"../headers/boite.h"
#include"../headers/objets.h"
#include"../headers/algo.h"

void afficher_tout(Liste *a,boite *box){ 
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

void afficher_objets_bande(Liste *a){
	int i,j,surface=0;
	for(i=0;i<a->nb_bande_solution;i++){
		surface=surface+a->bande_solution[i].surface;

	}

	printf("----------AFFICHAGE OBJETS BANDE SOLUTION----------\n");
	printf("Surface %d \n",surface);
	printf("_____________________________\n");
	printf("Nom Objet | Largeur | Hauteur\n"); 
	for(i=0;i<a->nb_bande_solution;i++){
		printf("	Bande %d | %d objets\n",i,a->bande_solution[i].nb_objets);
		for(j=0; j<a->bande_solution[i].nb_objets;j++){
			printf(" %8s |",a->bande_solution[i].objets_bande[j].nom);
			printf(" %7.d |", a->bande_solution[i].objets_bande[j].largeur);
			printf(" %7.d \n",a->bande_solution[i].objets_bande[j].hauteur);
		}
	}
}

int main(){
	boite B;
	initialiser_boite(&B);
	Liste L;
	L=initialiser_liste();
	reception_boite(&B);
	reception_objets(&L);
	fflush(stdout);
	afficher_tout(&L,&B);
	printf("DEBUT \n");
	int solution = remplir_boite(B.largeur, B.hauteur, &L,B.largeur,L.nb_objets);
	printf("----------------------------------------\n RESULTAT SURFACE : %d\n",solution);
	printf("NOMBRES DE BANDE : %d | \n",L.nb_bande_solution);
	afficher_objets_bande(&L);
	afficher_tout(&L,&B);
	return 0;
}
