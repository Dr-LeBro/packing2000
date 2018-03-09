#ifndef _H_INTERFACEG_
#define _H_INTERFACEG_

typedef struct{
    boite *box;
    Liste *liste;
    Liste_objet *liste_objets;
    int scale;
    double temps;
}Win_data;

void gui(boite *box, Liste *S, Liste_objet *L, double temps);

#endif
