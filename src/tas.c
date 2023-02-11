
#include <stdio.h>
#include <stdlib.h> 
#include "graphe.h"
 
 
#define INFINI  9000  

/*les fonction de manipulation du graphe */
void init_graphe(int nbs,int nba,graphe *g){
   
   g->nbsom = nbs;
   g->nbarc = nba;

   g->pris = calloc(nbs,sizeof(int));
   g->pred = calloc(nbs,sizeof(int));
   g->distance = calloc(nbs,sizeof(int));
}



void charge_graphe(FILE *fic, graphe* g){
   int d, gg,i,dis;
  
   for(i = 0;i<g->nbsom;i++){
      fscanf(fic,"%d %d %d",&d,&gg,&dis);
      g->matrice[d][gg] = dis;
      g->matrice[gg][d] = dis;
   }
}

void affichage(graphe * g){
   int i,j;
   for (i = 0;i<g->nbsom;i++){
      for(j=0;j<g->nbsom;j++){
         printf("%f ",g->matrice[i][j]);
      }
      printf("\n");
   }
}

int  calcule_chemin(graphe* g,int depart,int* fin, int size_fin){
  int arrivee;
  tas * t = calloc(1,sizeof(tas));
  init_tas(g->nbsom,t);
  arrivee = plus_court_chemin(*g,*t,depart,fin,size_fin);
  return arrivee;
}



void init_tas(int nb,tas* t){
   t->nbelem = nb;
   t->tab_tas = calloc(nb,sizeof(elem_tas));
   t->place_dans_le_tas = calloc(nb,sizeof(int));
}


elem_tas extraire_min_tas(tas* t){
 /*  int i = t->tab_tas[t->nbelem-1].num_som;*/
   elem_tas sommet;
   sommet = t->tab_tas[1];
   echanger(t,1,t->nbelem - 1);
   t->nbelem --;
   redescendre(t,1);
  /* t->place_dans_le_tas[i] = j;*/
   return sommet;
}



void maj_tas(int m,tas* t){
   remonter(t,m);
   /*t->place_dans_le_tas[m] = i;*/
}

   
int plus_2(int n){
   return n+2;}

void place_tas(tas* t){
   int i;
   for(i = 1;i<t->nbelem;i++){
      t->place_dans_le_tas[t->tab_tas[i].num_som] = i;
   }
}


int check_tab(int* tab,int size,int element){
  int i = 0;
  while(i<size){
    if (tab[i] == element){
      return 1;
    }
    i++;
  }
  return 0;
 }




int plus_court_chemin(graphe g,tas t,int depart,int* arrivee, int size_arrivee){
   int j ;
   elem_tas x, sommet;
   float nv_pot;
   for (j = 0;j<g.nbsom;j++){
      t.tab_tas[j].num_som = j;
      t.place_dans_le_tas[j] = j;
      t.tab_tas[j].potentiel = INFINI;}



/*   
   do {printf("Sommet de depart ? "); scanf("%d",&depart); }
   while ((depart < 1)||(depart > g.nbsom)) ;
   do {printf("Sommet d'arrivee ? "); scanf("%d",&arrivee); }
   while ((arrivee < 1)||(arrivee > g.nbsom)||(arrivee==depart)) ;
*/
   t.tab_tas[depart].potentiel = 0;
   /* on amène le sommet depart au sommet du tas, à l’indice 1 */
   x = t.tab_tas[depart];
   t.tab_tas[depart] = t.tab_tas[1];
   t.tab_tas[1] = x;
   t.place_dans_le_tas[depart] = 1; t.place_dans_le_tas[1] = depart;
   
   do {/* le sommet du tas entre dans l'ensemble solution */
   sommet = extraire_min_tas(&t);
   place_tas(&t);
/* sommet est un couple (num_som, potentiel) */
   g.pris[sommet.num_som] = 1;
   g.distance[sommet.num_som] = sommet.potentiel;
/* MAJ des potentiels des successeurs */
   for (j = 1; j <= g.nbsom; j++)
   if ((g.matrice[sommet.num_som][j]) && (! g.pris[j]))
   {  nv_pot = g.matrice[sommet.num_som][j]
         + sommet.potentiel;
      if (nv_pot < t.tab_tas[t.place_dans_le_tas[j]].potentiel)
      {  g.pred[j] = sommet.num_som;
         t.tab_tas[t.place_dans_le_tas[j]].potentiel
                           = nv_pot;
         maj_tas(t.place_dans_le_tas[j],&t);
         place_tas(&t);}
   }
   } while (!check_tab(arrivee,size_arrivee,sommet.num_som));
   return sommet.num_som;

   /*   for (j = 0;j<g.nbsom;j++){ 
      printf("les valeurs de pred sont : %d\n",g.pred[j]);}*/
  /* if (sommet.potentiel != INFINI)
   {  printf("Chemin de %d a %d ",depart,arrivee);
      printf(" - Longueur = %f\n",g.distance[arrivee]);*/
   /*   affiche_itineraire(g,depart,arrivee); printf("\n\n");
   }*/

 /*  else printf("Pas de chemin entre %d et %d\n",depart,arrivee);
   return g.pred;*/

}



/*

void main(){
   graphe * g = calloc(1,sizeof(graphe));
   int n,m;
   FILE * fic = fopen("graphe.txt","r");
   fscanf(fic,"%d %d",&n,&m);
   init_graphe(n,m,g);
   charge_graphe(fic,g);
   affichage(g);
   tas *t;
   init_tas(n,t);
   plus_court_chemin(*g,*t,1,5);
}

*/


   



/*
void affiche(T_Elt T[], const int n)
 
{
 
        int i;
 
        printf("|");
 
        for(i=0;i<n;++i)
 
        {
 
                printf("%ld|",T[i]);
 
        }
 
        printf("\n");
 
}
 
*/


 
void echanger (tas* t, int i, int j)
 
{
 
        elem_tas echange;
 
        echange = t->tab_tas[i];       
 
        t->tab_tas[i] = t->tab_tas[j];
 
        t->tab_tas[j] = echange;
 
}
 
void remonter (tas* t, int i)
 
{
 
        if (i==1) return ;
 
        if (t->tab_tas[i].potentiel < t->tab_tas[i/2].potentiel)
 
        {
 
                echanger (t, i, i/2); 
 
                remonter (t, i/2);
 
        }
      
 
}
 
void  redescendre (tas* t, int i)
 
{
        int n = t->nbelem;
 
        int imin;
 
        if (2*i+1>=n) return ;      
 
        if (t->tab_tas[2*i+1].potentiel<t->tab_tas[2*i].potentiel)   
 
        imin=2*i+1;
 
        else
 
        imin=2*i;
 
        if (t->tab_tas[imin].potentiel<t->tab_tas[i].potentiel)
 
        {
 
                echanger (t, imin, i);
 
                redescendre (t, imin);
 
  
 
        }
       
}


/*
void organiser( T_Elt T[], int n )
 
{
 
        int i;
 
        for(i = 1 ; i < n ; i++)  
 
  
 
        remonter(T, n, i);
 
}
 
  
 
void Tri_Arbre( T_Elt T[], const int n )
 
{
 
        int i;
 
        organiser(T, n);
 
        for(i=n-1 ; i>0 ; i-- )
 
        {
 
                echanger(T, 0, i);
 
                redescendre(T, i, 0);
 
        }
 
}

*/
