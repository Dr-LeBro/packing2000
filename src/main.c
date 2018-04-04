#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"../headers/boite.h"
#include"../headers/objets.h"
#include"../headers/algo.h"
#include"../headers/Interface/interfaceG.h"

/*Affiche Boite et Liste_Objets*/
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

/*Affiche type Liste */
void afficher_listeS(Liste *listeS, Liste_objet *a){
	int i;
	printf("----------------AFFICHAGE LISTE S--------------------\n");
	printf("	nb_objets : %d\n",listeS->nb_objets);
	for(i=0; i<a->nb_objets;i++){
		printf(" %d , %d \n",listeS->objets[i], listeS->orientation[i]);
	}
}

/*Trouver max pour afficher_bandes*/
int trouver_max(Liste *S, Liste_objet *L){
	int i,max=0;
	for(i=0;i<L->nb_objets;i++){
		if(max<S->objets[i]) max=S->objets[i];
	}
	return max;
}

/*Afficher bandes */
void afficher_bandes(Liste *S, Liste_objet *L){
	int i,j, max=trouver_max(S,L);
	for(i=1;i<=max;i++){
		printf("------------BANDE %d----------\n",i);
		printf("___________________________________________\n");
		printf("Nom Objet | Largeur | Hauteur | Orientation\n"); 
        	for(j=0;j<L->nb_objets;j++){
			if(S->objets[j]==i){
				printf(" %8s | %7.d | %7.d | %d\n",L->objets[j].nom, L->objets[j].largeur, L->objets[j].hauteur, S->orientation[j]); 
			}
		}
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

	printf("DEBUT ALGO A\n");
	clock_t temps;
	temps = clock();
	Liste listeS = initialiser_listeA(0);
	//remplir_boite_A(&B,&L, listeA, B.largeur, 1);

	printf("----------------------------------------\n RESULTAT SURFACE : %d / %d\n",listeS.surface,B.largeur*B.hauteur);
	double temps_final=(double)(clock()-temps)/CLOCKS_PER_SEC;
	printf("%f en %d etapes\n", temps_final, cc);
	//afficher_bandes(&listeS,&L);
	//gui(&B,&listeS,&L,temps_final);

	printf("DEBUT ALGO D\n");
	clock_t temps2;
	temps2 = clock();
	remplir_boite_D(&B,&L, listeA, B.largeur, 1);
	printf("----------------------------------------\n RESULTAT SURFACE : %d / %d\n",best.surface,B.largeur*B.hauteur);
	double temps_final2=(double)(clock()-temps2)/CLOCKS_PER_SEC;
	printf("%f en %d etapes\n", temps_final2, cc2);
	afficher_bandes(&best,&L);
	afficher_tout(&L,&B);
	gui(&B,&listeS,&best,&L,temps_final,temps_final2);

	return 0;
}
