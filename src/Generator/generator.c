#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"generator.h"

void aff_specif(){
	printf("generator $rand [largeur_max hauteur_max nombre_de_pieces] \n");
	exit(1);
}

int main(int argc, char *argv[]){
	int i, randt, l_max=LMAX, h_max=HMAX, nb_piece;
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
	
	/*Print boite Largeur-Hauteur*/
	printf("%d ",rand()%l_max);
	printf("%d ",rand()%h_max);

	/*Print Nb objets*/
	printf("%d ",nb_piece);
	
	/*Print Pieces Nom-Largeur-Hauter*/
	for(i=0;i<nb_piece;i++){
		sprintf(str,"piece%d",i+1);
		printf("%s ",str);
		printf("%d ",rand()%l_max);
		printf("%d ",rand()%h_max);	
	}
	printf("\n");
	return 0;
}
