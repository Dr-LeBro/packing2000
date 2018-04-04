#ifndef _H_ALGO_
#define _H_ALGO_

#include"boite.h"
#include"objets.h"

extern int cc;
extern int cc2;
extern Liste best;

Liste remplir_boite_A(boite *box, Liste_objet *liste_objets, Liste listeA, int k, int couche);
void remplir_boite_D(boite *box, Liste_objet *liste_objets, Liste listeA, int k, int couche);
#endif
