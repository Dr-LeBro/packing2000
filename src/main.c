#include<stdio.h>
#include<stdlib.h>
#include"../headers/boite.h"
#include"../headers/objets.h"

void afficher_tout(Liste *a,boite *box){ 
        int i; 
        printf("---------AFFICHER TOUT---------\n"); 
        printf(" Dimensions boite: %d x %d\n",box->largeur, box->hauteur); 
        printf("\n---------Liste objets-----------\n"); 
        printf(" Nombres objets: %d\n",a->nb_objets);
	printf("_____________________________________________\n");
	printf("Nom Objet | Largeur | Hauteur | Pos X | Pos Y\n"); 
        for(i=0;i<a->nb_objets;i++){ 
                printf(" %8s | %7.d | %7.d | %5.d | %5.d\n",a->objets[i].nom, a->objets[i].largeur, a->objets[i].hauteur, a->objets[i].x, a->objets[i].y); 
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
	printf("---------------------------------\n");
	ajouter_objet(&L, "TESTO", 1,2,3,4);
	afficher_tout(&L,&B);
	supprimer_objet(&L, "TESTO");
	afficher_tout(&L,&B);
	
	return 0;
}
