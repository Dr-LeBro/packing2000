/************************************************************************/
/*		GENERATEUR						*/
/*	Arguments: (int)rand 						*/
/*	Option: (int)Largeur_Max (int)Hauteur_Max (int)Nombre de pieces */
/*	Input: 					      			*/
/*	Output: L/H boite > Nb piece > Pieces Nom/L/H 			*/
/************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../../headers/Generator/generator.h"

void aff_specif(){
	printf("generator $rand [largeur_max hauteur_max nombre_de_pieces] \n");
	exit(1);
}

int main(int argc, char *argv[]){
	int i, randt, l_max=LMAX, h_max=HMAX, nb_piece, largeur_boite, hauteur_boite;
	char str[20];
	
	/*Test arguments*/
	if(argc <= 1){aff_specif();}
	randt=atoi(argv[1]),	
	srand(randt);

	if(argc > 2){
		if(argc != 5) aff_specif();	
		l_max=atoi(argv[2]);
		h_max=atoi(argv[3]);
		nb_piece=atoi(argv[4]);
	}
	else{
		nb_piece=rand()%NBMAX;
	}

	/*Ajustements pour evité 0*/	
	largeur_boite=rand()%l_max;
	hauteur_boite=rand()%h_max;

	/*Print boite Largeur-Hauteur*/
	printf("%d ",largeur_boite);
	printf("%d ",hauteur_boite);

	/*Print Nb objets*/
	printf("%d ",nb_piece);
	
	/*Print Pieces Nom-Largeur-Hauter*/
	for(i=0;i<nb_piece;i++){
		sprintf(str,"piece%d",i+1);
		printf("%s ",str);
		printf("%d ",(rand()%largeur_boite)+1);
		printf("%d ",(rand()%hauteur_boite)+1);	
	}
	printf("\n");
	return 0;
}
