#ifndef graphe_h
#define graphe_h


#include <stdio.h>
#include <stdlib.h>


typedef struct {
   int nbsom;
   int nbarc;
   float **matrice; /* matrice d'adjacence */
   float *distance;
   int *pris;
   int *pred; /* pour obtenir l’itinéraire suivi */
   } graphe;


typedef struct {
   int num_som; /* numero du sommet dans le graphe */
   float potentiel;
   } elem_tas;


typedef struct {
   int nbelem; /* taille du tas */
   elem_tas *tab_tas; /* le tableau représentant le tas */
   int *place_dans_le_tas;
   } tas;
int norme(int,int);
void getMinAcceleration(int,int*,int*);
int calcule_chemin(graphe*,int,int*,int);
int suivre_chemin(int**,int,int);
void getAccelerations(int**,int,int,int,int,int*,int*,int,int*);
void getAcceleration(int*,int*,int,int,int,int,int**,int,int,int,int);
int check_tab(int*,int,int);
int plus_court_chemin(graphe,tas,int,int*,int);
int plus_2(int);
elem_tas extraire_min_tas(tas*);
void maj_tas(int,tas*);
void init_tas(int,tas*);
void init_graphe(int,int,graphe*);
void place_tas(tas*);
void remonter(tas*,int);
void echanger(tas*,int,int);
void redescendre(tas*,int);
#endif
