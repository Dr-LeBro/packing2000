#ifndef _H_INTERFACEG_
#define _H_INTERFACEG_

typedef struct{
    boite *box;
    Liste *liste;
    Liste_objet *liste_objets;
    int scale;
    double temps;
}Win_data;

void gui(boite *box, Liste *A, Liste *D, Liste_objet *L, double temps, double temps2);

#endif
