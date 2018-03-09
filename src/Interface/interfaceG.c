#include"../../headers/Interface/ez-draw.h"
#include"../../headers/boite.h"
#include"../../headers/objets.h"
#include"../../headers/Interface/interfaceG.h"

/*Trouver max pour afficher_bandes*/
int trouver_max_gui(Liste *S, Liste_objet *L){
	int i,max=0;
	for(i=0;i<L->nb_objets;i++){
		if(max<S->objets[i]) max=S->objets[i];
	}
	return max;
}

void win1_on_expose(Ez_event *ev){
    Win_data *data = ez_get_data(ev->win);

    int win_w, win_h;
    ez_window_get_size (ev->win, &win_w, &win_h);

    //OBJETS
    ez_set_thick (1);
    int i, j, max=trouver_max_gui(data->liste,data->liste_objets), largeur_utils=0;
	for(i=1; i<=max; i++){
        int hauteur_utils=data->box->hauteur*data->scale+50, Lmax=0;
        for(j=0; j < data->liste_objets->nb_objets; j++){
            //SI OBJ UTILISER DANS BANDE i
            if(data->liste->objets[j] == i){
                //ALIAS DIMENSIONS
                int h_obj=data->liste_objets->objets[j].hauteur;
                int l_obj=data->liste_objets->objets[j].largeur;
                int x_start=50+largeur_utils*data->scale;
                int y_start=hauteur_utils;

                //TEST ORIENTATION OBJ
                if(data->liste->orientation[j] == 0){
                    //DESSIN RECTANGLE
                    ez_set_color (ez_blue);
                    ez_fill_rectangle(ev->win,x_start, y_start, x_start+l_obj*data->scale, y_start-h_obj*data->scale);
                    ez_set_color (ez_black);
                    ez_draw_rectangle(ev->win,x_start, y_start, x_start+l_obj*data->scale, y_start-h_obj*data->scale);

                    //MAJ DIMENSIONS
                    hauteur_utils-=data->liste_objets->objets[j].hauteur*data->scale;
                    //RECHECHE OBJ LARGEUR BANDE
                    if(Lmax < data->liste_objets->objets[j].largeur) Lmax = data->liste_objets->objets[j].largeur;
                }else{
                    ez_set_color (ez_red);
                    ez_fill_rectangle(ev->win,x_start, y_start, x_start+h_obj*data->scale, y_start-l_obj*data->scale);
                    ez_set_color (ez_black);
                    ez_draw_rectangle(ev->win,x_start, y_start, x_start+h_obj*data->scale, y_start-l_obj*data->scale);

                    hauteur_utils-=data->liste_objets->objets[j].largeur*data->scale;
                    //RECHECHE OBJ LARGEUR BANDE
                    if(Lmax < data->liste_objets->objets[j].largeur) Lmax = data->liste_objets->objets[j].hauteur;
                }
            }
        }
        //MAJ LARGEUR DISPO
        largeur_utils+=Lmax;
	}

    //BOITE
    ez_set_color(ez_black);
    ez_set_thick(2);
    ez_draw_rectangle(ev->win, 50, 50, 50+data->box->largeur*data->scale, 50+data->box->hauteur*data->scale);

    //TEXTE
    ez_set_nfont(2);
    ez_draw_text(ev->win, EZ_TC, win_w/2,25,"Calcul en %fs | %d/%d objets | Remplisage : %d/%d", data->temps, data->liste->nb_objets, data->liste_objets->nb_objets, data->liste->surface, data->box->hauteur*data->box->largeur);
    ez_set_nfont(1);
    ez_draw_text(ev->win, EZ_TC, win_w/2, 50+data->box->hauteur*data->scale+10, "Scale %d\n a : augmenter taille / z : reduire taille",data->scale);
}

void win1_on_key_press(Ez_event *ev){
    Win_data *data = ez_get_data(ev->win);

    switch(ev->key_sym){
        case XK_q: ez_quit(); break;
        case XK_a: data->scale++; ez_window_clear(ev->win); win1_on_expose(ev); break;
        case XK_z: if(data->scale > 1){data->scale--; ez_window_clear(ev->win); win1_on_expose(ev); break;}
    }
}

void win1_on_event(Ez_event *ev){
    switch(ev->type){
        case Expose: win1_on_expose(ev); break;
        case KeyPress: win1_on_key_press(ev); break;
    }
}

/*Interface Affichage solution*/
void gui(boite *box, Liste *S, Liste_objet *L, double temps){
    Ez_window win1;
    if (ez_init() < 0) exit(1);

    Win_data data;
    data.box = box;
    data.liste = S;
    data.liste_objets = L;
    data.scale=10;
    data.temps=temps;

    win1 = ez_window_create (box->largeur*10+100, box->hauteur*10+100, "Packing 2000", win1_on_event);
    
    ez_window_dbuf(win1,1);
    ez_set_data(win1, &data);
    
    ez_main_loop ();
}